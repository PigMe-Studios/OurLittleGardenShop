// Fill out your copyright notice in the Description page of Project Settings.


#include "Customer.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ACustomer::ACustomer()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACustomer::BeginPlay()
{
	Super::BeginPlay();
	//StartDialogue(FName("MM_Intro1"));
}

bool ACustomer::UpdateDialogue(FName Name)
{
	if (FDialogueLine* Row = DIALOGUE_TABLE->FindRow<FDialogueLine>(Name, ""))
	{
		CurrentDialogue = Name;
		Emotion = Row->CharacterEmotion;
		FString CharacterFullName = UEnum::GetValueAsString(Row->CharacterSpeaking);
		CharacterFullName = CharacterFullName.Replace(TEXT("ECharacter::"), TEXT(""));
		ConversationWidget->UpdateContentText(FName(CharacterFullName), Row->Content);
		if (Row->bRespondable)
		{
			DisplayedResponses.Empty();
			//int ResponseAmount = 0;
			TArray<FString> ResponseContents;
			for (FResponse Response : Row->Responses)
			{
				if (IsResponseConditionMet(Response.Condition))
				{
					ResponseContents.Add(Response.Content);
					DisplayedResponses.Add(Response.NextLine);
				}
			}
			ConversationWidget->DisplayResponses(DisplayedResponses.Num(), ResponseContents);
		}
		else
		{
			ConversationWidget->HideResponses();
		}

		return true;
	}
	return false;
}

void ACustomer::CreateConversationWidget()
{
	APlayerController* Controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	ConversationWidget = CreateWidget<UConversationWidget>(Controller, CONVERSATION_CLASS);
	if (ConversationWidget)
	{
		ConversationWidget->AddToPlayerScreen();
		ConversationWidget->OwningCustomer = this;
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
	UpdateDialogue(FName(DialogueLine));
}

void ACustomer::EndDialogue()
{
	if (ConversationWidget)
	{
		ConversationWidget->RemoveFromParent();
		ConversationWidget = nullptr;
	}

	if (FDialogueLine* Row = DIALOGUE_TABLE->FindRow<FDialogueLine>(CurrentDialogue, ""))
	{
		if (Row->CompletedEvent != FName(""))
		{
			CompleteEvent(Row->CompletedEvent);
		}
		if (Row->TriggeredQuest != FName(""))
		{
			AddQuest(Row->TriggeredQuest);
		}
	}

}

FName ACustomer::GetNextLine()
{
	FDialogueLine* Row = DIALOGUE_TABLE->FindRow<FDialogueLine>(CurrentDialogue, "");
	return Row->NextLine;
}

bool ACustomer::IsResponseConditionMet(FName Condition)
{
	//if (Response.Condition == FName("") || *ConditionMap.Find(Response.Condition))
	//xif (Condition == FName(""))
	//x{
	//x	return true;
	//x}

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

