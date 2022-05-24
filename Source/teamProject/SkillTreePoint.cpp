// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillTreePoint.h"
#include "Engine/Classes/Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Components/PrimitiveComponent.h"
#include "teamProjectGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "ClickPlayerController.h"

// Sets default values
ASkillTreePoint::ASkillTreePoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("OutCollision"));
	//CollisionSphere->SetupAttachment(this->GetStaticcom)
	CollisionSphere->InitSphereRadius(200.f);
	RootComponent = CollisionSphere;

	PointMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("inCollision"));
	PointMesh->SetupAttachment(RootComponent);

	bOverlap = false;
	
	CollisionSphere->OnComponentBeginOverlap.AddDynamic(this, &ASkillTreePoint::OnOverlapBegin);
	CollisionSphere->OnComponentEndOverlap.AddDynamic(this, &ASkillTreePoint::OnOverlapEnd);
}

// Called when the game starts or when spawned
void ASkillTreePoint::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASkillTreePoint::OnOverlapBegin(UPrimitiveComponent* OverlapedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{	
	if (OtherActor->ActorHasTag("Player")) {
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Overlap Skill True"));

		bOverlap = true;
		AClickPlayerController* player = Cast<AClickPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(),0));
		if (player) {
			player->SetOverlapSkillZone_true();
		}
	}
}

void ASkillTreePoint::OnOverlapEnd(UPrimitiveComponent* OverlapedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor->ActorHasTag("Player")) {
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Overlap Skill false"));

		bOverlap = false;
		AClickPlayerController* player = Cast<AClickPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
		if (player) {
			player->SetOverlapSkillZone_false();
		}
	}
}

// Called every frame
void ASkillTreePoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

