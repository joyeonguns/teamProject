// Fill out your copyright notice in the Description page of Project Settings.


#include "MissileActor.h"
#include "Engine/Classes/Components/StaticMeshComponent.h"
#include "Components/PrimitiveComponent.h"
#include "GameplayTagContainer.h"
#include "Engine.h"

// Sets default values
AMissileActor::AMissileActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// BoxMesh�� �⺻���� �����Ǵ� �ڽ��޽� �Ҵ�
	BoxMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BoxMesh"));
	RootComponent = BoxMesh;
}

// Called when the game starts or when spawned
void AMissileActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void AMissileActor::NotifyActorBeginOverlap(AActor* OtherActor)
{
	FName name = "Enemy";
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, TEXT("NotifyActorBeginOverlap"));

	
	if (OtherActor->ActorHasTag(tagName)) {
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, name.ToString());

		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, TEXT("Attack!!"));
		UGameplayStatics::ApplyDamage(OtherActor, damage, NULL, this, UDamageType::StaticClass());
		//Enemy = Cast<AEnemyCharacter>(OtherActor);

		Destroy();
	}
}

void AMissileActor::NotifyActorEndOverlap(AActor* OtherActor)
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, TEXT("NotifyOverlapEnd"));
}

// Called every frame
void AMissileActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	MoveMissile(DeltaTime);
}

void AMissileActor::SetParameter(FVector des, FName tag, float Damage)
{
	// ��ġ
	destination = { des.X, des.Y, this->GetActorLocation().Z };
	direction = (destination - this->GetActorLocation()).GetSafeNormal();
	destination = direction * 800 + GetActorLocation();

	// �±�
	tagName = tag;
	damage = Damage;
}

void AMissileActor::MoveMissile(float Deltatime)
{
	FVector curLoc = this->GetActorLocation();
	float distance = FVector::Dist(curLoc, destination);
	// ���������� �����ϸ� ������Ʈ �ı�
	if (distance > 10.0f)
	{
		// �����Ӵ� Deltatime * �ӵ� ��ŭ �߰�
		curLoc += direction * speed * Deltatime;
		SetActorLocation(curLoc);
	}
	else {
		Destroy();
	}
}

