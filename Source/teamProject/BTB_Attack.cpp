// Fill out your copyright notice in the Description page of Project Settings.


#include "BTB_Attack.h"
#include "BehaviorTree/BTNode.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BlackboardData.h"
#include "Enemy_AIController.h"
#include "NavigationSystem.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "Kismet/KismetMathLibrary.h"

UBTB_Attack::UBTB_Attack(FObjectInitializer const& object_initializer)
{
	NodeName = TEXT("Attack");
}

EBTNodeResult::Type UBTB_Attack::ExecuteTask(UBehaviorTreeComponent& Ownercomp, uint8* NodeMemory)
{

	ACharacter* const player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	FVector p_Location = player->GetActorLocation();
	// cont에 비헤이비어 트리를 저장, npc 에 ai를 따르는 폰 저장
	auto cont = Cast<AEnemy_AIController>(Ownercomp.GetAIOwner());
	auto const npc = cont->GetPawn();

	FVector const origin = npc->GetActorLocation();

	FVector const player_location = cont->get_blackboard()->GetValueAsVector("PlayerLocation");

	ProjectileClass = cont->ProjetileClass;

	FRotator spwRotator = { 0,0,0 };
	UWorld* world = GetWorld();

	//FRotator LookRot = UKismetMathLibrary::FindLookAtRotation(npc->GetActorLocation(), player_location);
	FRotator LookRot = UKismetMathLibrary::FindLookAtRotation(npc->GetActorLocation(), p_Location);
	npc->SetActorRotation(LookRot);			

	//if (search_mode)
	//{
	//	// 네비 로케이션과 네비시스템V1 초기화
	//	FNavLocation loc;
	//	UNavigationSystemV1* const nav_sys = UNavigationSystemV1::GetCurrent(GetWorld());

	//	if (nav_sys->GetRandomPointInNavigableRadius(player_location, search_radious, loc, nullptr))
	//	{
	//		destination = loc.Location;
	//		//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, "Set DES");
	//	}
	//}
	
	//destination = player_location;
	destination = p_Location;
	if (world) {
		FActorSpawnParameters spwPatameter;
		spwPatameter.Owner = cont;
		spwPatameter.Instigator = cont->GetInstigator();
		FVector dir = (destination - npc->GetActorLocation()).GetSafeNormal();
		FVector spwLocation = npc->GetActorLocation() + dir * 50;

		AMissileActor* Projectile = world->SpawnActor<AMissileActor>(ProjectileClass, spwLocation, spwRotator, spwPatameter);
		if (Projectile) {
			FName tag = TEXT("Player");
			Projectile->SetParameter(destination, tag, 10.f);
		}
	}

	FinishLatentTask(Ownercomp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Type();
}
