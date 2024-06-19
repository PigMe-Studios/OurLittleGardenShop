// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "DialogueTrigger.h"
#include "ConversationWidget.generated.h"

class UTextBlock;
class UButton;
class ACustomer;

/**
 * 
 */
UCLASS()
class OURLITTLEGARDENGAME_API UConversationWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

public:

	/// @brief Update Name and Content textboxes
	/// @param Name to display in Name textbox
	/// @param Content is the text to display in the main textbox
	void UpdateContentText(FName Name, FString Content);

	/// @brief Un-hide relevant response buttons
	/// @param Amount of response buttons to display, between 1-3
	/// @param Contents of each response button
	void DisplayResponses(int Amount, TArray<FString> Contents);

	/// @brief Progress to next dialogue line when button pressed
	/// @param 	Chosen response represented as an integer from 0-3 (0 when the player can't respond)
	UFUNCTION(BlueprintCallable)
	void ProgressDialogue(int ChosenResponse);

	/// @brief Hide all response buttons
	void HideResponses();

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UTextBlock* NAME_TEXT;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UTextBlock* CONTENT_TEXT;

	// Reponse buttons
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UButton* RESPONSE_BUTTON_1;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UButton* RESPONSE_BUTTON_2;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UButton* RESPONSE_BUTTON_3;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UTextBlock* RESPONSE_TEXT_1;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UTextBlock* RESPONSE_TEXT_2;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UTextBlock* RESPONSE_TEXT_3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UButton*> ResponseButtons;
	TArray<UTextBlock*> ResponseTexts;

	AActor* OwningCustomer;
};
