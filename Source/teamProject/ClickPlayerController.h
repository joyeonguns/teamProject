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

	// 스킬 존 오버랩 체크
	bool bOverlapSkillZone = false;

	// Action_1 입력
	bool bActionKey;

	// 쿨다운 체크
	bool bCoolTime;

	// 마우스 클릭 상태
	bool bClickRightMouse;

	// S 키입력
	bool bStopKey;

	// 마우스 좌클릭 상태
	bool bClickLeftClick;

	bool bAttackCommand;

	void CoolDown(float deltaTime);

	void AttackCommandTrue();

	void AttackCommandFalse();

	// bCooltime True
	void CoolDownTrue();
	// bCooltime False
	void CoolDownFalse();

	// 우클릭 누름 - bClickRightMouse상태 변환
	void InputRightMouseButtonPressed();

	// 우클릭 해제 - bClickRightMouse상태 변환
	void InputRightMouseButtonReleased();

	// 좌클릭 누름 - bClickRightMouse상태 변환
	void InputLeftMouseButtonPressed();

	// 좌클릭 해제 - bClickRightMouse상태 변환
	void InputLeftMouseButtonReleased();

	// S키 입력 - bStopKey : true
	void InputStopKeyPressed();

	// S키 입력 - bStopKey : false
	void InputStopKeyreleased();

	// Action_1 - true;
	void InputActionPress();

	// Action_1 - false
	void InputActionreleased();

	// 오브젝트 이동 정지
	void StopMoveObject();

	// 정해진 위치로 오브젝트 이동
	void SetNewDestination(const FVector Destination, int m_num);

	// 마우스정보를 SetNewDestination에 넘겨줌
	void MoveToMouseCursor(const int m_num);

	// 버튼클릭 실행
	virtual void SetupInputComponent() override;

	// 실시간 마우스 정보호출을 위해
	virtual void PlayerTick(float DeltaTime) override;

	// ESC 메뉴오픈
	void InGameMenu();

public:
	// 오브젝트 스폰
	void Fire(FVector Destination);

	// RPM
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float coolTime;

	//현재 총 정보
	// 재장전
	bool bReload = false;
	
	// 재장전 시간
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ReloadTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float curReloadTime;

	// RPM 시간
	UPROPERTY(EditAnywhere, BlueprintReadWrite )
	float RPM;

	// 장탄수
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Armo;
	// 현재 장탄수
	UPROPERTY(EditAnywhere, BlueprintReadWrite )
	int32 cur_Armo;

	// 데미지
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Damage;
	// 총코드
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 GunCode;


	// 아이템 박스 획득
	void GetItemBox(AActor& other);

	// 블루브린터로 편집 가능
	UPROPERTY(EditDefaultsOnly, Category = "Projectile")
		// 스폰할 오브젝트를 담을 변수 추가
		TSubclassOf<AMissileActor> MissileClass;
	// 블루브린터로 편집 가능
	UPROPERTY(EditDefaultsOnly, Category = "Boom")
		TSubclassOf<AItem_Boom> I_Boom;

	// 아이템 사용
	void UsingItem_1();
	void UsingItem_2();
	void UsingItem_3();
	void UsingItem_4();

	// 액션키 입력
	void Input_Action_1();
	void Input_Action_2();
	void Input_Action_3();
	void Input_Action_4();

	// 총 저장
	void SetGun(int32 num);
	void Reloading(float deltaTime);
	FGunInfo* curGunData;
	
	// 스킬 저장
	void SetSkill(int32 s1, int32 s2, int32 s3);

	// 폰
	APawn* AMyPawn;
	// 아이템
	ADropBox* ItemBox;
	// 플래이어
	APlayerCharacter* Player;

	// bOverlapSkillZone true;
	void SetOverlapSkillZone_true();
	void SetOverlapSkillZone_false();


};
