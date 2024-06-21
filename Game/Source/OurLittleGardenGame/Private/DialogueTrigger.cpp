// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogueTrigger.h"

// Add default functionality here for any IDialogueTrigger functions that are not pure virtual.

FName IDialogueTrigger::GetResponseDialogue(int ResponseOption)
{
	return FName();
}

bool IDialogueTrigger::UpdateDialogue(FName Name)
{
	return false;
}

FName IDialogueTrigger::GetNextLine()
{
	return FName();
}
