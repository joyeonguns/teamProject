// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "UObject/Class.h"
#include "teamProjectGameModeBase.generated.h"

/**
 * 
 */


UCLASS()
class TEAMPROJECT_API AteamProjectGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	AteamProjectGameModeBase();
	// 블루프린터에서 UI제어 가능
	UFUNCTION(BlueprintCallable, Category = "UMG_Game")
		void ChangeMenuWidget(TSubclassOf<UUserWidget> NewWidgetClass);

	UFUNCTION(BlueprintCallable, Category = "UMG_Game")
		void ChangeSideWidget(TSubclassOf<UUserWidget> NewWidgetClass);
	

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = "UMG_Game")
		TSubclassOf<UUserWidget> StartingWidgetClass;
	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = "UMG_Game")
		TSubclassOf<UUserWidget> InGameWidgetClass;
	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = "UMG_Game")
		TSubclassOf<UUserWidget> DeadWidgetClass;
	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = "UMG_Game")
		TSubclassOf<UUserWidget> SkillTreeWidgetClass;
	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = "UMG_Game")
		TSubclassOf<UUserWidget> InGameMenuClass;

	UPROPERTY()
		UUserWidget* CurrentWidget;
	UPROPERTY()
		UUserWidget* SideWidget;

public:
	TSubclassOf<UUserWidget> GetInGameWidget();
	TSubclassOf<UUserWidget> GetDeadWidget();
	TSubclassOf<UUserWidget> GetStartingWidgetWidget();
	TSubclassOf<UUserWidget> GetSkillTreeWidgetWidget();
	TSubclassOf<UUserWidget> GetInGameMenu();
	
	int32 index = 0;

	// 게임 저장, 로드
	void SaveGame();
	void LoadGame();
};
