// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy_Chat_UserWidget.h"

void UEnemy_Chat_UserWidget::NativeConstruct()
{
}

void UEnemy_Chat_UserWidget::Set_EnemyChat(FString const str)
{
	EnemyChat->SetText(FText::FromString(str));
}
