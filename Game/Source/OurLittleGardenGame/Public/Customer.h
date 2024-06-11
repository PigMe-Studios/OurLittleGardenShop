// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CharacterEnumeration.h"
#include "ConversationWidget.h"
#include "Customer.generated.h"

UCLASS()
class OURLITTLEGARDENGAME_API ACustomer : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACustomer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/// @brief Update Dialogue text and character emotion with new line
	/// @param Name the desired dialogue line
	/// @return Was an appropriate line found?
	bool UpdateDialogue(FName Name);

	/// @brief Create a new Conversation widget and add to viewport
	void CreateConversationWidget();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UDataTable* DIALOGUE_TABLE;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class UConversationWidget> CONVERSATION_CLASS;

	class UConversationWidget* ConversationWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ECharacter Character;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EEmotion Emotion;
};
