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
	
}

bool ACustomer::UpdateDialogue(FName Name)
{
	FDialogueLine* Row = DIALOGUE_TABLE->FindRow<FDialogueLine>(Name, "");
	Emotion = Row->CharacterEmotion;
	// TODO: Add UI element to update, update it's text
	return false;
}

// Called every frame
void ACustomer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

