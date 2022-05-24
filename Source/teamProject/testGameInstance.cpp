// Fill out your copyright notice in the Description page of Project Settings.


#include "testGameInstance.h"
#include "GunData.h"

UtestGameInstance::UtestGameInstance()
{
	static ConstructorHelpers::FObjectFinder<UDataTable> GunInfoObject(TEXT("DataTable'/Game/DataTable/GunDataTable.GunDataTable'"));
	if (GunInfoObject.Succeeded())
	{
		GunDataTable = GunInfoObject.Object;
	}
}

FGunInfo* UtestGameInstance::GunDataTableInstance(int32 num)
{
	return GunDataTable->FindRow<FGunInfo>(*FString::FromInt(num),TEXT(""));
}
