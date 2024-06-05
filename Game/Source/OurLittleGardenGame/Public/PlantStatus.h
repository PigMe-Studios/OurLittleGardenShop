// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlantStatus.generated.h"

/**
 * 
 */

//!Structs

USTRUCT(BlueprintType)
struct FPlantStatus
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float GrowthPercent;

	//UPROPERTY()
};

USTRUCT(BlueprintType)
struct FPlantResistancesAndRequirements
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float GrowthPercent;

	//UPROPERTY()
};

USTRUCT(BlueprintType)
struct FDecorativeObject
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FTransform Transform;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UClass* Class; //ToDo: change this to the base decoration actor class
};

USTRUCT(BlueprintType)
struct FPlantSaveData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FTransform Transform;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UClass* Class; //ToDo: change this to the base plant class

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FPlantStatus Status;
};

//!Enums

UENUM(BlueprintType)
enum EWaterStat
{
	BoneDry UMETA(DisplayName = "BoneDry"),
	Dry UMETA(DisplayName = "Dry"),
};

UENUM(BlueprintType)
enum EKnowledgeLevel
{
	Undiscovered UMETA(DisplayName = "Undiscovered"),
	Aware UMETA(DisplayName = "Aware"),
	Knowledgable UMETA(DisplayName = "Knowledgable"),
};

UENUM(BlueprintType)
enum ELevel
{
	Title UMETA(DisplayName = "Title"),
	Garden UMETA(DisplayName = "Garden"),
	Shop UMETA(DisplayName = "Shop"),
};

UENUM(BlueprintType)
enum EPlants
{
	Carrot UMETA(DisplayName = "Carrot"),
	Sage UMETA(DisplayName = "Sage"),
	Potato UMETA(DisplayName = "Potato"),
	Lavender UMETA(DisplayName = "Lavender"),
};
