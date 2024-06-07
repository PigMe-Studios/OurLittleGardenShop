// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Growable.generated.h"

/**
 * This class does not need to be modified.
 * Empty class for reflection system visibility.
 * Uses the UINTERFACE macro.
 * Inherits from UInterface.
 */
UINTERFACE(MinimalAPI, Blueprintable)
class UGrowable : public UInterface
{
	GENERATED_BODY()
};

//! Actual interface decleration
class IGrowable
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void GrowPlant();

};

