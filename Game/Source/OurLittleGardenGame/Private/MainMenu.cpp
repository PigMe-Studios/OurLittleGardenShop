// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenu.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"


void UMainMenu::NativeConstruct()
{
    Super::NativeConstruct();

    if (StartButton)
    {
       // StartButton->OnClicked.AddDynamic(this, &W_MainMenu::StartGame);
    }

    if (QuitButton)
    {
       // QuitButton->OnClicked.AddDynamic(this, &W_MainMenu::QuitGame);
    }
}

void UMainMenu::StartGame()
{
	UGameplayStatics::OpenLevel(this, FName("firstlevelname(GETTHIS)"));
}

void UMainMenu::QuitGame()
{
	UKismetSystemLibrary::QuitGame(this, GetWorld()->GetFirstPlayerController(), EQuitPreference::Quit, true);
}
//** will probs want this more interactive,
// eg ckick on door and the shop will open as the start game.
// Will also need to choose if we are loading a game save or starting a new save? Save slots?
// Ask deri how to feed this into persistant levels as itll probs need changing. */