// Fill out your copyright notice in the Description page of Project Settings.


#include "CursorController.h"
#include "Engine/Engine.h"
#include "GameFramework/Actor.h"
#include "Components/PrimitiveComponent.h"
#include "InputMappingContext.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
//#include "Kismet/GameplayStatics.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "InteractableObjectParent.h"
#include "InteractionInterface.h"
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

	bIsInteracting = false;

	MouseObjectDistance = 200.0f;

	HoverCheckDelay = 0.1f;
	LastHoverCheck = 0.0f;
}

// Called when the game starts or when spawned
void ACursorController::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* PlayerControllerRef = Cast<APlayerController>(GetController());
	PlayerControllerRef->SetShowMouseCursor(true);
	
	SetCursorType(ECursorType::Default);
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

void ACursorController::ActorInteract(const FInputActionValue& Value)
{
	//check if already hoilding item
	if (bIsInteracting)
	{
		return;
	}

	FVector Start = CursorWorldLocation; 
	FVector End = Start + (CursorWorldDirection * 5000.0f);
	
	FHitResult HitResult;
	FCollisionQueryParams LineTraceParams;

	if (GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECollisionChannel::ECC_Visibility, LineTraceParams, FCollisionResponseParams()))
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("HitSomething: %s"), *HitResult.GetActor()->GetName()));

		AActor* HitActor = HitResult.GetActor();

		if (HitActor && HitActor->GetClass()->ImplementsInterface(UInteractionInterface::StaticClass()))
		{
			//HitResult.GetActor()
			IInteractionInterface::Execute_Interact(HitActor);
			//IInteractionInterface::Execute_Interact(HitActor, CursorController	
			// 
			AInteractableObjectParent* InteractableObject = Cast<AInteractableObjectParent>(HitActor);
			if (InteractableObject && InteractableObject->bCanBePickedUp)
			{
				GrabActor(HitResult, InteractableObject);
			}
		}
		else
		{
			//if not interactable, pick up as physical object
			//GrabActor(HitResult, nullptr);
		}
		//todo:change mouse cursor to different state on interact

	}
}

void ACursorController::GrabActor(const FHitResult& HitResult, AInteractableObjectParent* InteractableObject)
{
	UPrimitiveComponent* HitComponent = HitResult.GetComponent();

	if (HitComponent && HitComponent->IsSimulatingPhysics())
	{
		PhysicsHandle->GrabComponentAtLocationWithRotation(HitComponent, NAME_None, HitResult.ImpactPoint, HitComponent->GetComponentRotation());
		bIsInteracting = true;
		SetCursorType(ECursorType::Interact);

		if (InteractableObject)
		{
			InteractableObject->OnGrab();
		}
	}
}

void ACursorController::SetCursorType(ECursorType CursorType)
{
	//cursor type

	APlayerController* PlayerControllerRef = Cast<APlayerController>(GetController());

	switch (CursorType)
	{
	case ECursorType::Default:
		PlayerControllerRef->CurrentMouseCursor = EMouseCursor::Default;
		break;
	case ECursorType::Interact:
		PlayerControllerRef->CurrentMouseCursor = EMouseCursor::GrabHandClosed;
		break;
		//going to add a hover state to make it more noticable what is interactable 
	case ECursorType::HoverInteract:
		PlayerControllerRef->CurrentMouseCursor = EMouseCursor::GrabHand;
		break;


	default:
		PlayerControllerRef->CurrentMouseCursor = EMouseCursor::Default;
		break;
	}
}

void ACursorController::CurserHoverCheck()
{
	//checking for cursor hover over interactable item

	if (bIsInteracting)
	{
		SetCursorType(ECursorType::Interact);
		return;
	}

	FVector Start = CursorWorldLocation;
	FVector End = Start + (CursorWorldDirection * 5000.0f);

	FHitResult HitResult;
	FCollisionQueryParams LineTraceParams;

	if (GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECollisionChannel::ECC_Visibility, LineTraceParams, FCollisionResponseParams()))
	{
		AActor* HitActor = HitResult.GetActor();

		if (HitActor && HitActor->GetClass()->ImplementsInterface(UInteractionInterface::StaticClass()))
		{
			SetCursorType(ECursorType::HoverInteract); 
		}
		else
		{
			SetCursorType(ECursorType::Default); 
		}
	}
	else
	{
		SetCursorType(ECursorType::Default); 
	}

}

void ACursorController::ReleaseActor(const FInputActionValue& Value)
{
	if (bIsInteracting && PhysicsHandle->GrabbedComponent)
	{

		AActor* HitActor = PhysicsHandle->GrabbedComponent->GetOwner();

		PhysicsHandle->ReleaseComponent();
		bIsInteracting = false;
		SetCursorType(ECursorType::Default);
		//GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, TEXT("released actor"));

		//tells object that its been released
		AInteractableObjectParent* InteractableObject = Cast<AInteractableObjectParent>(HitActor);
		if (InteractableObject)
		{
			InteractableObject->OnRelease();
		}
		//todo:return cursor back to normal on release
	}
}


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

	if (GetWorld()->GetTimeSeconds() - LastHoverCheck >= HoverCheckDelay)
	{
		CurserHoverCheck();
		LastHoverCheck = GetWorld()->GetTimeSeconds();
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
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Started, this, &ACursorController::ActorInteract);
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Completed, this, &ACursorController::ReleaseActor);

		EnhancedInputComponent->BindAction(UnInteractAction, ETriggerEvent::Triggered, this, &ACursorController::ReleaseActor);

		//todo: on interact, if has tag or something of that idea, can interact in a different way. probably a seperate func but set up similarly

	}
}

