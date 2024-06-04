// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterEnumeration.h"

UENUM(BlueprintType)
enum class ECharacter : uint8
{
	CHEF UMETA(DisplayName = "Chef"),
	FLORIST UMETA(DisplayName = "Florist"),
	MAILMAN UMETA(DisplayName = "Mailman")

};

UENUM(BlueprintType)
enum class EEmotion : uint8
{
	HAPPY,
	SAD,
	ANGRY

};

CharacterEnumeration::CharacterEnumeration()
{
}

CharacterEnumeration::~CharacterEnumeration()
{
}
