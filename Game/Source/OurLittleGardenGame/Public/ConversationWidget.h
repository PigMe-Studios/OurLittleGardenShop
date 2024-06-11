// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ConversationWidget.generated.h"

class UTextBlock;

/**
 * 
 */
UCLASS()
class OURLITTLEGARDENGAME_API UConversationWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	/// @brief Update Name and Content textboxes
	/// @param Name to display in Name textbox
	/// @param Content is the text to display in the main textbox
	void UpdateContentText(FName Name, FString Content);

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UTextBlock* NAME_TEXT;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UTextBlock* CONTENT_TEXT;
};
