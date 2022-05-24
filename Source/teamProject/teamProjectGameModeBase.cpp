// Copyright Epic Games, Inc. All Rights Reserved.


#include "teamProjectGameModeBase.h"
#include "Blueprint/UserWidget.h"
#include "StartMenuHUD.h"
#include "testGameInstance.h"
#include "testSaveGame.h"
#include "Kismet/GameplayStatics.h"

AteamProjectGameModeBase::AteamProjectGameModeBase()
{
	HUDClass = AStartMenuHUD::StaticClass();
	DefaultPawnClass = nullptr;
	
}


void AteamProjectGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	UWorld* curWorld = GetWorld();
	UtestGameInstance* GI = Cast<UtestGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (GI) {
		if (curWorld->GetMapName() == FString("UEDPIE_0_1_StartMenu"))
		{
			ChangeMenuWidget(StartingWidgetClass);
			index = 2;
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Index : %d"), index));
		}
		if (GI->I_GameState == EGameState::GamePlay)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("game start")));
			ChangeMenuWidget(InGameWidgetClass);
		}
	}
}

TSubclassOf<UUserWidget> AteamProjectGameModeBase::GetInGameWidget()
{
	return InGameWidgetClass;
}

TSubclassOf<UUserWidget> AteamProjectGameModeBase::GetDeadWidget()
{
	return DeadWidgetClass;
}

TSubclassOf<UUserWidget> AteamProjectGameModeBase::GetStartingWidgetWidget()
{
	return StartingWidgetClass;
}

TSubclassOf<UUserWidget> AteamProjectGameModeBase::GetSkillTreeWidgetWidget()
{
	return SkillTreeWidgetClass;
}

TSubclassOf<UUserWidget> AteamProjectGameModeBase::GetInGameMenu()
{
	return InGameMenuClass;
}

void AteamProjectGameModeBase::SaveGame()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT(" Save game "));

	UtestSaveGame* SaveGameInstance = Cast<UtestSaveGame>(UGameplayStatics::CreateSaveGameObject(UtestSaveGame::StaticClass()));
	if (SaveGameInstance) {
		// Savefile Data
		SaveGameInstance->SaveSlotName = "SaveGame_1";
		SaveGameInstance->SaveIndex = 0;

		// Save Data
		SaveGameInstance->SaveName = "p_0";
		SaveGameInstance->SaveFloat = 11.f;

		SaveGameInstance->SaveStruct.StructInteger = 255;
		SaveGameInstance->SaveTArray.Add(1);
		
		SaveGameInstance->SaveTransform = FTransform(FVector(0,0,118));		
	}
	else {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT(" SaveInstance is null "));
	}
	UGameplayStatics::SaveGameToSlot(SaveGameInstance, SaveGameInstance->SaveSlotName, SaveGameInstance->SaveIndex);
}

void AteamProjectGameModeBase::LoadGame()
{
	//SaveGame();
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT(" Load game "));

	UtestSaveGame* LoadGameInstance = Cast<UtestSaveGame>(UGameplayStatics::CreateSaveGameObject(UtestSaveGame::StaticClass()));
	if (LoadGameInstance)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Black, TEXT(" Find Load "));
		LoadGameInstance->SaveSlotName = "SaveGame_1";
		LoadGameInstance->SaveIndex = 0;

		LoadGameInstance = Cast<UtestSaveGame>(UGameplayStatics::LoadGameFromSlot(LoadGameInstance->SaveSlotName, LoadGameInstance->SaveIndex));
	
		if (LoadGameInstance) {
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Black, FString::Printf(TEXT("SaveName : %s"), *LoadGameInstance->SaveName.ToString()));
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Black, FString::Printf(TEXT("Savefloat : %f"), LoadGameInstance->SaveFloat));
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Black, FString::Printf(TEXT("SaveTransform : %s"), *LoadGameInstance->SaveTransform.ToString()));
		}
		else {
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Black, FString::Printf(TEXT("Load Null")));
		}
		
	}
	else {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Black, FString::Printf(TEXT("Load Null!!")));
	}
}

void AteamProjectGameModeBase::ChangeMenuWidget(TSubclassOf<UUserWidget> NewWidgetClass)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Change Widget")));
	if (CurrentWidget != nullptr) {
		CurrentWidget->RemoveFromViewport();
		CurrentWidget = nullptr;
	}

	if (NewWidgetClass != nullptr) {
		CurrentWidget = CreateWidget(GetWorld(), NewWidgetClass);
		if (CurrentWidget != nullptr) {
			CurrentWidget->AddToViewport();
		}
	}
}

void AteamProjectGameModeBase::ChangeSideWidget(TSubclassOf<UUserWidget> NewWidgetClass)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Change side Widget")));
	if (SideWidget != nullptr) {
		SideWidget->RemoveFromViewport();
		SideWidget = nullptr;
	}

	if (NewWidgetClass != nullptr) {
		SideWidget = CreateWidget(GetWorld(), NewWidgetClass);
		if (SideWidget != nullptr) {
			SideWidget->AddToViewport();
		}
	}
}



