// Fill out your copyright notice in the Description page of Project Settings.


#include "InGameUI.h"
#include "Kismet/GameplayStatics.h"
#include "teamProjectGameModeBase.h"
#include "ClickPlayerController.h"


void UInGameUI::NativeConstruct()
{
	if (Btn_Return) {
		Btn_Return->OnClicked.AddDynamic(this, &UInGameUI::ReturnClick);
	}
	if (Btn_Exit) {
		Btn_Exit->OnClicked.AddDynamic(this, &UInGameUI::ExitClick);
	}
	if (Btn_Setting) {
		Btn_Setting->OnClicked.AddDynamic(this, &UInGameUI::SettingClick);
	}
	if (Btn_End) {
		Btn_End->OnClicked.AddDynamic(this, &UInGameUI::EndClick);
	}
	if (Btn_Cancle) {
		Btn_Cancle->OnClicked.AddDynamic(this, &UInGameUI::CancleClick);
	}
	Exit_Panel->SetVisibility(ESlateVisibility::Hidden);
}

void UInGameUI::ReturnClick()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("ExitMenu")));
	auto gameMode = Cast<AteamProjectGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	//auto Player = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (gameMode) {
		gameMode->ChangeSideWidget(nullptr);
		//Player->I_PlayerState = EPlayerState::PlayerPoss;
	}
	auto p_Cont = Cast<AClickPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	p_Cont->SetPause(false);
}

void UInGameUI::SettingClick()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("SettingClick")));
}
void UInGameUI::ExitClick()
{
	Exit_Panel->SetVisibility(ESlateVisibility::Visible);
	HorizontalBox_0->SetVisibility(ESlateVisibility::Hidden);
}

void UInGameUI::EndClick()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Exit")));
	GetWorld()->GetFirstLocalPlayerFromController()->ConsoleCommand("quit");
}

void UInGameUI::CancleClick()
{
	Exit_Panel->SetVisibility(ESlateVisibility::Hidden);
	HorizontalBox_0->SetVisibility(ESlateVisibility::Visible);
}
