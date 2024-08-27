// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "InputActionValue.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Public/Customer.h"
#include "CursorController.generated.h"

class UInputMappingContext;
class AInteractableObjectParent;
class UInputAction;
class ACustomer;


UENUM(BlueprintType)
enum class ECursorType : uint8
{
	Default UMETA(DisplayName = "Default"),
	Interact UMETA(DisplayName = "Interact"),
	HoverInteract UMETA(DisplayName = "Hover"),

};


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
	//stop interation action on click
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "EnhancedInput")
	class UInputAction* UnInteractAction;
	// Used to rotate grabbed objects
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "EnhancedInput")
	class UInputAction* RotateAction;


	//Called when LMB pressed
	void ActorInteract(const FInputActionValue& Value);
	UFUNCTION(BlueprintCallable)
	//called when lmb released
	void ReleaseActor(const FInputActionValue& Value);
	// Called when scroll wheel / QE pressed
	void RotateActor(const FInputActionValue& Value);

	//hover outline effect 
	void HoverOutline(AActor* CurrentHoveredActor);

	void CursorWorldPosition();

	//mouse detection for screen location
	float MouseX;
	float MouseY;
	float MouseObjectDistance;

	//tick flaot check
	float HoverCheckDelay;
	float LastHoverCheck;

	// Amount to rotate a grabbed object
	float RotationMagnitude;

	float RotationYaw;

	float RotationSpeed;

	AActor* LastHoveredActor = nullptr;

	// The rotation of the grabbed object when it is first grabbed
	FRotator GrabRotation;

	//world position of the mouse location
	FVector CursorWorldLocation;
	FVector CursorWorldDirection;

	bool bIsInteracting;

	// The actor currently being held by the player
	AActor* HeldActor;

	AActor* PrevHoveredActor = nullptr;
	bool bHoverSoundPlayed = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UPhysicsHandleComponent* PhysicsHandle;



public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable)
	void GrabActor(const FHitResult& HitResult, AInteractableObjectParent* InteractableObject);

	void SetCursorType(ECursorType CursorType);

	void CurserHoverCheck();

	// @Breif Check if the textbox is currently on screen
	// @Return Is the textbox on screen?
	UFUNCTION(BlueprintImplementableEvent)
	bool IsDialogueActive();

	// These are used for the currently active tool
	UFUNCTION(BlueprintImplementableEvent)
	void LeftClick();
	UFUNCTION(BlueprintImplementableEvent)
	void RightClick();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EnhancedInput")
	ACustomer* CustomerReference;

private:
};
