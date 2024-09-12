// Fill out your copyright notice in the Description page of Project Settings.


#include "CursorController.h"
#include "Engine/Engine.h"
#include "GameFramework/Actor.h"
#include "Components/PrimitiveComponent.h"
#include "InputMappingContext.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "InteractableObjectParent.h"
#include "InteractionInterface.h"
#include "AkGameplayStatics.h"
#include "AkAudioEvent.h"
#include "Kismet/GameplayStatics.h"
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
	LastHoveredActor = nullptr;
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
	//check if already hoilding item or interaction is disablked
	if (bIsInteracting || !bInteractionEnabled)
	{
		return;
	}

	if (CustomerReference && CustomerReference->ConversationWidget != nullptr)
	{
		return;
	}
	FVector Start = CursorWorldLocation; 
	FVector End = Start + (CursorWorldDirection * 5000.0f);
	
	FHitResult HitResult;
	FCollisionQueryParams LineTraceParams;

	if (GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECollisionChannel::ECC_Visibility, LineTraceParams, FCollisionResponseParams())
		&& !IsDialogueActive())
	{
		AActor* HitActor = HitResult.GetActor();

		if (HitActor && HitActor->GetClass()->ImplementsInterface(UInteractionInterface::StaticClass()))
		{
			IInteractionInterface::Execute_Interact(HitActor);
		
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
	}
}

void ACursorController::GrabActor(const FHitResult& HitResult, AInteractableObjectParent* InteractableObject)
{
	UPrimitiveComponent* HitComponent = HitResult.GetComponent();

	if (HitComponent && HitComponent->IsSimulatingPhysics())
	{
		PhysicsHandle->GrabComponentAtLocationWithRotation(HitComponent, NAME_None, HitResult.GetActor()->GetActorLocation(), HitComponent->GetComponentRotation());
		//PhysicsHandle->GrabComponentAtLocation(HitComponent, NAME_None, HitResult.ImpactPoint);
		bIsInteracting = true;
		SetCursorType(ECursorType::Interact);

		if (InteractableObject)
		{
			InteractableObject->OnGrab();
			MouseObjectDistance = InteractableObject->GrabDistance;
			HeldActor = InteractableObject;
			RotationSpeed = InteractableObject->RotationSpeed;
			GrabRotation = InteractableObject->GetActorRotation();
			RotationYaw = GrabRotation.Yaw;
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
	//check if interaction is enabled
	if (!bInteractionEnabled)
	{
		SetCursorType(ECursorType::Default);
		HoverOutline(nullptr);
		return;
	}

	//checking for cursor hover over interactable item
	if (bIsInteracting)
	{
		SetCursorType(ECursorType::Interact);
		HoverOutline(nullptr);
		return;
	}

	FVector Start = CursorWorldLocation;
	FVector End = Start + (CursorWorldDirection * 5000.0f);

	FHitResult HitResult;
	FCollisionQueryParams LineTraceParams;

	if (GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECollisionChannel::ECC_Visibility, LineTraceParams, FCollisionResponseParams()))
	{
		AActor* HitActor = HitResult.GetActor();
		UPrimitiveComponent* HitComponent = HitResult.GetComponent();

		if (!IsValid(HitActor))
		{
			// If the cursor is no longer over any actor, reset the flag
			bHoverSoundPlayed = false;
			return;
		}

		if (!HitActor->GetClass()->ImplementsInterface(UInteractionInterface::StaticClass()))
		{
			SetCursorType(ECursorType::Default);
			// Remove outline
			HoverOutline(nullptr);
			// Reset the flag if the actor does not implement the interface
			bHoverSoundPlayed = false;
			return;
		}

		SetCursorType(ECursorType::HoverInteract);
		// Outline triggered on current hovered object
		HoverOutline(HitActor);

		// Audio - Getting the ak event for hover from the actor implementing interaction interface
		if (HitActor != PrevHoveredActor)
		{
			bHoverSoundPlayed = false; // Reset the flag for a new actor
		}

		if (!bHoverSoundPlayed)
		{
			UAkAudioEvent* HoverEvent = IInteractionInterface::Execute_GetHoverAkEvent(HitActor);
			if (IsValid(HoverEvent))
			{
				UAkGameplayStatics::PostEvent(HoverEvent, nullptr, 0, FOnAkPostEventCallback(), true);
				bHoverSoundPlayed = true; // Set the flag after playing the sound
			}
		}

		PrevHoveredActor = HitActor;
	}
	else
	{
		SetCursorType(ECursorType::Default); 
		//remove outline
		HoverOutline(nullptr);
	}

}

void ACursorController::SetInteractionEnabled(bool bEnabled)
{
	bInteractionEnabled = bEnabled;

	// remove outline from actor if disabled
	if (!bInteractionEnabled)
	{
		if (LastHoveredActor)
		{
			if (UStaticMeshComponent* LastMeshComponent = LastHoveredActor->FindComponentByClass<UStaticMeshComponent>())
			{
				LastMeshComponent->SetRenderCustomDepth(false);
			}
			LastHoveredActor = nullptr;
		}
	}
}

bool ACursorController::IsInteractionEnabled() const
{
	return bInteractionEnabled;
}


void ACursorController::HoverOutline(AActor* CurrentHoveredActor)
{
	if (!bInteractionEnabled)
	{
		return;
	}

	//disable 'render customdepth pass' on the last hovered actor
	if (LastHoveredActor && LastHoveredActor != CurrentHoveredActor)
	{
		TArray<UStaticMeshComponent*> LastMeshComponents;
		LastHoveredActor->GetComponents<UStaticMeshComponent>(LastMeshComponents);

		TArray<USkeletalMeshComponent*> LastSkeleMeshComponents;
		LastHoveredActor->GetComponents<USkeletalMeshComponent>(LastSkeleMeshComponents);

		//loops through all the meshes in the acotr bp instead 
		for (UStaticMeshComponent * MeshComponent : LastMeshComponents)
		{
			MeshComponent->SetRenderCustomDepth(false);
		}
		for (USkeletalMeshComponent* SkeleMeshComponent : LastSkeleMeshComponents)
		{
			SkeleMeshComponent->SetRenderCustomDepth(false);
		}
	}


	//update the last hovered actor
	LastHoveredActor = CurrentHoveredActor;

	//is object valid with interaction interface
	if (CurrentHoveredActor && CurrentHoveredActor->GetClass()->ImplementsInterface(UInteractionInterface::StaticClass()))
	{
		TArray<UStaticMeshComponent*> MeshComponents;
		LastHoveredActor->GetComponents<UStaticMeshComponent>(MeshComponents);

		TArray<USkeletalMeshComponent*> SkeleMeshComponents;
		LastHoveredActor->GetComponents<USkeletalMeshComponent>(SkeleMeshComponents);

		//updates all object outlines to true
		for (UStaticMeshComponent* MeshComponent : MeshComponents)
		{
			MeshComponent->SetRenderCustomDepth(true);
		}
		for (USkeletalMeshComponent* SkeleMeshComponent : SkeleMeshComponents)
		{
			SkeleMeshComponent->SetRenderCustomDepth(true);
		}
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
		// Reset grab distance to default
		MouseObjectDistance = 200.0f;
		//GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, TEXT("released actor"));

		//tells object that its been released
		AInteractableObjectParent* InteractableObject = Cast<AInteractableObjectParent>(HitActor);
		if (InteractableObject)
		{
			InteractableObject->OnRelease();
		}

		HeldActor = nullptr;
		RotationYaw = 0;
		RotationSpeed = 0;
		//todo:return cursor back to normal on release
	}
}

void ACursorController::RotateActor(const FInputActionValue& Value)
{
	if (HeldActor == nullptr)
	{
		RotateInput(Value.Get<float>());
	}
	else
	{
		RotationMagnitude = Value.Get<float>();
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

		FRotator AddedYaw = FRotator(0, RotationYaw, 0) + GrabRotation;
		PhysicsHandle->SetTargetLocationAndRotation(updatelocation, AddedYaw);//CursorWorldRotation + AddedYaw);

		GEngine->AddOnScreenDebugMessage(1, 200, FColor::Green, FString::Printf(TEXT("Check for snap")));
		FHitResult SnapHitResult;
		FVector SnapStart = updatelocation + (CursorWorldDirection * 50.0f);
		FVector SnapEnd = SnapStart + (CursorWorldDirection * 5000.0f);
		FCollisionQueryParams LineTraceParams;

		// Raycast to check for snap points
		if (GetWorld()->LineTraceSingleByChannel(SnapHitResult, SnapStart, SnapEnd, ECollisionChannel::ECC_Visibility, LineTraceParams, FCollisionResponseParams()))
		{
			UPrimitiveComponent* SnapHitComponent = SnapHitResult.GetComponent();

			//xGEngine->AddOnScreenDebugMessage(1, 200, FColor::Green, FString::Printf(TEXT("Detected Component: %s"), *SnapHitComponent->GetName()));
			if (SnapHitComponent->ComponentHasTag(TEXT("Snap")))
			{
				// When hovering over snap point, change target location of held object
				//xGEngine->AddOnScreenDebugMessage(1, 1, FColor::Red, FString::Printf(TEXT("Snap Detected!")));
				PhysicsHandle->SetTargetLocation(SnapHitComponent->GetComponentLocation());

			}
		}
		//PhysicsHandle->SetTargetLocation(updatelocation);
	}

	if (GetWorld()->GetTimeSeconds() - LastHoverCheck >= HoverCheckDelay)
	{
		CurserHoverCheck();
		LastHoverCheck = GetWorld()->GetTimeSeconds();
	}

	//float DeltaTime = UGameplayStatics::GetWorldDeltaSeconds(this);
	RotationYaw += RotationSpeed * RotationMagnitude * DeltaTime;

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
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Started, this, &ACursorController::LeftClick);
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Completed, this, &ACursorController::ReleaseActor);

		EnhancedInputComponent->BindAction(UnInteractAction, ETriggerEvent::Triggered, this, &ACursorController::ReleaseActor);
		EnhancedInputComponent->BindAction(UnInteractAction, ETriggerEvent::Started, this, &ACursorController::RightClick);

		// Completed rotate action is binded to stop the input
		EnhancedInputComponent->BindAction(RotateAction, ETriggerEvent::Triggered, this, &ACursorController::RotateActor);
		EnhancedInputComponent->BindAction(RotateAction, ETriggerEvent::Completed, this, &ACursorController::RotateActor);

		//todo: on interact, if has tag or something of that idea, can interact in a different way. probably a seperate func but set up similarly

	}
}

