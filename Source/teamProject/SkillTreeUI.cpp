// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillTreeUI.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "teamProjectGameModeBase.h"
#include "PlayerCharacter.h"

void USkillTreeUI::NativeConstruct()
{
	Super::NativeConstruct();

	if (Btn_Exit) {
		Btn_Exit = Cast<UButton>(GetWidgetFromName(TEXT("Btn_Exit")));
		Btn_Exit->OnClicked.AddDynamic(this, &USkillTreeUI::ExitClick);
	}
	if (Btn_UpSkill1) {
		Btn_UpSkill1->OnClicked.AddDynamic(this, &USkillTreeUI::UpSkill1Click);
	}
	if (Btn_DownSkill1) {
		Btn_DownSkill1->OnClicked.AddDynamic(this, &USkillTreeUI::DownSkill1Click);
	}

	if (Btn_Save) {
		Btn_Save->OnClicked.AddDynamic(this, &USkillTreeUI::SaveClick);
	}
	
	if (Btn_X) {
		Btn_X->OnClicked.AddDynamic(this, &USkillTreeUI::XClick);
	}
	Check_Panel->SetVisibility(ESlateVisibility::Hidden);
	MainPanel->SetVisibility(ESlateVisibility::Visible);
	auto Player = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	Lv_skill = Player->s1_level;
	Skill1LvL->SetText(FText::FromString(FString::FromInt(Lv_skill)));
	Set_CurMoney(Player->CurGold);
	Set_skill1LvL(0);
}

void USkillTreeUI::ExitClick()
{
	// 나가기
	if (Btn_Ok) {
		Btn_Ok->OnClicked.AddDynamic(this, &USkillTreeUI::OkClick_Exit);
	}
	Check_Text->SetText(FText::FromString(" EXIT ?"));
	Check_Panel->SetVisibility(ESlateVisibility::Visible);
	MainPanel->SetVisibility(ESlateVisibility::Hidden);
}

void USkillTreeUI::SaveClick()
{
	// 저장
	if (Btn_Ok) {
		Btn_Ok->OnClicked.AddDynamic(this, &USkillTreeUI::OkClick_Save);
	}
	Check_Text->SetText(FText::FromString("Save ?"));
	Check_Panel->SetVisibility(ESlateVisibility::Visible);
	MainPanel->SetVisibility(ESlateVisibility::Hidden);
}

void USkillTreeUI::OkClick_Save()
{
	// 저장
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Save")));
	auto gameMode = Cast<AteamProjectGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	auto Player = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	Player->s1_level = Lv_skill;
	Player->CurGold = UIMoney;
	Player->SetSkill();
	if (gameMode) {
		gameMode->ChangeSideWidget(nullptr);
		Player->I_PlayerState = EPlayerState::PlayerPoss;
		gameMode->SaveGame();
	}
}

void USkillTreeUI::OkClick_Exit()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("ExitMenu")));
	auto gameMode = Cast<AteamProjectGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	auto Player = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (gameMode) {
		gameMode->ChangeSideWidget(nullptr);
		Player->I_PlayerState = EPlayerState::PlayerPoss;
	}
}

void USkillTreeUI::XClick()
{
	Check_Panel->SetVisibility(ESlateVisibility::Visible);
	MainPanel->SetVisibility(ESlateVisibility::Hidden);
}

void USkillTreeUI::UpSkill1Click()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Up Skill 1")));
	Set_skill1LvL(1);
}

void USkillTreeUI::DownSkill1Click()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Down Skill 1")));
	Set_skill1LvL(-1);
}

void USkillTreeUI::Set_skill1LvL(int32 lvl)
{
	if (lvl == 1 && Lv_skill < 5) {
		Lv_skill++;
		Set_CurMoney(UIMoney - 100 * Lv_skill);
	}
	else if (lvl == -1 && Lv_skill > 0) {
		Set_CurMoney(UIMoney + 100 * Lv_skill);
		Lv_skill--;
	}
	
	Skill1LvL->SetText(FText::FromString(FString::FromInt(Lv_skill)));


	if (Lv_skill == 5 || UIMoney < (Lv_skill+1) *100) {
		FLinearColor _textColor = { 1,1,1,0.5 };
		FLinearColor _bgColor = { 1,1,1,0.5 };
		Btn_UpSkill1->SetColorAndOpacity(_textColor);
		Btn_UpSkill1->SetBackgroundColor(_bgColor);
		Btn_UpSkill1->SetIsEnabled(false);
	}
	else if (Lv_skill == 0) {
		FLinearColor _textColor = { 1,1,1,0.5 };
		FLinearColor _bgColor = { 1,1,1,0.5 };
		Btn_DownSkill1->SetColorAndOpacity(_textColor);
		Btn_DownSkill1->SetBackgroundColor(_bgColor);
		Btn_DownSkill1->SetIsEnabled(false);
	}
	else {

		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT(" Skill 1 ~ 4")));

		FLinearColor textColor = { 1,1,1,1 };
		FLinearColor bgColor = { 1,1,1,1 };
		Btn_UpSkill1->SetColorAndOpacity(textColor);
		Btn_UpSkill1->SetBackgroundColor(bgColor);
		Btn_UpSkill1->SetIsEnabled(true);

		Btn_DownSkill1->SetColorAndOpacity(textColor);
		Btn_DownSkill1->SetBackgroundColor(bgColor);
		Btn_DownSkill1->SetIsEnabled(true);
	}
}

void USkillTreeUI::Set_CurMoney(int32 Money)
{
	UIMoney = Money;

	CurMoney->SetText(FText::FromString(FString::FromInt(UIMoney)));
}
