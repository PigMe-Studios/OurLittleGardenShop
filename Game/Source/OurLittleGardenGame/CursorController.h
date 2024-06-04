// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "InputAction.h"
#include "CursorController.generated.h"

class UInputMappingContext;
class UInputAction;

UCLASS()
class OURLITTLEGARDENGAME_API ACursorController : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ACursorController();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//cursor visibility
	

	//xUPROPERTY(EditAnywhere, BlueprintReadWrite, category = "Cursor")
	//xEMouseCursorType MouseCursor = EMouseCursorType: Default;

	//Character mapping context for controls
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "EnhancedInput")
	UInputMappingContext* InputMappingContext;

	//Interaction action on click
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "EnhancedInput")
	class UInputAction* InteractAction;

	//Called when LMB pressed
	void Interaction(const FInputActionValue& Value);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
