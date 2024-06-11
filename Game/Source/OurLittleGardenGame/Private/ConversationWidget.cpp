// Fill out your copyright notice in the Description page of Project Settings.


#include "ConversationWidget.h"
#include "Components/TextBlock.h"

void UConversationWidget::UpdateContentText(FName Name, FString Content)
{
	NAME_TEXT->SetText(FText::FromName(Name));
	CONTENT_TEXT->SetText(FText::FromString(Content));
}
