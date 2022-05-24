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

	// ���� ü��
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "HP")
		float curHp;
	// �ƽ� ü��
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Hp")
		float maxHp;
	// ������ �ڽ�
	UPROPERTY(EditDefaultsOnly, Category = "DropBox")
		TSubclassOf<ADropBox> DropBoxClass;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "ABPawnComponent")
		class UCapsuleComponent* Body = nullptr;
	// ������
	virtual float TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCasual) override;
	// ������ ���
	void DropItemBox();

	// ��Ʈ�� ��ǥ
	UPROPERTY(EditAnywhere, Category = "PatrollPos")
		FVector Pos1 = { 0,0,118 };
	UPROPERTY(EditAnywhere, Category = "PatrollPos")
		FVector Pos2 = { 0,0,118 };


private:
	class UWidgetComponent* Widget_Component;
	
};
