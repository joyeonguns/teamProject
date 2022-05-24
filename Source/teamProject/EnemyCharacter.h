// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "DropBox.h"
#include "EnemyCharacter.generated.h"

UCLASS()
class TEAMPROJECT_API AEnemyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemyCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere, Category = "itemCode")
		int32 itemCode = 0;
	UPROPERTY(EditAnywhere, Category = "itemCode")
		int32 GunCode = 0;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// 현재 체력
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "HP")
		float curHp;
	// 맥스 체력
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Hp")
		float maxHp;
	// 아이템 박스
	UPROPERTY(EditDefaultsOnly, Category = "DropBox")
		TSubclassOf<ADropBox> DropBoxClass;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "ABPawnComponent")
		class UCapsuleComponent* Body = nullptr;
	// 데미지
	virtual float TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCasual) override;
	// 아이템 드롭
	void DropItemBox();

	// 패트롤 좌표
	UPROPERTY(EditAnywhere, Category = "PatrollPos")
		FVector Pos1 = { 0,0,118 };
	UPROPERTY(EditAnywhere, Category = "PatrollPos")
		FVector Pos2 = { 0,0,118 };


private:
	class UWidgetComponent* Widget_Component;
	
};
