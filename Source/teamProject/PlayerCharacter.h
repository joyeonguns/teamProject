// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyCharacter.h"
#include "GameFramework/Character.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "DropBox.h"
#include "Containers/Map.h"
#include "GunData.h"
#include "PlayerCharacter.generated.h"

UENUM(BlueprintType)
enum class EPlayerState :uint8
{
	PlayerPoss UMETA(DisplayName = "PlayerPoss"),
	PlayerUnPoss UMETA(DisplayName = "PlayerUnPoss"),	
};

UCLASS()
class TEAMPROJECT_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	// 충돌 Overrap 판정
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	virtual void NotifyActorEndOverlap(AActor* OtherActor) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	//  AllowPrivateAccess= true : 상속 가능
	// UCameraComponent , USpringArmComponent 형태의 멤버 변수 생성
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* CameraComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* SpringArmComponent;

	class UAIPerceptionStimuliSourceComponent* stimulus;
	void setStimulus();

	// Action 입력
	bool bActionKey;

	// itembox 겹침
	bool bOverrapItemBox;

	float MaxHP;

	float curHP;


public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EPlayerState I_PlayerState = EPlayerState::PlayerPoss;

	// 아이템 
	ADropBox* ItemBox;
	class UWidgetComponent* Widget_Component;

	// Action - true;
	void InputActionPress();

	// Action - false
	void InputActionreleased();


	// 아이템 겹침상태
	void OverrapItemBox_True();
	void OverrapItemBox_False();

	// HP 
	UFUNCTION(BlueprintCallable)
	float GetHP();
	UFUNCTION(BlueprintCallable)
	void SetHP(float value);
	
	// 데미지 받음
	virtual float TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCasual) override;

	// 아이템 창
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	TArray<int32> ItemArray = {0,0,0,0};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	TMap<int32, int32> ItemAmount;


	// 스킬레벨
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Info")
		int32 s1_level = 0;

	// 캐릭터 스텟 (데미지 계수, 이속, 초당 발사수, 체력)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "status")
		float Dmg_Rate = 1.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "status")
		float Move_Rate = 1.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "status")
		float AtSpeed = 1.0f;

	// 현재 돈
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gold")
	int32 CurGold;

	// 모든 돈
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gold")
	int32 MaxGold;

	// 스킬 적용
	void SetSkill();

	// 사망
	void Dead();

	void GetItem();

	/** 상태 관련 **/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "state")
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
};
