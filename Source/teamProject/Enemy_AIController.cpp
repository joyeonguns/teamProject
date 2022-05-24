// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy_AIController.h"
#include "EnemyCharacter.h"
#include "PlayerCharacter.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"

const FName AEnemy_AIController::PatrollPos1(TEXT("PLocation_1"));
const FName AEnemy_AIController::PatrollPos2(TEXT("PLocation_2"));

AEnemy_AIController::AEnemy_AIController()
{
	PrimaryActorTick.bCanEverTick = true;
	setAIPerception();

	// FObjectFinder를 이용해 ASSET의 오브젝트를 가져옴
	static ConstructorHelpers::FObjectFinder<UBlackboardData> BBObject(TEXT("/Game/AI/BB_Enemy.BB_Enemy"));
	if (BBObject.Succeeded())
	{
		BBAsset = BBObject.Object;
	}
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BTObject(TEXT("BehaviorTree'/Game/AI/BT_Enemy.BT_Enemy'"));
	if (BTObject.Succeeded())
	{
		BTAsset = BTObject.Object;
	}
}

void AEnemy_AIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	if (UseBlackboard(BBAsset, Blackboard))
	{
		AEnemyCharacter* npc = Cast<AEnemyCharacter>(InPawn);
		Blackboard->SetValueAsVector(PatrollPos1, npc->Pos1);
		Blackboard->SetValueAsVector(PatrollPos2, npc->Pos2);
		RunBehaviorTree(BTAsset);
	}
}

void AEnemy_AIController::Tick(float deltaTime)
{
	Super::Tick(deltaTime);

}

void AEnemy_AIController::RunAI()
{
	if (UseBlackboard(BBAsset, Blackboard))
	{
		//Blackboard->SetValueAsVector(PatrollPos1,Inpawn)
		RunBehaviorTree(BTAsset);
	}
}

void AEnemy_AIController::StopAI()
{
	UBehaviorTreeComponent* BehaviorTreeComponent = Cast<UBehaviorTreeComponent>(BrainComponent);
	if (nullptr == BehaviorTreeComponent) return;

	BehaviorTreeComponent->StopTree(EBTStopMode::Safe);
}

UBlackboardComponent* AEnemy_AIController::get_blackboard()
{
	return Blackboard;
}

void AEnemy_AIController::OnPawnDetected(const TArray<AActor*>& DetectedPawns)
{
}

void AEnemy_AIController::OnTarget_Detected(AActor* actor, FAIStimulus const stimulus)
{
	if (auto const ch = Cast<APlayerCharacter>(actor))
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, "Find Player!!!");
		Blackboard->SetValueAsBool("see?", true);

		/*ACharacter* const player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
		Blackboard->SetValueAsVector("Destination", player->GetActorLocation());*/
	}
}

void AEnemy_AIController::setAIPerception()
{
	// AiSense클래스 초기화, Perception AI 세팅
	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Config"));
	SetPerceptionComponent(*CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("Perception Component")));

	SightConfig->SightRadius = AISightRadious;
	SightConfig->LoseSightRadius = AILosesSightRadius;
	SightConfig->PeripheralVisionAngleDegrees = AIFieldOfView;
	SightConfig->SetMaxAge(AISightAge);

	SightConfig->DetectionByAffiliation.bDetectEnemies = true;
	SightConfig->DetectionByAffiliation.bDetectFriendlies = true;
	SightConfig->DetectionByAffiliation.bDetectNeutrals = true;

	GetPerceptionComponent()->SetDominantSense(*SightConfig->GetSenseImplementation());
	GetPerceptionComponent()->OnTargetPerceptionUpdated.AddDynamic(this, &AEnemy_AIController::OnTarget_Detected);
	GetPerceptionComponent()->ConfigureSense(*SightConfig);
}

void AEnemy_AIController::Attack()
{
	
}
