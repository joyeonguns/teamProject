// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/HorizontalBox.h"
#include "Components/CanvasPanel.h"
#include "InGameUI.generated.h"

/**
 * 
 */
UCLASS()
class TEAMPROJECT_API UInGameUI : public UUserWidget
{
	GENERATED_BODY()
	

public:
	void NativeConstruct() override;

	UFUNCTION()
		void ExitClick();
	UFUNCTION()
		void ReturnClick();
	UFUNCTION()
		void SettingClick();
	UFUNCTION()
		void EndClick();
	UFUNCTION()
		void CancleClick();

protected:

	// 버튼
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UButton* Btn_Return;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UButton* Btn_Exit;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UButton* Btn_Setting;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UButton* Btn_End;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UButton* Btn_Cancle;
	// 패널
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UHorizontalBox* HorizontalBox_0;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UCanvasPanel* Exit_Panel;

};
