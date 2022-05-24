// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MissileActor.h"
#include "Item_Boom.h"
#include "DropBox.h"
#include "PlayerCharacter.h"
#include "testGameInstance.h"
#include "GunData.h"
#include "ClickPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class TEAMPROJECT_API AClickPlayerController : public APlayerController
{
	GENERATED_BODY()

public : 
	AClickPlayerController();

protected:
	virtual void BeginPlay() override;

private:
	float DefCooltime = 0.4f;
	FVector _AttDestination;
	FVector _MoveVector;

	// ��ų �� ������ üũ
	bool bOverlapSkillZone = false;

	// Action_1 �Է�
	bool bActionKey;

	// ��ٿ� üũ
	bool bCoolTime;

	// ���콺 Ŭ�� ����
	bool bClickRightMouse;

	// S Ű�Է�
	bool bStopKey;

	// ���콺 ��Ŭ�� ����
	bool bClickLeftClick;

	bool bAttackCommand;

	void CoolDown(float deltaTime);

	void AttackCommandTrue();

	void AttackCommandFalse();

	// bCooltime True
	void CoolDownTrue();
	// bCooltime False
	void CoolDownFalse();

	// ��Ŭ�� ���� - bClickRightMouse���� ��ȯ
	void InputRightMouseButtonPressed();

	// ��Ŭ�� ���� - bClickRightMouse���� ��ȯ
	void InputRightMouseButtonReleased();

	// ��Ŭ�� ���� - bClickRightMouse���� ��ȯ
	void InputLeftMouseButtonPressed();

	// ��Ŭ�� ���� - bClickRightMouse���� ��ȯ
	void InputLeftMouseButtonReleased();

	// SŰ �Է� - bStopKey : true
	void InputStopKeyPressed();

	// SŰ �Է� - bStopKey : false
	void InputStopKeyreleased();

	// Action_1 - true;
	void InputActionPress();

	// Action_1 - false
	void InputActionreleased();

	// ������Ʈ �̵� ����
	void StopMoveObject();

	// ������ ��ġ�� ������Ʈ �̵�
	void SetNewDestination(const FVector Destination, int m_num);

	// ���콺������ SetNewDestination�� �Ѱ���
	void MoveToMouseCursor(const int m_num);

	// ��ưŬ�� ����
	virtual void SetupInputComponent() override;

	// �ǽð� ���콺 ����ȣ���� ����
	virtual void PlayerTick(float DeltaTime) override;

	// ESC �޴�����
	void InGameMenu();

public:
	// ������Ʈ ����
	void Fire(FVector Destination);

	// RPM
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float coolTime;

	//���� �� ����
	// ������
	bool bReload = false;
	
	// ������ �ð�
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ReloadTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float curReloadTime;

	// RPM �ð�
	UPROPERTY(EditAnywhere, BlueprintReadWrite )
	float RPM;

	// ��ź��
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Armo;
	// ���� ��ź��
	UPROPERTY(EditAnywhere, BlueprintReadWrite )
	int32 cur_Armo;

	// ������
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Damage;
	// ���ڵ�
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 GunCode;


	// ������ �ڽ� ȹ��
	void GetItemBox(AActor& other);

	// ���기�ͷ� ���� ����
	UPROPERTY(EditDefaultsOnly, Category = "Projectile")
		// ������ ������Ʈ�� ���� ���� �߰�
		TSubclassOf<AMissileActor> MissileClass;
	// ���기�ͷ� ���� ����
	UPROPERTY(EditDefaultsOnly, Category = "Boom")
		TSubclassOf<AItem_Boom> I_Boom;

	// ������ ���
	void UsingItem_1();
	void UsingItem_2();
	void UsingItem_3();
	void UsingItem_4();

	// �׼�Ű �Է�
	void Input_Action_1();
	void Input_Action_2();
	void Input_Action_3();
	void Input_Action_4();

	// �� ����
	void SetGun(int32 num);
	void Reloading(float deltaTime);
	FGunInfo* curGunData;
	
	// ��ų ����
	void SetSkill(int32 s1, int32 s2, int32 s3);

	// ��
	APawn* AMyPawn;
	// ������
	ADropBox* ItemBox;
	// �÷��̾�
	APlayerCharacter* Player;

	// bOverlapSkillZone true;
	void SetOverlapSkillZone_true();
	void SetOverlapSkillZone_false();


};
