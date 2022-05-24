// Fill out your copyright notice in the Description page of Project Settings.


#include "BTB_AttackRelease.h"
#include "BehaviorTree/BTNode.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BlackboardData.h"
#include "Enemy_AIController.h"
#include "NavigationSystem.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "Kismet/KismetMathLibrary.h"

UBTB_AttackRelease::UBTB_AttackRelease(FObjectInitializer const& object_initializer)
{
	NodeName = TEXT("AttackFalse");
}

EBTNodeResult::Type UBTB_AttackRelease::ExecuteTask(UBehaviorTreeComponent& Ownercomp, uint8* NodeMemory)
{
	// cont�� �����̺�� Ʈ���� ����, npc �� ai�� ������ �� ����
	auto cont = Cast<AEnemy_AIController>(Ownercomp.GetAIOwner());
	auto const npc = cont->GetPawn();

	cont->get_blackboard()->SetValueAsBool("Attack?",false);
	
	FinishLatentTask(Ownercomp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Type();
}
