// Fill out your copyright notice in the Description page of Project Settings.


#include "icePlate_Actor.h"
#include "Engine/Classes/Components/StaticMeshComponent.h"
#include "Components/PrimitiveComponent.h"
#include "GameplayTagContainer.h"
#include "Engine.h"

// Sets default values
AicePlate_Actor::AicePlate_Actor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CylinderMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CylinderMesh"));
	CylinderMesh->CreateDynamicMaterialInstance(0);

	RootComponent = CylinderMesh;
}

// Called when the game starts or when spawned
void AicePlate_Actor::BeginPlay()
{
	Super::BeginPlay();
	curTime = time;
}

void AicePlate_Actor::NotifyActorBeginOverlap(AActor* OtherActor)
{
	
}

void AicePlate_Actor::NotifyActorEndOverlap(AActor* OtherActor)
{
}

// Called every frame
void AicePlate_Actor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	timer(DeltaTime);
}

void AicePlate_Actor::Frozen(AActor* OtherActor)
{
}

void AicePlate_Actor::timer(float DeltaTime)
{
	if (curTime > 0) {
		curTime -= DeltaTime;
		//CylinderMesh->SetVectorParameterValueOnMaterials(TEXT(color));
	}
	else {
		Destroy();
	}
}

