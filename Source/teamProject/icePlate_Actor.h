// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemyCharacter.h"
#include "icePlate_Actor.generated.h"

UCLASS()
class TEAMPROJECT_API AicePlate_Actor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AicePlate_Actor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	virtual void NotifyActorEndOverlap(AActor* OtherActor) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// 오브젝트의 메쉬설정을 위한 멤버 변수
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* CylinderMesh;

	float time = 13.0f;
	float curTime;
	
	void Frozen(AActor* OtherActor);
	void timer(float DeltaTime);

};
