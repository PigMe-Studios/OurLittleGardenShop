// Fill out your copyright notice in the Description page of Project Settings.


#include "CursorController.h"
#include "InputMappingContext.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h"

// Sets default values
ACursorController::ACursorController()
{
 	// Set this pawn to call Tick() every frame. You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//posess player on start
	AutoPossessPlayer = EAutoReceiveInput::Player0;
}

// Called when the game starts or when spawned
void ACursorController::BeginPlay()
{
	Super::BeginPlay();
	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, TEXT("Scene is Working"));

	APlayerController* PlayerControllerRef = Cast<APlayerController>(GetController());
	PlayerControllerRef->SetShowMouseCursor(true);
	//xPlayerControllerRef->DeprojectMousePositionToWorld()

}

void ACursorController::CursorWorldPosition()
{
	//playercontroller reference
	APlayerController* PlayerControllerRef = Cast<APlayerController>(GetController());

	//checks if cursor is reallife + pos
	if (!PlayerControllerRef->GetMousePosition(MouseX, MouseY))
	{
		return;
	}

	//converting cursor position ref to world position ref
	if (PlayerControllerRef->DeprojectScreenPositionToWorld(MouseX, MouseY, CursorWorldLocation, CursorWorldDirection))
	{
		//success
		//GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, FString::Printf(TEXT("Mouse Location %f %f"), MouseX, MouseY));
	}
	else
	{
		// failed
	}
}

void ACursorController::Interaction(const FInputActionValue& Value)
{
	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, TEXT("clicked"));

	FVector Start = CursorWorldLocation; //()->GetComponentLocation();
	FVector End = Start + (CursorWorldDirection * 5000.0f); //->GetForwardVector() * 300.0f;
	
	FHitResult HitResult;
	FCollisionQueryParams LineTraceParams;

	if (GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECollisionChannel::ECC_Visibility, LineTraceParams, FCollisionResponseParams()))
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, TEXT("Interact Event Triggered"));
	}

	//todo:change mouse cursor to different state on interact
	//todo:return back to normal on release
}



// Called every frame
void ACursorController::Tick(float DeltaTime)
{ 
	Super::Tick(DeltaTime);

	//updates cursor position on tick
	CursorWorldPosition();

}

// Called to bind functionality to input
void ACursorController::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Started, this, &ACursorController::Interaction);
	}
}

