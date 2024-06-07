// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlantStatus.h"
#include "PlantParent.generated.h"

//!Functions
//ToDo:Find Growth speed
//ToDo:Grow for end of day
//ToDo:Harvest
//ToDo:Growth instant on load

UCLASS()
class OURLITTLEGARDENGAME_API APlantParent : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APlantParent();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FPlantResistancesAndRequirements Requirements;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FPlantStatus Status;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
