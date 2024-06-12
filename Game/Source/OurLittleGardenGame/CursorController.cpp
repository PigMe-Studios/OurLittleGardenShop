// Fill out your copyright notice in the Description page of Project Settings.


#include "CursorController.h"
#include "InputMappingContext.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Kismet/GameplayStatics.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "GameFramework/PlayerController.h"

// Sets default values
ACursorController::ACursorController()
{
 	// Set this pawn to call Tick() every frame. You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//posess player on start
	AutoPossessPlayer = EAutoReceiveInput::Player0;

	//initialising physics handle 
	PhysicsHandle = CreateDefaultSubobject<UPhysicsHandleComponent>(TEXT("PhysicsHandle"));

	MouseObjectDistance = 200.0f;
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

void ACursorController::GrabActor(const FInputActionValue& Value)
{
	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, TEXT("clicked"));

	FVector Start = CursorWorldLocation; 
	FVector End = Start + (CursorWorldDirection * 5000.0f);
	
	FHitResult HitResult;
	FCollisionQueryParams LineTraceParams;

	if (GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECollisionChannel::ECC_Visibility, LineTraceParams, FCollisionResponseParams()))
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("HitSomething: %s"), *HitResult.GetActor()->GetName()));

		//check if obkect already sim physics
		UPrimitiveComponent* HitComponent = HitResult.GetComponent();
		if (HitComponent && HitComponent->IsSimulatingPhysics())
		{
			//grab object hit 
			PhysicsHandle->GrabComponentAtLocationWithRotation(HitComponent, NAME_None, HitResult.ImpactPoint, HitComponent->GetComponentRotation());
			//GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, TEXT("grabbing"));
		}
		//todo:change mouse cursor to different state on interact
		//todo: distance from cursor lol

	}
}


void ACursorController::ReleaseActor(const FInputActionValue& Value)
{
	if (PhysicsHandle->GrabbedComponent)
	{
		PhysicsHandle->ReleaseComponent();
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, TEXT("released actor"));
		//todo:return back to normal on release
	}
}

//void ACursorController::StopInteraction(const FInputActionValue& Value)
//{
//	if (PhysicsHandle->GrabbedComponent)
//	{
//		PhysicsHandle->ReleaseComponent();
//		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, TEXT("released actor"));
		//todo:return back to normal on release
//	}
//}



// Called every frame
void ACursorController::Tick(float DeltaTime)
{ 
	Super::Tick(DeltaTime);

	//updates cursor position on tick
	CursorWorldPosition();

	if (PhysicsHandle->GrabbedComponent)
	{
		//updates object location based on cursor movement x distance offset (wip)
		FVector updatelocation = CursorWorldLocation + (CursorWorldDirection * MouseObjectDistance);
		FRotator CursorWorldRotation = CursorWorldDirection.Rotation();

		PhysicsHandle->SetTargetLocationAndRotation(updatelocation, CursorWorldRotation);
	}

}

// Called to bind functionality to input
void ACursorController::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//setting up player input oops
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(InputMappingContext, 0);
		}
	}

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Started, this, &ACursorController::GrabActor);
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Completed, this, &ACursorController::ReleaseActor);

		EnhancedInputComponent->BindAction(UnInteractAction, ETriggerEvent::Triggered, this, &ACursorController::ReleaseActor);
		//todo: need to fix it being held on contuinuously if clicked once and not held 

	}
}

