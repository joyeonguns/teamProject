// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/CanvasPanel.h"
#include "SkillTreeUI.generated.h"

/**
 * 
 */
UCLASS()
class TEAMPROJECT_API USkillTreeUI : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void NativeConstruct() override;
	
	UFUNCTION()
		void ExitClick();
	UFUNCTION()
		void SaveClick();
	UFUNCTION()
		void OkClick_Save();
	UFUNCTION()
		void OkClick_Exit();
	UFUNCTION()
		void XClick();

	UFUNCTION()
		void UpSkill1Click();
	UFUNCTION()
		void DownSkill1Click();

	void Set_skill1LvL(int32 lvl);

	void Set_CurMoney(int32 Money);

	int32 Lv_skill = 0;
	int32 UIMoney = 0;

protected:
	// 버튼
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UButton* Btn_UpSkill1;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UButton* Btn_DownSkill1;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UButton* Btn_Exit;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UButton* Btn_Save;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UButton* Btn_Ok;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UButton* Btn_X;
	
	// 텍스트
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UTextBlock* Skill1LvL = nullptr;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UTextBlock* Check_Text = nullptr;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UTextBlock* CurMoney = nullptr;

	// 캔버스 패널
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UCanvasPanel* MainPanel;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UCanvasPanel* Check_Panel;


};
