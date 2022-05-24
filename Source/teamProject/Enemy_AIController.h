// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionTypes.h"
#include "MissileActor.h"
#include "Enemy_AIController.generated.h"

/**
 * 
 */
UCLASS()
class TEAMPROJECT_API AEnemy_AIController : public AAIController
{
	GENERATED_BODY()
	
public:
	AEnemy_AIController();
	// 컨트롤러 빙의
	virtual void OnPossess(APawn* InPawn) override;
	virtual void Tick(float deltaTime) override;


	void RunAI();
	void StopAI();

	
	static const FName PatrollPos1;
	static const FName PatrollPos2;

	UBlackboardComponent* get_blackboard();

	UFUNCTION()
		void OnPawnDetected(const TArray<AActor*>& DetectedPawns);

private:
	UPROPERTY()
		class UBehaviorTree* BTAsset;
	UPROPERTY()
		class UBlackboardData* BBAsset;
	

public:

	// 시각센서
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = AI)
		float AISightRadious = 500.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = AI)
		float AISightAge = 5.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = AI)
		float AILosesSightRadius = AISightRadious + 50.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = AI)
		float AIFieldOfView = 90.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = AI)
		class UAISenseConfig_Sight* SightConfig;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = AI)
		bool bIsPlayerDetected = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = AI)
		float DistanceToPlayer = 0.0f;

	UFUNCTION(BlueprintCallable, Category = Behavior)
		void OnTarget_Detected(AActor* actor, FAIStimulus const stimulus);

	//// 페트롤 좌표
	//UPROPERTY(EditDefaultsOnly, Category = "P_Location")
	//FVector pos1 = { 700,-1000,118 };
	//UPROPERTY(EditDefaultsOnly, Category = "P_Location")
	//FVector pos2 = { -700,-1000,118 };
	// AI 시각정보 설정
	void setAIPerception();

	// 공격
	void Attack();

	// 프로젝타일 서브오브젝트
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AMissileActor> ProjetileClass;

	//
	
};
