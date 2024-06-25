// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/MenuWidgetSwitcher.h"
#include "PauseMenu.generated.h"


class UButton;
class UWidgetSwitcher;
class UWidget;
/**
 * 
 */
UCLASS()
class OURLITTLEGARDENGAME_API UPauseMenu : public UMenuWidgetSwitcher
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
	UWidget* PauseMenu;

	//button list

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	UButton* ResumeButton;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	UButton* MainMenuButton;




	UFUNCTION()
	void ResumeGame();

	UFUNCTION()
	void GoToMenu();


protected:
private:

};
