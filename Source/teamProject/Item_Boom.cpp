// Fill out your copyright notice in the Description page of Project Settings.


#include "Item_Boom.h"
#include "Components/SphereComponent.h"
// Sets default values
AItem_Boom::AItem_Boom()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	BoomMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BoomMesh"));
	BoomMesh->CreateDynamicMaterialInstance(0);

	DamageComponent = CreateDefaultSubobject<USphereComponent>(TEXT("DamageCollision"));
	//CollisionSphere->SetupAttachment(this->GetStaticcom)
	DamageComponent->InitSphereRadius(300.f);

	RootComponent = DamageComponent;
	BoomMesh->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AItem_Boom::BeginPlay()
{
	Super::BeginPlay();
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Boom!!_ Spawn"));
	curTime = time;
	//BoomMesh->AddImpulse(FVector(500,0,500));
	AddVector = GetActorForwardVector() * 20 + FVector(0, 0, 20);
}

// Called every frame
void AItem_Boom::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	timer(DeltaTime);
}

void AItem_Boom::Boom(AActor* OtherActor)
{	
	
}

void AItem_Boom::sp_Effect()
{
	
	FRotator SpawnRotation = { 0,0,0 };
	UWorld* world = GetWorld();

	if (world)
	{
		FActorSpawnParameters SpawnParamater;
		SpawnParamater.Owner = this;
		SpawnParamater.Instigator = GetInstigator();
		FVector spawnLocation = GetActorLocation();

		AActor* B_effect = world->SpawnActor<AActor>(BoomEffect, spawnLocation, SpawnRotation, SpawnParamater);
		FName tag = TEXT("Enemy");
		if (B_effect)
		{
			//B_effect->SetParameter(Destination, tag, Damage);
		}
	}
}

void AItem_Boom::timer(float DeltaTime)
{
	if (curTime > 0) {
		curTime -= DeltaTime;
		//CylinderMesh->SetVectorParameterValueOnMaterials(TEXT(color));

		/*if(curTime < 1)
			AddVector = AddVector - AddVector * DeltaTime * (0.3f,0.3f,0);*/
		AddVector = AddVector - AddVector * DeltaTime * (0, 0, 2.0f);
		FVector NextLocation = this->GetActorLocation() + AddVector;
		
		SetActorLocation(NextLocation);
	}
	else {
		sp_Effect();
		Destroy();
	}
}

