// Fill out your copyright notice in the Description page of Project Settings.


#include "ScreenLock.h"

// Sets default values for this component's properties
UScreenLock::UScreenLock()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

bool UScreenLock::CheckOnScreen()
{
	// Get location of Mesh on screen
	FVector MeshLocation = RestrainedMesh->GetComponentLocation();
	FVector2D ScreenLocation;
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	int32 ViewportSizeX, ViewportSizeY;
	PlayerController->ProjectWorldLocationToScreen(MeshLocation, ScreenLocation);
	
	// Get Size of the screen, and calculate the Pixel amount of Edge Tolerance 
	PlayerController->GetViewportSize(ViewportSizeX, ViewportSizeY);

	if (ScreenLocation.X < 0 || ScreenLocation.X > ViewportSizeX)
	{
		return false;
	}
	if (ScreenLocation.Y < 0 || ScreenLocation.Y > ViewportSizeY)
	{
		return false;
	}

	return true;
}


// Called when the game starts
void UScreenLock::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UScreenLock::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (bLockToScreen && !CheckOnScreen())
	{
		GEngine->AddOnScreenDebugMessage(1, 1, FColor::Red, FString::Printf(TEXT("Offscreen")));
	}

	// ...
}

