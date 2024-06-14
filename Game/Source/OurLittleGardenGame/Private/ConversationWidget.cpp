// Fill out your copyright notice in the Description page of Project Settings.


#include "ConversationWidget.h"

void UConversationWidget::NativeConstruct()
{
	Super::NativeConstruct();

	ResponseButtons = { RESPONSE_BUTTON_1, RESPONSE_BUTTON_2 , RESPONSE_BUTTON_3 };
}

void UConversationWidget::UpdateContentText(FName Name, FString Content)
{
	NAME_TEXT->SetText(FText::FromName(Name));
	CONTENT_TEXT->SetText(FText::FromString(Content));
	DisplayResponses(1);
}

void UConversationWidget::DisplayResponses(int Amount)
{
	for (int i = 0; i < ResponseButtons.Num(); i++) {
		if (Amount  > i)
		{
			ResponseButtons[i]->SetVisibility(ESlateVisibility::Visible);
		}
		else
		{
			ResponseButtons[i]->SetVisibility(ESlateVisibility::Hidden);
		}
	}
}

void UConversationWidget::HideResponses()
{
	for (UButton* Button : ResponseButtons)
	{
		Button->SetVisibility(ESlateVisibility::Hidden);
	}
}
