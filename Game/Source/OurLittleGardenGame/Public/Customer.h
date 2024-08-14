// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CharacterEnumeration.h"
#include "ConversationWidget.h"
#include "DialogueTrigger.h"
#include "Customer.generated.h"

UCLASS()
class OURLITTLEGARDENGAME_API ACustomer : public AActor, public IDialogueTrigger
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ACustomer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/// @brief Update Dialogue text and character emotion with new line
	/// @param Name of the desired dialogue line
	/// @return Was an appropriate line found?
	bool UpdateDialogue(FName Name) override;

	/// @brief Create a new Conversation widget and add to viewport
	void CreateConversationWidget();

	/// @brief Give the Player a new quest
	/// @param Quest ID of the quest to be added
	UFUNCTION(BlueprintImplementableEvent)
	void AddQuest(const FName& QuestID);

	/// @brief Mark an event as completed on the event manager
	/// @param The event to be marked complete
	UFUNCTION(BlueprintImplementableEvent)
	void CompleteEvent(const FName& CompletedEvent);

	/// @brief Switch the customer's model to different character's model
	/// @param New Character's model to switch to
	UFUNCTION(BlueprintImplementableEvent)
	void SwitchCustomerModel(ECharacter NewCharacter);

	UFUNCTION(BlueprintImplementableEvent)
	void UpdateStatus(bool bDialogueOpen);

	/// @brief Search condition map to find if condition met
	/// @param Condition to search for
	/// @return Returns true is condition not found or condition's status is true
	bool IsResponseConditionMet(FName Condition);

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/// @brief Get the Name of the next dialogue line from the response number
	/// @param Response Option chosen by the player
	/// @return Name of the next Dialogue line
	FName GetResponseDialogue(int ResponseOption) override;

	UFUNCTION(BlueprintCallable)
	/// @brief Start a new dialogue conversation
	/// @param Dialogue Line to start the conversation with
	void StartDialogue(FName DialogueLine) override;

	UFUNCTION(BlueprintCallable)
	/// @brief Change the display name of a character
	/// @param Character who's name will be changed
	/// @param New Name to be displayed for the character
	void ChangeCharacterName(ECharacter SelectedCharacter, FName NewName);

	/// @brief Destroy Conversation widget and end dialogue
	void EndDialogue() override;


	/// @brief Get the Name of the next dialogue line from the current dialogue line
	/// @return Name of the next Dialogue line
	FName GetNextLine() override;

	/// @brief Process dialogue by replacing placeholder text (e.g [Name]) with desired text
	/// @param Content to process
	/// @return The processed dialogue
	FString ProcessString(FString Content);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UDataTable* DIALOGUE_TABLE;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<class UConversationWidget> CONVERSATION_CLASS;

	class UConversationWidget* ConversationWidget;

	// Contains the display names of the characters, including the player
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<ECharacter, FName> NameMap;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		ECharacter Character;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EEmotion Emotion;

	FName CurrentDialogue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TMap<FName, bool> ConditionMap;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FName> DisplayedResponses;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FName ShopName ;

	//UPROPERTY(EditAnywhere, BlueprintReadOnly)
		//bool bDialogueOpen;

};