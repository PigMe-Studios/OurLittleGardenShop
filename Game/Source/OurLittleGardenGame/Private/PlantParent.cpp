// Fill out your copyright notice in the Description page of Project Settings.


#include "PlantParent.h"

// Sets default values
APlantParent::APlantParent()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APlantParent::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlantParent::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APlantPArent::Grow_Implementation(float GrowthPerTick)
{
	
}