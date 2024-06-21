// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenu.generated.h"

/**
 * 
 */
UCLASS()
class OURLITTLEGARDENGAME_API UMainMenu : public UUserWidget
{
	GENERATED_BODY()
	

public: 
	virtual void NativeConstruct() override;

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	class UButton* StartButton;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	class UButton* QuitButton;

private:

	UFUNCTION()
	void StartGame();

	UFUNCTION()
	void QuitGame();


	//settings, load game, etc

};
