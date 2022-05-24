// Fill out your copyright notice in the Description page of Project Settings.


#include "testWidget.h"
#include "Kismet/GameplayStatics.h"
#include "teamProjectGameModeBase.h"
#include <Components/Button.h>

void UtestWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (TestButton) {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("TestButton")));
		TestButton = Cast<UButton>(GetWidgetFromName(TEXT("TestButton")));
		
		//TestButton->OnClicked.AddDynamic(this, &UtestWidget::TestButtonClick);
	}
}

void UtestWidget::TestButtonClick()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("ButtonClick")));
}
