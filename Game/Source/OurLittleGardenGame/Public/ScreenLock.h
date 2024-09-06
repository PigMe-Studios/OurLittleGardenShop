// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ScreenLock.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class OURLITTLEGARDENGAME_API UScreenLock : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UScreenLock();

	bool CheckOnScreen();

	// Should the object be restricted to the screen
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bLockToScreen;

	// Should the object be restricted to the screen
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UMeshComponent* RestrainedMesh;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
