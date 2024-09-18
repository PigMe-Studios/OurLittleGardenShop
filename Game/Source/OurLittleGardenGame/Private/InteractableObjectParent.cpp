// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableObjectParent.h"
#include "GameFramework/PlayerController.h"
#include "Blueprint/UserWidget.h"
#include "Engine/Engine.h"
#include "AkGameplayStatics.h"
#include "AkAudioEvent.h"

// Sets default values
AInteractableObjectParent::AInteractableObjectParent()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	RootComponent = StaticMesh;

	StaticMesh->SetSimulatePhysics(true);
	StaticMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	StaticMesh->SetCollisionObjectType(ECollisionChannel::ECC_PhysicsBody);

	//defualt pickupable actor to true
	bCanBePickedUp = true;
	bIsWidgetVisible = false;

	// Hover outline is enabled by default
	bHoverOutlineEnabled = true;

}

void AInteractableObjectParent::Interact_Implementation()
{
	if (bCanBePickedUp)
	{
		pickup();
	}
	else
	{
		View();
	}
}

void AInteractableObjectParent::SetHoverOutlineEnabled(bool bEnabled)
{
	bHoverOutlineEnabled = bEnabled;
}

void AInteractableObjectParent::OnGrab()
{
	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Blue, TEXT("BISHELD"));
}

void AInteractableObjectParent::OnRelease()
{
	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Blue, TEXT("BISRELEASED"));
}

void AInteractableObjectParent::pickup()
{
	//pickup
	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Emerald, TEXT("holding object"));

	if (IsValid(InteractSound)) UAkGameplayStatics::PostEvent(InteractSound, this, 0, FOnAkPostEventCallback(), true);
}

void AInteractableObjectParent::View()
{

	if (InteractionWidgetClass)
	{
		APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
		if (bIsWidgetVisible && ActiveWidget)
		{
			ActiveWidget->RemoveFromParent();

			bIsWidgetVisible = false;
		}
		else if (!bIsWidgetVisible)
		{
			ActiveWidget = CreateWidget<UUserWidget>(PlayerController, InteractionWidgetClass);
			if (ActiveWidget)
			{
				ActiveWidget->AddToViewport();

				bIsWidgetVisible = true;
			}
		}
	}
//thyis just removes and creates it straight away again... need to basically flip flop itso instead it doesnt call it
}

// Called when the game starts or when spawned
void AInteractableObjectParent::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AInteractableObjectParent::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

