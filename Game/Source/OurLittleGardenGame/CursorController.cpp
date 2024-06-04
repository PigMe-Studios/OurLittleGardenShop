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

	APlayerController* PlayerControllerRef = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	PlayerControllerRef->SetShowMouseCursor(true);
	//xPlayerControllerRef->DeprojectMousePositionToWorld()
}

void ACursorController::Interaction(const FInputActionValue& Value)
{
	//!im having an issue with thisss ): cant find a way to get the mouse position for this hmm
	FVector Start = (APlayerController::GetMousePosition)->GetComponentLocation();
	FVector End = Start + (APlayerController::GetMousePosition)->GetForwardVector() * 300.0f;
	FHitResult HitResult;

	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);

	if (GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECollisionChannel::ECC_Visibility, Params, FCollisionResponseParams()))
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, TEXT("Interact Event Triggered"));
	}

	DrawDebugLine(GetWorld(), Start, End, FColor::Magenta, false, 5.0f, 0, 5.0f);

	//todo:change mouse cursor to different state on interact

	//todo:return back to normal on release
}

// Called every frame
void ACursorController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//xGEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Emerald, TEXT("Tick is Working"));

	//mouse location on the screen
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetMousePosition(MouseX, MouseY);
	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, FString::Printf(TEXT("Mouse LocSation: %f %f"), MouseX, MouseY));
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

