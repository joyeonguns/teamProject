// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemyCharacter.h"
#include "DrawDebugHelpers.h"
#include "Item_Boom.generated.h"

UCLASS()
class TEAMPROJECT_API AItem_Boom : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItem_Boom();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// ÆøÅº ¸Þ½¬
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* BoomMesh;
	// µ¥¹ÌÁö ¸Þ½¬
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		class USphereComponent* DamageComponent;

	// Æø¹ßÀÌÆåÆ®
	UPROPERTY(EditDefaultsOnly, Category = "Booom")
		TSubclassOf<AActor> BoomEffect;

	float time = 3.0f;
	float curTime;
	FVector AddVector = { 1,0,1 };

	// Æø¹ß
	void Boom(AActor* OtherActor);
	
	// Æø¹ßÀÌÆåÆ®
	void sp_Effect();
	void timer(float DeltaTime);
};
