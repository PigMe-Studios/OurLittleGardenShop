// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MainMenuWS.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

bool UMainMenuWS::Initialize()
{
	bool const bsuccess = Super::Initialize();
	if (!bsuccess) return false;

	
	if (StartButton)
	{
		StartButton->OnClicked.AddDynamic(this, &UMainMenuWS::OpenStartMenu);
	}

	if (OptionsButton)
	{
		OptionsButton->OnClicked.AddDynamic(this, &UMainMenuWS::OpenOptionsMenu);
	}

	if (QuitButton)
	{
		QuitButton->OnClicked.AddDynamic(this, &UMainMenuWS::QuitGame);
	}

	if (NewGameButton)
	{
		NewGameButton->OnClicked.AddDynamic(this, &UMainMenuWS::NewGameData);
	}

	if (LoadGameButton)
	{
		LoadGameButton->OnClicked.AddDynamic(this, &UMainMenuWS::LoadGameData);
	}

	if (BackButton)
	{
		BackButton->OnClicked.AddDynamic(this, &UMainMenuWS::ReturnToMenu);
	}

	//setting widget switcher to default to the main menu index
	MainMenuWidgetSwitcher->SetActiveWidget(MainMenu);

	return true;
}

void UMainMenuWS::SetActiveWidget(int const& Index)
{
	MainMenuWidgetSwitcher->SetActiveWidgetIndex(Index);
}

void UMainMenuWS::OpenStartMenu()
{
	/**this will be where saving and loading of save files will be popped
	Currently only opens whatever scene
	will also need to check this with deri though as due to persistant levels*/
	//UGameplayStatics::OpenLevel(this, FName("Shop_P"));
	MainMenuWidgetSwitcher->SetActiveWidget(LoadGame);
}

void UMainMenuWS::OpenOptionsMenu()
{
	/**this will be a todo later down the line. Dont need this right now!!*/
	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Purple, TEXT("Options menu will be real one day <3"));

	//MainMenuWidgetSwitcher->SetActiveWidget(OptionsMenu);
}

void UMainMenuWS::QuitGame()
{

	UKismetSystemLibrary::QuitGame(this, GetWorld()->GetFirstPlayerController(), EQuitPreference::Quit, true);

	/**Quit game? 
	Maybe give the players the option to make sure they wanna quit
	and also to save or discarg their gameplay?! / also create another save file if theyve not got one set up*/
}

void UMainMenuWS::LoadGameData()
{
	//might have to temp do this in blueprints
}

void UMainMenuWS::NewGameData()
{
	//might have to temp do this in blueprints
}

void UMainMenuWS::ReturnToMenu()
{
	//can be used from any other switcher to go back to the main menu
	MainMenuWidgetSwitcher->SetActiveWidget(MainMenu);
}
