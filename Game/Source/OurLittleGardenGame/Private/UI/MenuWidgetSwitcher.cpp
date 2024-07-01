// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MenuWidgetSwitcher.h"

void UMenuWidgetSwitcher::SetupWidget()
{

    this->AddToViewport();

    const UWorld* World = GetWorld();
    if (!ensure(World))
    {
        return;
    }

    APlayerController* PlayerController = World->GetFirstPlayerController();
    if (!ensure(PlayerController))
    {
        return;
    }

    this->SetOwningPlayer(PlayerController);


    FInputModeGameAndUI InputModeData;
    InputModeData.SetWidgetToFocus(this->TakeWidget());

    PlayerController->SetInputMode(InputModeData);
    PlayerController->bShowMouseCursor = true;


}

void UMenuWidgetSwitcher::DestroyWidget()
{
    this->RemoveFromViewport();

    const UWorld* World = GetWorld();
    if (!ensure(World))
    {
        return;
    }

    APlayerController* PlayerController = World->GetFirstPlayerController();
    if (!ensure(PlayerController))
    {
        return;
    }


    const FInputModeGameAndUI InputModeData;
    PlayerController->SetInputMode(InputModeData);
}
