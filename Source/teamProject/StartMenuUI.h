// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "StartMenuUI.generated.h"

/**
 * 
 */
UCLASS()
class TEAMPROJECT_API UStartMenuUI : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void NativeConstruct() override;
	
	// ���۹�ư
	UFUNCTION()
	void Btn_StartGame();
	// ������ ��ư
	UFUNCTION()
	void Btn_ExitGame();

	UFUNCTION()
		void Btn_LoadGame();

protected:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UButton* Btn_Start;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UButton* Btn_Exit;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UButton* Btn_Load;
};
