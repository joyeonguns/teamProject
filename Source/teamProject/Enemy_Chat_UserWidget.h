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
	// UI를 사용하기 위해 필요한 함수 생성자와 비슷한 역할
	void NativeConstruct() override;
	// 문자열을 바꿔줄 함수
	void Set_EnemyChat(FString const str);

protected:
	// 블루프린트와 연결하기위해 UPROPERTY에 meta = (BindWidget) 설정
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UTextBlock* EnemyChat = nullptr;
};
