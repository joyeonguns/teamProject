// Fill out your copyright notice in the Description page of Project Settings.


#include "DropBox.h"
#include "Engine/Classes/Components/StaticMeshComponent.h"
#include "Components/PrimitiveComponent.h"

// Sets default values
ADropBox::ADropBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	BoxMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BoxMesh"));
	RootComponent = BoxMesh;
}

// Called when the game starts or when spawned
void ADropBox::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADropBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
void ADropBox::SetItem(int item, int gun)
{
	itemCode = item;
	GunCode = gun;
}
int32 ADropBox::GetItemCode()
{
	return itemCode;
}
int32 ADropBox::GetGunCode()
{
	return GunCode;
}

void ADropBox::OpenBox()
{
	this->Destroy();
}

