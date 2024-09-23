#include "Customer.h"
// Fill out your copyright notice in the Description page of Project Settings.


#include "Customer.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ACustomer::ACustomer()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Initialise Name map, player name needs to be loaded from Instance in BP
	NameMap.Add(ECharacter::CHEF, FName("Chef"));
	NameMap.Add(ECharacter::FLORIST, FName("Florist"));
	NameMap.Add(ECharacter::MAILMAN, FName("Post Man"));
	NameMap.Add(ECharacter::PLAYER, FName("Player"));

}

// Called when the game starts or when spawned
void ACustomer::BeginPlay()
{
	Super::BeginPlay();
	//StartDialogue(FName("MM_Intro1"));
}

bool ACustomer::UpdateDialogue(FName Name)
{
	if (Name == FName(""))
	{
		return false;
	}
	// Events should be completed at the end of a line
	if (FDialogueLine* PreviousRow = DIALOGUE_TABLE->FindRow<FDialogueLine>(CurrentDialogue, ""))
	{
		if (PreviousRow->CompletedEvent != FName(""))
		{
			CompleteEvent(PreviousRow->CompletedEvent);
		}
	}

	if (FDialogueLine* Row = DIALOGUE_TABLE->FindRow<FDialogueLine>(Name, ""))
	{
		CurrentDialogue = Name;
		if (Row->CharacterSpeaking != ECharacter::PLAYER)
		{
			Emotion = Row->CharacterEmotion;
		}

		//? Redundant rn?
		FString CharacterFullName = UEnum::GetValueAsString(Row->CharacterSpeaking);
		CharacterFullName = CharacterFullName.Replace(TEXT("ECharacter::"), TEXT(""));

		FString ProcessedContent = ProcessString(Row->Content);	

		//? Updated this to pass the raw ENUM value, processing the string inside function
		//? Response: The character speaking param is for the name on-top of the textbox, and needs to come
		//? from NameMap to allow for custom names. ProcessString only handles the main part of the textbox.
		ConversationWidget->UpdateContentText(*NameMap.Find(Row->CharacterSpeaking), ProcessedContent, Row->CharacterSpeaking);
		

		if (Row->bRespondable)
		{
			DisplayedResponses.Empty();
			//int ResponseAmount = 0;
			TArray<FString> ResponseContents;
			for (FResponse Response : Row->Responses)
			{
				if (IsResponseConditionMet(Response.Condition))
				{
					ResponseContents.Add(ProcessString(Response.Content));
					DisplayedResponses.Add(Response.NextLine);
				}
			}
			ConversationWidget->DisplayResponses(DisplayedResponses.Num(), ResponseContents);
		}
		else
		{
			ConversationWidget->HideResponses();
		}

		if (Row->TriggeredQuest != FName(""))
		{
			AddQuest(Row->TriggeredQuest);
		}
		if (Row->bRemoveBox)
		{
			RemoveBox();
		}

		return true;
	}
	return false;
}

void ACustomer::CreateConversationWidget()
{
	APlayerController* Controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (Controller)
	{
		ConversationWidget = CreateWidget<UConversationWidget>(Controller, CONVERSATION_CLASS);
		if (ConversationWidget)
		{
			ConversationWidget->AddToViewport();
			ConversationWidget->OwningCustomer = this;
		}
	}
}

FName ACustomer::GetResponseDialogue(int ResponseOption)
{
	FDialogueLine* Row = DIALOGUE_TABLE->FindRow<FDialogueLine>(CurrentDialogue, "");
	for (int i = 0; i < DisplayedResponses.Num(); i++) {
		if (i == ResponseOption - 1)
		{
			FName Name = DisplayedResponses[i];
			return Name;
		}
	}
	return FName();
}

void ACustomer::StartDialogue(FName DialogueLine)
{
	CreateConversationWidget();
	//bDialogueOpen = true;
	UpdateStatus(true);
	UpdateDialogue(FName(DialogueLine));
	FDialogueLine* Row = DIALOGUE_TABLE->FindRow<FDialogueLine>(CurrentDialogue, "");
	SwitchCustomerModel(Row->CharacterSpeaking);
}

void ACustomer::ChangeCharacterName(ECharacter SelectedCharacter, FName NewName)
{
	NameMap.Add(SelectedCharacter, NewName);
}

void ACustomer::EndDialogue(bool bCharacterLeave)
{
	if (ConversationWidget)
	{
		ConversationWidget->CancelTimer();
		ConversationWidget->RemoveFromParent();
		ConversationWidget = nullptr;
	}

	if (FDialogueLine* Row = DIALOGUE_TABLE->FindRow<FDialogueLine>(CurrentDialogue, ""))
	{
		if (Row->CompletedEvent != FName(""))
		{
			CompleteEvent(Row->CompletedEvent);
		}
	}

	if (bCharacterLeave)
	{
		SwitchCustomerModel(ECharacter::NONE);
	}
	
	//bDialogueOpen = false;
	UpdateStatus(false);

}



FName ACustomer::GetNextLine()
{
	FDialogueLine* Row = DIALOGUE_TABLE->FindRow<FDialogueLine>(CurrentDialogue, "");
	return Row->NextLine;
}

FString ACustomer::ProcessString(FString Content)
{
	RefreshNames();
	FString ProcessedString = Content;
	ProcessedString = ProcessedString.Replace(TEXT("[Name]"), *NameMap.Find(ECharacter::PLAYER)->ToString());
	ProcessedString = ProcessedString.Replace(TEXT("[Shop]"), *ShopName.ToString());
	//ProcessedString = ProcessedString.Replace(TEXT("[Name]"), TEXT("IUHDFIOUAHOIAUDW"));
	return ProcessedString;
}

bool ACustomer::IsResponseConditionMet(FName Condition)
{

	if (bool* ConditionValue = ConditionMap.Find(Condition))
	{
		return *ConditionValue;
	}
	return true;

	
}

// Called every frame
void ACustomer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

