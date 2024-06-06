// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterEnumeration.generated.h"

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

USTRUCT(BlueprintType)
struct FResponse
{
	GENERATED_USTRUCT_BODY()

	// Name/ID used to refer to this specific response
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName Name;

	// Text to be displayed in text box
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Content;

	// The line to play after selecting this response
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName NextLine;


	//UPROPERTY()
};

USTRUCT(BlueprintType)
struct FDialogueLine : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	// Name/ID used to refer to this specific response
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName Name;

	// Text to be displayed in text box
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Content;

	// The character who's speaking this line of dialogue
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ECharacter CharacterSpeaking;

	// The emotion/pose of the character currently speaking
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EEmotion CharacterEmotion;

	// Can the player respond to this line of dialogue?
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bRespondable;

	// The possible responses to this line
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FResponse> Responses;

	// The line to display after this one, leave blank to end conversation
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName NextLine;


	//UPROPERTY()
};

/**
 * 
 */
class OURLITTLEGARDENGAME_API CharacterEnumeration
{
public:
	CharacterEnumeration();
	~CharacterEnumeration();
};
