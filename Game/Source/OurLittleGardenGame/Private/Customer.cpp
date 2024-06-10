// Fill out your copyright notice in the Description page of Project Settings.


#include "Customer.h"

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
	UpdateDialogue(FName("NewRow"));
	
}

bool ACustomer::UpdateDialogue(FName Name)
{
	if (FDialogueLine* Row = DIALOGUE_TABLE->FindRow<FDialogueLine>(Name, ""))
	{
		Emotion = Row->CharacterEmotion;
		// TODO: Add UI element to update, update it's text
		// TODO: Remove "Name" from struct, as Data-tables already have row names
		UE_LOG(LogTemp, Warning, TEXT("Text: %s"), *Row->Content);
		return true;
	}
	return false;
}

// Called every frame
void ACustomer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

