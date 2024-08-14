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

void UConversationWidget::UpdateContentText(ECharacter Character, FString Content)
{
	// Get ENUM as string, remove class specifier. Convert to FName
	FString NameString = UEnum::GetValueAsString(Character);
	NameString = NameString.Replace(TEXT("ECharacter::"), TEXT(""));
	FName Name = *NameString;

	NAME_TEXT->SetText(FText::FromName(Name));

	TextToDisplay = Content;
	CurrentText = TEXT("");

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
			}
		}

	}
}

void UConversationWidget::HideResponses()
{
	for (UButton* Button : ResponseButtons)
	{
		Button->SetVisibility(ESlateVisibility::Hidden);
	}
	//show progress button
	PROGRESS_BUTTON->SetVisibility(ESlateVisibility::Visible);
}

void UConversationWidget::UpdateText(const ECharacter Char)
{
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

			//! Should move this outside the timer, but I cba making variables and shit rn
			bool bAkCompCreated = false;
			UAkComponent* DialogueComponent = UAkGameplayStatics::GetAkComponent(OwningCustomer->GetRootComponent(), bAkCompCreated, FName(), FVector(), EAttachLocation::KeepRelativeOffset);
			if (!IsValid(DialogueComponent)) return;
		
			//! Move these to their own function for tidiness
			// Switching between different character layers
			switch (Char) 
			{
			case ECharacter::CHEF:
				DialogueComponent->SetSwitch(nullptr, "Switch_DialogueRollCharacter", "Chef");
				break;
			case ECharacter::FLORIST:
				DialogueComponent->SetSwitch(nullptr, "Switch_DialogueRollCharacter", "Florist");
				break;
			case ECharacter::MAILMAN:
				DialogueComponent->SetSwitch(nullptr, "Switch_DialogueRollCharacter", "Postman");
				break;
			default:
				DialogueComponent->SetSwitch(nullptr, "Switch_DialogueRollCharacter", "Null");
				break;
			}
			
			// Switching between different text char types
			TCHAR LastChar = CurrentText[CurrentText.Len() - 1];
			if (LastChar == '!' || LastChar == '?') 
			{
				DialogueComponent->SetSwitch(nullptr, "Switch_DialogueRollType", "Exclamation");
			}
			else if (LastChar == '.' || LastChar == ',') 
			{
				DialogueComponent->SetSwitch(nullptr, "Switch_DialogueRollType", "Punctuation");
			}
			else
			{
				DialogueComponent->SetSwitch(nullptr, "Switch_DialogueRollType", "AlphaNum");
				int32 RandInt = FMath::RandRange(1, 10);
				if (RandInt < 4) return;
			}
			// Post the Ak event
			DialogueComponent->PostAkEvent(DialogueRollAkEvent);

#pragma endregion
		}
	}
	else
	{
		GetWorld()->GetTimerManager().ClearTimer(TypingTimerHandle);
	}
}


