// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlayerCharacter.h"
#include "EnemyCharacter.h"
#include "icePlate_Actor.h"
#include "MissileActor.generated.h"

UCLASS()
class TEAMPROJECT_API AMissileActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMissileActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	// 부모클래스의 함수 오브젝트 충돌시 함수 호출 
	/*virtual void NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* otherComp, bool bSelfMoved,
		FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit) override;*/
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	virtual void NotifyActorEndOverlap(AActor* OtherActor) override;


public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	// UPROPERTY는 Public 제한자 안에서 사용하여야 한다.
	UPROPERTY(EditAnywhere)
		// 오브젝트의 메쉬설정을 위한 멤버 변수
		UStaticMeshComponent* BoxMesh;

	// destination을 초기화
	void SetParameter(FVector des, FName tag,float Damage);


	// 데미지
	float damage = 20.0f;	
	// 탄 속성
	FString Element = "ice";
	// 속성탄 확률 
	int32 Sp_Rate = 30;


	// 탄 머티리얼
	 
	// 기본 머티리얼
	UPROPERTY(EditAnywhere)
		class UMaterial* nomal_Material;
	// ice material
	UPROPERTY(EditAnywhere)
		class UMaterial* ice_Material;
	// 중독 머티리얼
	UPROPERTY(EditAnywhere)
		class UMaterial* poison_Material;

	// 장판 소환
	UPROPERTY(EditAnywhere)
		TSubclassOf<AicePlate_Actor> iceFloor;

	UPROPERTY(EditAnywhere)
		TSubclassOf<AicePlate_Actor> PoisonFloor;

	void SpwFloor();
	
	


private:
	// 목적지점
	FVector destination = { 100,100,100 };
	// 이동 방향
	FVector direction;

	FName tagName;

	float speed = 1000.0f;

	float impulsePower = 200.f;

	// 미사일 이동
	void MoveMissile(float Deltatime);

};
