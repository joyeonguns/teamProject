// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Enemy_Chat_UserWidget.generated.h"

/**
 * 
 */
UCLASS()
class TEAMPROJECT_API UEnemy_Chat_UserWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	// UI�� ����ϱ� ���� �ʿ��� �Լ� �����ڿ� ����� ����
	void NativeConstruct() override;
	// ���ڿ��� �ٲ��� �Լ�
	void Set_EnemyChat(FString const str);

protected:
	// �������Ʈ�� �����ϱ����� UPROPERTY�� meta = (BindWidget) ����
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UTextBlock* EnemyChat = nullptr;
};
