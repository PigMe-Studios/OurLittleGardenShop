// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableObjectParent.h"

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

