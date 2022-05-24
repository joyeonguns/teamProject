// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "testSaveGame.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FStructSaveGame {
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SaveData")
		int32 StructInteger;
};

UCLASS()
class TEAMPROJECT_API UtestSaveGame : public USaveGame
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SaveData")
		FString SaveSlotName;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SaveData")
		int32 SaveIndex;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SaveData")
		FStructSaveGame SaveStruct;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SaveData")
		TArray<int32> SaveTArray;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SaveData")
		FName SaveName;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SaveData")
		FTransform SaveTransform;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SaveData")
		float SaveFloat;
};
