// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "DialogueTrigger.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UDialogueTrigger : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class OURLITTLEGARDENGAME_API IDialogueTrigger
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	
	/// @brief Get the Name of the next dialogue line from the response number
	/// @param Response Option chosen by the player (represented by an integer)
	/// @return Name of the next Dialogue line
	virtual FName GetResponseDialogue(int ResponseOption);

	/// @brief Update Dialogue text and character emotion with new line
	/// @param Name the desired dialogue line
	/// @return Was an appropriate line found?
	virtual  bool UpdateDialogue(FName Name);

	/// @brief Get the Name of the next dialogue line from the current dialogue line
	/// @return Name of the next Dialogue line
	virtual FName GetNextLine();

	/// @brief Start a new dialogue conversation
	/// @param Dialogue Line to start the conversation with
	virtual void StartDialogue(FName DialogueLine);

	/// @brief Destroy Conversation widget and end dialogue
	/// @param Should the character leave after this dialogue line has finished?
	virtual void EndDialogue(bool bCharacterLeave);
};
