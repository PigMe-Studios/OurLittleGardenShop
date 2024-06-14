// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractionInterface.h"
#include "InteractableObjectParent.generated.h"


UCLASS()
class OURLITTLEGARDENGAME_API AInteractableObjectParent : public AActor, public IInteractionInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInteractableObjectParent();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* StaticMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Interaction")
	bool bCanBePickedUp;

	void OnGrab();
	void OnRelease();

	void pickup();
	void View();

	//insert other action here

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	//prototype decleration
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
	void Interact(); 
	// actual decleration of interactinterface
	virtual void Interact_Implementation() override;

};
