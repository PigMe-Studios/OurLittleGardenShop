// Fill out your copyright notice in the Description page of Project Settings.


#include "DecorationParent.h"

// Sets default values
ADecorationParent::ADecorationParent()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ObjectMesh"));

	Mesh->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ADecorationParent::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADecorationParent::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

