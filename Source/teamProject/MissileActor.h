// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlayerCharacter.h"
#include "EnemyCharacter.h"
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
	// �θ�Ŭ������ �Լ� ������Ʈ �浹�� �Լ� ȣ�� 
	/*virtual void NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* otherComp, bool bSelfMoved,
		FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit) override;*/
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	virtual void NotifyActorEndOverlap(AActor* OtherActor) override;


public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	// UPROPERTY�� Public ������ �ȿ��� ����Ͽ��� �Ѵ�.
	UPROPERTY(EditAnywhere)
		// ������Ʈ�� �޽������� ���� ��� ����
		UStaticMeshComponent* BoxMesh;

	// destination�� �ʱ�ȭ
	void SetParameter(FVector des, FName tag,float Damage);

	//AEnemyCharacter* Enemy;

	// ������
	float damage = 20.0f;


private:
	// ��������
	FVector destination = { 100,100,100 };
	// �̵� ����
	FVector direction;

	FName tagName;

	float speed = 1000.0f;

	float impulsePower = 200.f;

	// �̻��� �̵�
	void MoveMissile(float Deltatime);

};