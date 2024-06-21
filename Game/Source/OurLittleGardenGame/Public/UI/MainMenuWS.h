// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/MenuWidgetSwitcher.h"
#include "MainMenuWS.generated.h"

class UButton;
class UWidgetSwitcher;
class UWidget;

/**
 * 
 */
UCLASS()
class OURLITTLEGARDENGAME_API UMainMenuWS : public UMenuWidgetSwitcher
{
	GENERATED_BODY()

public:
	virtual bool Initialize() override;

	void SetActiveWidget(int const& Index);

	//widget switcher

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	UWidgetSwitcher* MainMenuWidgetSwitcher;

	//widget switcher menus

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	UWidget* MainMenu;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	UWidget* LoadGame;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	UWidget* OptionsMenu;

	//button list

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	UButton* StartButton;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	UButton* QuitButton;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	UButton* OptionsButton;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	UButton* NewGameButton;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	UButton* LoadGameButton;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	UButton* BackButton;





protected:
private:


	UFUNCTION()
	void OpenStartMenu();

	UFUNCTION()
	void OpenOptionsMenu();

	UFUNCTION()
	void QuitGame();

	UFUNCTION()
	void LoadGameData();

	UFUNCTION()
	void NewGameData();

	UFUNCTION()
	void ReturnToMenu();



	//settings, load game, etc



};
