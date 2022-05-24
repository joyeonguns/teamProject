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
	// �浹 Overrap ����
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	virtual void NotifyActorEndOverlap(AActor* OtherActor) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	//  AllowPrivateAccess= true : ��� ����
	// UCameraComponent , USpringArmComponent ������ ��� ���� ����
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* CameraComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* SpringArmComponent;

	class UAIPerceptionStimuliSourceComponent* stimulus;
	void setStimulus();

	// Action �Է�
	bool bActionKey;

	// itembox ��ħ
	bool bOverrapItemBox;

	float MaxHP;

	float curHP;


public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EPlayerState I_PlayerState = EPlayerState::PlayerPoss;

	// ������ 
	ADropBox* ItemBox;
	class UWidgetComponent* Widget_Component;

	// Action - true;
	void InputActionPress();

	// Action - false
	void InputActionreleased();


	// ������ ��ħ����
	void OverrapItemBox_True();
	void OverrapItemBox_False();

	// HP 
	UFUNCTION(BlueprintCallable)
	float GetHP();
	UFUNCTION(BlueprintCallable)
	void SetHP(float value);
	
	// ������ ����
	virtual float TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCasual) override;

	// ������ â
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	TArray<int32> ItemArray = {0,0,0,0};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	TMap<int32, int32> ItemAmount;

	// ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "state")
		FString state = TEXT("Nomal");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Info")
	float PoisonDamage = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Info")
	float PoisonTime = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Info")
	float HpRegen = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Info")
	float BuffTime = 0;

	// ��ų����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Info")
		int32 s1_level = 0;

	// ĳ���� ���� (������ ���, �̼�, �ʴ� �߻��, ü��)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "status")
		float Dmg_Rate = 1.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "status")
		float Move_Rate = 1.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "status")
		float AtSpeed = 1.0f;

	// ���� ��
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gold")
	int32 CurGold;

	// ��� ��
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gold")
	int32 MaxGold;

	// ��ų ����
	void SetSkill();

	// ���
	void Dead();

	void GetItem();
};
