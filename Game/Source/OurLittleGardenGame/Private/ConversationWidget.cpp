// Fill out your copyright notice in the Description page of Project Settings.


#include "ConversationWidget.h"

class ACustomer;

void UConversationWidget::NativeConstruct()
{
	Super::NativeConstruct();

	ResponseButtons = { RESPONSE_BUTTON_1, RESPONSE_BUTTON_2 , RESPONSE_BUTTON_3 };
	ResponseTexts = { RESPONSE_TEXT_1, RESPONSE_TEXT_2, RESPONSE_TEXT_3 };
}

void UConversationWidget::UpdateContentText(FName Name, FString Content)
{
	NAME_TEXT->SetText(FText::FromName(Name));
	CONTENT_TEXT->SetText(FText::FromString(Content));
	//DisplayResponses(1);
}

void UConversationWidget::DisplayResponses(int Amount, TArray<FString> Contents)
{
	for (int i = 0; i < ResponseButtons.Num(); i++) {
		if (Amount  > i)
		{
			ResponseButtons[i]->SetVisibility(ESlateVisibility::Visible);
			ResponseTexts[i]->SetText(FText::FromString(Contents[i]));
			PROGRESS_BUTTON->SetVisibility(ESlateVisibility::Hidden);
		}
		else
		{
			ResponseButtons[i]->SetVisibility(ESlateVisibility::Hidden);
		}
	}
}

// This function is called in BPs as there's no easy way to bind a button's OnClicked()
// to a function whilst also passing along a parameter
void UConversationWidget::ProgressDialogue(int ChosenResponse)
{
	FName NextLine;
	if (ChosenResponse > 0)
	{
		if (IDialogueTrigger* DialogueInterface = Cast<IDialogueTrigger>(OwningCustomer))
		{
			NextLine = DialogueInterface->GetResponseDialogue(ChosenResponse);
			DialogueInterface->UpdateDialogue(NextLine);
		}
	}
	else
	{
		if (IDialogueTrigger* DialogueInterface = Cast<IDialogueTrigger>(OwningCustomer))
		{
			NextLine = DialogueInterface->GetNextLine();
			if (NextLine == FName(""))
			{
				RemoveFromParent();
			}
			else
			{
				DialogueInterface->UpdateDialogue(NextLine);
			}	
		}
	}
}

void UConversationWidget::HideResponses()
{
	for (UButton* Button : ResponseButtons)
	{
		Button->SetVisibility(ESlateVisibility::Hidden);
	}
	PROGRESS_BUTTON->SetVisibility(ESlateVisibility::Visible);
}
