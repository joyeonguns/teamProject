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
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	virtual void NotifyActorEndOverlap(AActor* OtherActor) override;

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


	/** ���� ���� **/
	FString state = TEXT("Nomal");

	// �ߵ� ���� ����
	// �ߵ� ����
	bool bstate_Poison;
	// �ߵ� ��ħ?
	bool bOvelap_Poison;
	// �ߵ� ���ӽð�
	float PoisonDur;
	// �ߵ� ������
	float PoisonDmg;
	// �ߵ� ��ħ
	void ApplyPoison(float _dmg);
	// �ߵ� ����
	void Poison_ing(float deltaTime);

	// ���� ���� ����
	// ���� ����
	bool bstate_Buff;
	// ���� ��ħ?
	bool bOvelap_Buff;
	// ���� ���ӽð�
	float BuffDur;
	// ���� ����
	float BuffRegen;
	// ���� ��ħ
	void ApplyBuff();
	// ���� ����
	void Buff_ing(float deltaTime);


	// ice ���� ����
	// ice ����
	bool bstate_ice;
	// ice ��ħ?
	bool bOvelap_ice;
	// �⺻ �ӵ�
	float amuSpeed;
	// ice ���ӽð�
	float iceDur;
	// ice ��ħ
	void ApplyIce();
	// ice ����
	void Ice_ing(float deltaTime);

	void Dead();


	// �⺻ ��Ƽ����
	UPROPERTY(EditAnywhere)
		class UMaterial* nomal_Material;
	// ice material
	UPROPERTY(EditAnywhere)
		class UMaterial* ice_Material;
	// �ߵ� ��Ƽ����
	UPROPERTY(EditAnywhere)
		class UMaterial* poison_Material;
	// ���� ��Ƽ����
	UPROPERTY(EditAnywhere)
		class UMaterial* buff_Material;


private:
	class UWidgetComponent* Widget_Component;
	
};
