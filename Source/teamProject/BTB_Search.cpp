// Fill out your copyright notice in the Description page of Project Settings.


#include "BTB_Search.h"
#include "BehaviorTree/BTNode.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BlackboardData.h"
#include "Enemy_AIController.h"
#include "NavigationSystem.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"


UBTB_Search::UBTB_Search(FObjectInitializer const& object_initializer)
{
	NodeName = TEXT("Find Player");
}

EBTNodeResult::Type UBTB_Search::ExecuteTask(UBehaviorTreeComponent& Ownercomp, uint8* NodeMemory)
{

	// player �� �÷��̾� ����
	ACharacter* const player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	// cont�� �����̺�� Ʈ���� ����, npc �� ai�� ������ �� ����
	auto const cont = Cast<AEnemy_AIController>(Ownercomp.GetAIOwner());
	auto const npc = cont->GetPawn();

	FVector const origin = npc->GetActorLocation();

	FVector const player_location = player->GetActorLocation();

	
	float dist = abs(FVector::Dist(npc->GetActorLocation(), player_location));
	if (dist > 1200) {
		cont->get_blackboard()->SetValueAsBool("See?", false);
	}
	else if (1200 > dist && dist > 500) {
		destination = npc->GetActorLocation() + (player_location - npc->GetActorLocation()).GetSafeNormal() * (dist-400);
		//cont->get_blackboard()->SetValueAsBool("Attack?", false);
	}	
	else {
		destination = npc->GetActorLocation();
		cont->get_blackboard()->SetValueAsBool("Attack?", true);
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, "Attack");
	}

	cont->get_blackboard()->SetValueAsVector("PlayerLocation", player_location);

	if (search_mode)
	{
		// �׺� �����̼ǰ� �׺�ý���V1 �ʱ�ȭ
		FNavLocation loc;
		UNavigationSystemV1* const nav_sys = UNavigationSystemV1::GetCurrent(GetWorld());

		if (nav_sys->GetRandomPointInNavigableRadius(player_location, search_radious, loc, nullptr))
		{
			cont->get_blackboard()->SetValueAsVector("Destination", destination);
			//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, "Set DES");
		}
	}

	//cont->get_blackboard()->SetValueAsBool("Attack?", false);

	FinishLatentTask(Ownercomp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Type();
}
