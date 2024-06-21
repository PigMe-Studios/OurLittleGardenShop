// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MenuWidgetSwitcher.generated.h"

/**
 * 
 */
UCLASS()
class OURLITTLEGARDENGAME_API UMenuWidgetSwitcher : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void SetupWidget();

	void DestroyWidget();
};
