// Fill out your copyright notice in the Description page of Project Settings.


#include "StartMenuHUD.h"
#include "UObject/ConstructorHelpers.h"
#include "Runtime/UMG/Public/Blueprint/UserWidget.h"

AStartMenuHUD::AStartMenuHUD()
{
	static ConstructorHelpers::FClassFinder<UUserWidget>ui(TEXT("/Game/UI/StartMenu"));
	if (ui.Succeeded()) {
		uiBPClass = ui.Class;
	}
}

void AStartMenuHUD::BeginPlay()
{
	Super::BeginPlay();
	if (uiBPClass) {
		uiWidget = CreateWidget<UUserWidget>(GetWorld(), uiBPClass);
		// ���� �����ֱ�
		if (uiWidget)
		{
			uiWidget->AddToViewport();
		}
	}
}
