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
	CreateConversationWidget();
	UpdateDialogue(FName("NewRow"));
}

// TODO: Remove "Name" from struct, as Data-tables already have row names
// TODO: Get name of character from row
bool ACustomer::UpdateDialogue(FName Name)
{
	if (FDialogueLine* Row = DIALOGUE_TABLE->FindRow<FDialogueLine>(Name, ""))
	{
		Emotion = Row->CharacterEmotion;
		ConversationWidget->UpdateContentText(FName("Test"), Row->Content);
		if (Row->bRespondable)
		{
			TArray<FString> ResponseContents;
			for (FResponse Response : Row->Responses)
			{
				ResponseContents.Add(Response.Content);
			}
			ConversationWidget->DisplayResponses(Row->Responses.Num(), ResponseContents);
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
	}
}

// Called every frame
void ACustomer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

