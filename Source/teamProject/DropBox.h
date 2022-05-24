// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DropBox.generated.h"

UCLASS()
class TEAMPROJECT_API ADropBox : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADropBox();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private :
	UPROPERTY(EditAnywhere, Category = "itemCode")
	int32 itemCode = 2;
	UPROPERTY(EditAnywhere, Category = "itemCode")
	int32 GunCode = 0;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* BoxMesh;

	void SetItem(int item,int gun);

	int32 GetItemCode();
	int32 GetGunCode();

	void OpenBox();

};
