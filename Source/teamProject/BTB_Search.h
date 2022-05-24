// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BehaviorTree/BTTaskNode.h"
#include "GameFramework/Pawn.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "UObject/UObjectGlobals.h"
#include "BTB_Search.generated.h"

/**
 * 
 */
UCLASS()
class TEAMPROJECT_API UBTB_Search : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	
public:
	UBTB_Search(FObjectInitializer const& object_initializer);
	// ExecuteTask() 함수는 Aborted Failed Succeeded InProgress 반환값을가짐
	// Aborted : 테스크 실행 중단 -> 실패
	// Failed : 실패
	// Succeeded : 성공
	// InProgress : 결과를 나중에 알려줌
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& Ownercomp, uint8* NodeMemory) override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Search", meta = (AllowPrivateAccess = "true"));
	float search_radious = 550.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Search", meta = (AllowPrivateAccess = "true"));
	bool search_mode = true;

	FVector destination;
};
