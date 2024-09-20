// Fill out your copyright notice in the Description page of Project Settings.


#include "ConversationWidget.h"

#include "AkGameplayStatics.h"
#include "AkAudioEvent.h"
#include "AkComponent.h"

class ACustomer;

void UConversationWidget::NativeConstruct()
{
	Super::NativeConstruct();

	ResponseButtons = { RESPONSE_BUTTON_1, RESPONSE_BUTTON_2 , RESPONSE_BUTTON_3 };
	ResponseTexts = { RESPONSE_TEXT_1, RESPONSE_TEXT_2, RESPONSE_TEXT_3 };

	//default anim speed
	TypingAnimInterval = 0.04f;
}

void UConversationWidget::UpdateContentText(FName CharacterName, FString Content, ECharacter Character)
{
	//? Added a validity check here for safety
	if (!IsValid(GetWorld())) 
	{
		UE_LOG(LogTemp, Error, TEXT("ConversationWidget.cpp - UpdateContentText() | GetWorld() is Invalid!"));
		return;
	}
	//? Reverted this to old system, check Customer.cpp for more details
	// Get ENUM as string, remove class specifier. Convert to FName
	//xFString NameString = UEnum::GetValueAsString(Character);
	//xNameString = NameString.Replace(TEXT("ECharacter::"), TEXT(""));
	//xFName Name = *NameString;

	NAME_TEXT->SetText(FText::FromName(CharacterName));

	TextToDisplay = Content;
	CurrentText = TEXT("");

	bIsTyping = true;

	if (CONTENT_TEXT)
	{
		CONTENT_TEXT->SetText(FText::FromString(CurrentText));
	}

	//? Lowenna I've updated this timer call to use a Lamdba function to capture variables to pass into the Update text method
	FTimerManager& TimerManager = GetWorld()->GetTimerManager();	
	TimerManager.SetTimer(
		TypingTimerHandle, 
		[Character, this]() { UConversationWidget::UpdateText(Character); },
		TypingAnimInterval,
		true
	);
}

void UConversationWidget::DisplayResponses(int Amount, TArray<FString> Contents)
{
	for (int i = 0; i < ResponseButtons.Num(); i++) 
	{
		if (Amount  > i)
		{
			ResponseButtons[i]->SetVisibility(ESlateVisibility::Visible);
			ResponseTexts[i]->SetText(FText::FromString(Contents[i]));
			PROGRESS_BUTTON->SetVisibility(ESlateVisibility::Hidden);
		}
		else
		{
			ResponseButtons[i]->SetVisibility(ESlateVisibility::Hidden);
		}
	}
	//PROGRESS_BUTTON->SetVisibility(ESlateVisibility::Hidden);
}

// This function is called in BPs as there's no easy way to bind a button's OnClicked()
// to a function whilst also passing along a parameter
void UConversationWidget::ProgressDialogue(int ChosenResponse)
{
	//TDOD: Move interface check to reduce amount of IF statements
	FName NextLine;
	// Progress after player response
	if (IDialogueTrigger* DialogueInterface = Cast<IDialogueTrigger>(OwningCustomer))
	{
		if (ChosenResponse > 0)
		{
			{
				NextLine = DialogueInterface->GetResponseDialogue(ChosenResponse);
				DialogueInterface->UpdateDialogue(NextLine);
			}
		}
		// Progress for non-respondable dialogue
		else
		{
			NextLine = DialogueInterface->GetNextLine();
			if (NextLine == FName(""))
			{
				DialogueInterface->EndDialogue();
			}
			else
			{
				DialogueInterface->UpdateDialogue(NextLine);

				bIsTyping = true;
			}
		}

	}
}

void UConversationWidget::CancelTimer()
{
	GetWorld()->GetTimerManager().ClearTimer(TypingTimerHandle);
}

void UConversationWidget::HideResponses()
{
	for (UButton* Button : ResponseButtons)
	{
		Button->SetVisibility(ESlateVisibility::Hidden);
	}
	//show progress button
	PROGRESS_BUTTON->SetVisibility(ESlateVisibility::Visible);
	SkipText_Button->SetVisibility(ESlateVisibility::Visible);
}

void UConversationWidget::UpdateText(const ECharacter Char)
{
	if (!bIsTyping)
	{
		CONTENT_TEXT->SetText(FText::FromString(TextToDisplay));
		CancelTimer();
		return;
	}


	//text anim updating
	if (CurrentText.Len() < TextToDisplay.Len())
	{
		CurrentText += TextToDisplay[CurrentText.Len()];
		if (CONTENT_TEXT)
		{
			CONTENT_TEXT->SetText(FText::FromString(CurrentText));

#pragma region Audio
			//Audio
			if (!IsValid(DialogueRollAkEvent) || CurrentText.IsEmpty()) return;

			if (!IsValid(DialogueRollAkComponent))
			{
				bool bAkCompCreated = false;
				DialogueRollAkComponent = UAkGameplayStatics::GetAkComponent(OwningCustomer->GetRootComponent(), bAkCompCreated, FName(), FVector(), EAttachLocation::KeepRelativeOffset);
			}

			SetCharacterSwitch(DialogueRollAkComponent, Char);
			SetTextTypeSwitch(DialogueRollAkComponent, CurrentText);
			// Post the Ak event
			if (!ShouldPostEvent(CurrentText)) return;
			DialogueRollAkComponent->PostAkEvent(DialogueRollAkEvent);

#pragma endregion
		}
	}
	else
	{
		CancelTimer();
		bIsTyping = false;
		//DialogueRollAkComponent->DestroyComponent();
	}
}

void UConversationWidget::SkipTextRollout()
{
	if (bIsTyping)
	{
		bIsTyping = false;
		CancelTimer();
		//reveals full text, skips 'anim'
		CONTENT_TEXT->SetText(FText::FromString(TextToDisplay));
	}
}


#pragma region Audio

void UConversationWidget::SetCharacterSwitch(UAkComponent* InComponent, ECharacter InChar)
{
	switch (InChar)
	{
	case ECharacter::CHEF:
		InComponent->SetSwitch(nullptr, "Switch_DialogueRollCharacter", "Chef");
		break;
	case ECharacter::FLORIST:
		InComponent->SetSwitch(nullptr, "Switch_DialogueRollCharacter", "Florist");
		break;
	case ECharacter::MAILMAN:
		InComponent->SetSwitch(nullptr, "Switch_DialogueRollCharacter", "Postman");
		break;
	default:
		InComponent->SetSwitch(nullptr, "Switch_DialogueRollCharacter", "Null");
		break;
	}
}

void UConversationWidget::SetTextTypeSwitch(UAkComponent* InComponent, const FString& InCurrentText)
{
	TCHAR LastChar = InCurrentText[InCurrentText.Len() - 1];
	if (LastChar == '!' || LastChar == '?')
	{
		InComponent->SetSwitch(nullptr, "Switch_DialogueRollType", "Exclamation");
	}
	else if (LastChar == '.' || LastChar == ',')
	{
		InComponent->SetSwitch(nullptr, "Switch_DialogueRollType", "Punctuation");
	}
	else
	{
		InComponent->SetSwitch(nullptr, "Switch_DialogueRollType", "AlphaNum");
	}
}

bool UConversationWidget::ShouldPostEvent(const FString& InCurrentText)
{
	if (InCurrentText.IsEmpty())
	{
		UE_LOG(LogTemp, Error, TEXT("InCurrentText is empty in ShouldPostEvent!"));
		return false;
	}

	TCHAR LastChar = InCurrentText[InCurrentText.Len() - 1];

	if (LastChar != '!' && LastChar != '?' && LastChar != '.' && LastChar != ',')
	{
		int32 RandInt = FMath::RandRange(1, 10);
		return RandInt > 4;
	}

	return true;
}

#pragma endregion

