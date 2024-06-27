// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlantStatus.generated.h"

/**
 * 
 */
//!Forward Declarations

class ADecorationParent;
class APlantParent;

//!Enums

UENUM(BlueprintType)
enum EWaterStat
{
	BoneDry UMETA(DisplayName = "BoneDry"),
	Dry UMETA(DisplayName = "Dry"),
	Moist UMETA(DisplayName = "Moist"),
	Wet UMETA(DisplayName = "Wet"),
	Sopping UMETA(DisplayName = "Sopping"),
	Drowned UMETA(DisplayName = "Drowned"),
};

UENUM(BlueprintType)
enum ELightExposure
{
	PitchBlack UMETA(DisplayName = "PitchBlack"),
	FullCover UMETA(DisplayName = "FullCover"),
	Shaded UMETA(DisplayName = "Shaded"),
	Fair UMETA(DisplayName = "Fair"),
	Bright UMETA(DisplayName = "Bright"),
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
	None UMETA(DisplayName = "None"),
	Carrot UMETA(DisplayName = "Carrot"),
	Sage UMETA(DisplayName = "Sage"),
	Potato UMETA(DisplayName = "Potato"),
	Lavender UMETA(DisplayName = "Lavender"),
};


//!Structs

USTRUCT(BlueprintType)
struct FPlantStatus
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float GrowthPercent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TEnumAsByte<EWaterStat> WaterStatus;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//EDisease Diseased;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float RandomisationSeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float PlantHealth;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//EIrreparableDamage PermanentDefects;
};

USTRUCT(BlueprintType)
struct FPlantResistancesAndRequirements : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float TypicalGrowthSpeed = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bPondPlant = false;

	//!Visual
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Visual")
	UStaticMesh* Stem;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Visual")
	UMaterial* StemMat;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Visual")
	UStaticMesh* FruitingBody;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Visual")
	UMaterial* FruitingBodyMat;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Visual")
	UStaticMesh* Flower;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Visual")
	UMaterial* FlowerMat;

	//!Desires

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Desire")
	TEnumAsByte<EWaterStat> DesiredWater = Moist;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Desire")
	TEnumAsByte<ELightExposure> DesiredLight = Fair;

	//!Resistance

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resistance")
	float WaterResist = 0.6;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resistance")
	float LightResist = 0.8;
};


USTRUCT(BlueprintType)
struct FDecorativeObject
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FTransform Transform;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<ADecorationParent> Class;

};

USTRUCT(BlueprintType)
struct FPlantSaveData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FTransform Transform;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<APlantParent> Class;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FPlantStatus Status;
};

