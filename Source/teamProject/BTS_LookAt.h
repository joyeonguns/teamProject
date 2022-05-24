// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTS_LookAt.generated.h"

/**
 * 
 */
UCLASS()
class TEAMPROJECT_API UBTS_LookAt : public UBTService_BlackboardBase
{
	GENERATED_BODY()
	
public :
	UBTS_LookAt();
	void OnBecomeRelevant(UBehaviorTreeComponent& owner_comp, uint8* node_memory) override;

protected:
	// 설명 가져오기
	FString GetStaticServiceDescription() const;

private:
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
		FVector LookAtPoint = { 0,0,0 };
};
