// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SkillTreePoint.generated.h"

UCLASS()
class TEAMPROJECT_API ASkillTreePoint : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASkillTreePoint();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		class USphereComponent* CollisionSphere;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		UStaticMeshComponent* PointMesh;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlapedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlapedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	bool bOverlap;

};
