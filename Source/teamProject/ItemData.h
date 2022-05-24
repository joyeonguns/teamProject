// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/DataTable.h"
#include "ItemData.generated.h"

USTRUCT(BlueprintType)
struct  FItemInfo :public FTableRowBase
{
	GENERATED_BODY()
public:
	FItemInfo()
	{
		ItemName = FText::FromString("Name");
		ItemDescription = FText::FromString("This item is ....");
	}

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		FText ItemName;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		int32 ItemCode;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		UTexture2D* ItemImage;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		FText ItemDescription;
};

UCLASS()
class TEAMPROJECT_API AItemData : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItemData();

//protected:
//	// Called when the game starts or when spawned
//	virtual void BeginPlay() override;
//
//public:	
//	// Called every frame
//	virtual void Tick(float DeltaTime) override;

};
