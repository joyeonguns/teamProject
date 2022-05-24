// Fill out your copyright notice in the Description page of Project Settings.


#include "StartMenuUI.h"
#include "Kismet/GameplayStatics.h"
#include "teamProjectGameModeBase.h"
#include "testGameInstance.h"
#include <Components/Button.h>

void UStartMenuUI::NativeConstruct()
{
	Super::NativeConstruct();

	if (Btn_Start) {
		Btn_Start->OnClicked.AddDynamic(this, &UStartMenuUI::Btn_StartGame);
	}
	if (Btn_Exit) {
		Btn_Exit->OnClicked.AddDynamic(this, &UStartMenuUI::Btn_ExitGame);
	}
	if (Btn_Load) {
		Btn_Load->OnClicked.AddDynamic(this, &UStartMenuUI::Btn_LoadGame);
	}
	
	//Btn_ExitGame();
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Hellow")));
}

void UStartMenuUI::Btn_StartGame()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("by")));
	auto gameMode = Cast<AteamProjectGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	if (gameMode) {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("GameMode On")));
		UWorld* curWorld = GetWorld();
		UtestGameInstance* GI = Cast<UtestGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
		if (GI) {
			GI->I_GameState = EGameState::GamePlay;
		}
		//gameMode->ChangeMenuWidget(gameMode->GetInGameWidget());
	}
	UGameplayStatics::OpenLevel(GetWorld(), "/Game/Maps/ClickMoveMap");
}

void UStartMenuUI::Btn_ExitGame()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("ButtonClick")));
	GetWorld()->GetFirstPlayerController()->ConsoleCommand("quit");	
}

void UStartMenuUI::Btn_LoadGame()
{
	auto gameMode = Cast<AteamProjectGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	if (gameMode) {
		gameMode->LoadGame();
	}
}
