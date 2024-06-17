// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableObjectParent.h"
#include "GameFramework/PlayerController.h"
#include "CursorController.generated.h"
#include "Engine/Engine.h"

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
}

void AInteractableObjectParent::View()
{
	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Emerald, TEXT("viewing object"));
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

