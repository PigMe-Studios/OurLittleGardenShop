// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class ETool : uint8
{
	NONE UMETA(DisplayName = "None"),
	TROWEL UMETA(DisplayName = "Trowel"),
	SEEDS UMETA(DisplayName = "Seeds"),
	WATERINGCAN UMETA(DisplayName = "Watering Can")

};

/**
 * 
 */
class OURLITTLEGARDENGAME_API ToolEnumeration
{
public:
	ToolEnumeration();
	~ToolEnumeration();


};
