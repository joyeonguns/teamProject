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


	/** 상태 관련 **/
	FString state = TEXT("Nomal");

	// 중독 상태 관련
	// 중독 상태
	bool bstate_Poison;
	// 중독 겹침?
	bool bOvelap_Poison;
	// 중독 지속시간
	float PoisonDur;
	// 중독 데미지
	float PoisonDmg;
	// 중독 겹침
	void ApplyPoison(float _dmg);
	// 중독 상태
	void Poison_ing(float deltaTime);

	// 버프 상태 관련
	// 버프 상태
	bool bstate_Buff;
	// 버프 겹침?
	bool bOvelap_Buff;
	// 버프 지속시간
	float BuffDur;
	// 버프 리젠
	float BuffRegen;
	// 버프 겹침
	void ApplyBuff();
	// 버프 상태
	void Buff_ing(float deltaTime);


	// ice 상태 관련
	// ice 상태
	bool bstate_ice;
	// ice 겹침?
	bool bOvelap_ice;
	// 기본 속도
	float amuSpeed;
	// ice 지속시간
	float iceDur;
	// ice 겹침
	void ApplyIce();
	// ice 상태
	void Ice_ing(float deltaTime);

	void Dead();


	// 기본 머티리얼
	UPROPERTY(EditAnywhere)
		class UMaterial* nomal_Material;
	// ice material
	UPROPERTY(EditAnywhere)
		class UMaterial* ice_Material;
	// 중독 머티리얼
	UPROPERTY(EditAnywhere)
		class UMaterial* poison_Material;
	// 버프 머티리얼
	UPROPERTY(EditAnywhere)
		class UMaterial* buff_Material;


private:
	class UWidgetComponent* Widget_Component;
	
};
