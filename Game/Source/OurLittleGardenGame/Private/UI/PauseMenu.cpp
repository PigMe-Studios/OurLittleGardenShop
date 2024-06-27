// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/PauseMenu.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

bool UPauseMenu::Initialize()
{
    bool const bSuccess = Super::Initialize();
    if (!bSuccess) return false;

    if (ResumeButton)
    {
        ResumeButton->OnClicked.AddDynamic(this, &UPauseMenu::ResumeGame);
    }

    if (MainMenuButton)
    {
        MainMenuButton->OnClicked.AddDynamic(this, &UPauseMenu::GoToMenu);
    }

	//setting widget switcher to default to the main menu index
	MainMenuWidgetSwitcher->SetActiveWidget(PauseMenu);

	//pauses game whilst widget is on player screen
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (PlayerController)
	{
		UGameplayStatics::SetGamePaused(GetWorld(), true);
	}

	return true;
}

void UPauseMenu::SetActiveWidget(int const& Index)
{
	MainMenuWidgetSwitcher->SetActiveWidgetIndex(Index);
}

void UPauseMenu::ResumeGame()
{
	UGameplayStatics::SetGamePaused(GetWorld(), false);
	DestroyWidget();
}

void UPauseMenu::GoToMenu()
{
	UGameplayStatics::SetGamePaused(GetWorld(), false);
	UGameplayStatics::OpenLevel(this, "Menu_P");
}
