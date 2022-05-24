// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "testWidget.generated.h"

/**
 * 
 */
UCLASS()
class TEAMPROJECT_API UtestWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void NativeConstruct() override;

	// 시작버튼
	void TestButtonClick();

protected:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UButton* TestButton;
	
};
