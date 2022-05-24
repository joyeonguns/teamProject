// Fill out your copyright notice in the Description page of Project Settings.


#include "BTS_LookAt.h"
#include "EnemyCharacter.h"
#include "Kismet/KismetMathLibrary.h"
#include "Enemy_AIController.h"
#include "GameFramework/Character.h"

UBTS_LookAt::UBTS_LookAt()
{
	bNotifyBecomeRelevant = true;
	NodeName = TEXT("LookAt");
}


void UBTS_LookAt::OnBecomeRelevant(UBehaviorTreeComponent& owner_comp, uint8* node_memory)
{
	Super::OnBecomeRelevant(owner_comp, node_memory);
	auto const cont = owner_comp.GetAIOwner();
	AEnemyCharacter* const npcEnemy = Cast<AEnemyCharacter>(cont);
	FRotator rotation = UKismetMathLibrary::FindLookAtRotation(npcEnemy->GetActorLocation(), LookAtPoint);
	npcEnemy->SetActorRotation(rotation);
}

FString UBTS_LookAt::GetStaticServiceDescription() const
{
	return FString("Change LookAt Point");
}
