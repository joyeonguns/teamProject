// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "testGameInstance.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class EGameState :uint8
{
	GameStart UMETA(DisplayName = "GameStart"),
	GamePlay UMETA(DisplayName = "GamePlay"),
	GamePause UMETA(DisplayName = "GamePause"),
	GameOver UMETA(DisplayName = "GameOver"),
};
struct FGunInfo;
class UDataTable;
UCLASS()
class TEAMPROJECT_API UtestGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UtestGameInstance();

	UDataTable* GunDataTable;

	FGunInfo* GunDataTableInstance(int32 num);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EGameState I_GameState = EGameState::GameStart;
};
