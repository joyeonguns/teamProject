// Fill out your copyright notice in the Description page of Project Settings.


#include "MissileActor.h"
#include "Engine/Classes/Components/StaticMeshComponent.h"
#include "Components/PrimitiveComponent.h"
#include "GameplayTagContainer.h"
#include "Engine.h"
#include "Math/UnrealMathUtility.h"

// Sets default values
AMissileActor::AMissileActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// BoxMesh�� �⺻���� �����Ǵ� �ڽ��޽� �Ҵ�
	BoxMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BoxMesh"));
	RootComponent = BoxMesh;
	BoxMesh->CreateDynamicMaterialInstance(0);
}

// Called when the game starts or when spawned
void AMissileActor::BeginPlay()
{
	Super::BeginPlay();
	Tags.Add(FName(*Element));

	if(Element == "poison")
		BoxMesh->GetStaticMesh()->SetMaterial(0,poison_Material);
	else if (Element == "ice")
		BoxMesh->GetStaticMesh()->SetMaterial(0, ice_Material);

}

void AMissileActor::NotifyActorBeginOverlap(AActor* OtherActor)
{
	FName name = "Enemy";
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, TEXT("NotifyActorBeginOverlap"));

	
	
	if (OtherActor->ActorHasTag(tagName)) {
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, name.ToString());

		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, TEXT("Attack!!"));
		UGameplayStatics::ApplyDamage(OtherActor, damage, NULL, this, UDamageType::StaticClass());
		
		SpwFloor();

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

void AMissileActor::SpwFloor()
{
	int32 rnd = FMath::RandRange(1, 101);
	if (rnd <= Sp_Rate)
	{
		UWorld* world = GetWorld();
		FRotator spwRoatation = { 0,0,0 };
		FVector lc = GetActorLocation();
		FVector spwLocation = { lc.X, lc.Y, 20.f};

		FActorSpawnParameters spwParameter;
		spwParameter.Owner = this;
		spwParameter.Instigator = GetInstigator();

		if (Element == "poison") {
			AicePlate_Actor* spwFloor = world->SpawnActor<AicePlate_Actor>(PoisonFloor, spwLocation, spwRoatation, spwParameter);
		}
		else if (Element == "ice") {
			AicePlate_Actor* spwFloor = world->SpawnActor<AicePlate_Actor>(iceFloor, spwLocation, spwRoatation, spwParameter);
		}
		

	}
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

