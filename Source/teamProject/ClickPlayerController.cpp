// Fill out your copyright notice in the Description page of Project Settings.


#include "ClickPlayerController.h"
#include <Blueprint/AIBlueprintHelperLibrary.h> // 오브젝트 이동을 위해 필요
#include "Engine.h"
#include "teamProjectGameModeBase.h"
#include "Kismet/KismetMathLibrary.h"


AClickPlayerController::AClickPlayerController()
{
	bShowMouseCursor = true;  // 마우스를 보여줌

}


void AClickPlayerController::BeginPlay()
{
	Super::BeginPlay();
	AMyPawn = GetPawn();
	bCoolTime = false;
	coolTime = DefCooltime;
	Player = Cast<APlayerCharacter>(AMyPawn);

	SetGun(2);

	//bRelord = true;
	//RelordTime = Player->GunDataTable.
}

// bool 공격
void AClickPlayerController::AttackCommandTrue()
{
	bAttackCommand = true;
}
void AClickPlayerController::AttackCommandFalse()
{
	bAttackCommand = false;
}

// bool 쿨다운
void AClickPlayerController::CoolDownTrue()
{
	bCoolTime = true;
}
void AClickPlayerController::CoolDownFalse()
{
	bCoolTime = false;
}

// bool 우클릭
void AClickPlayerController::InputRightMouseButtonPressed()
{
	bClickRightMouse = true;
}
void AClickPlayerController::InputRightMouseButtonReleased()
{
	bClickRightMouse = false;
}

// bool 좌클릭
void AClickPlayerController::InputLeftMouseButtonPressed()
{
	bClickLeftClick = true;
}
void AClickPlayerController::InputLeftMouseButtonReleased()
{
	bClickLeftClick = false;
}

// bool stop
void AClickPlayerController::InputStopKeyPressed()
{
	bStopKey = true;
}
void AClickPlayerController::InputStopKeyreleased()
{
	bStopKey = false;
}

// bool Action1
void AClickPlayerController::InputActionPress()
{
	bActionKey = true;
	Player->InputActionPress();
	if (bOverlapSkillZone) {
		AteamProjectGameModeBase* GameMode = Cast<AteamProjectGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Overrap!!!!")));
		GameMode->ChangeSideWidget(GameMode->GetSkillTreeWidgetWidget());
		Player->I_PlayerState = EPlayerState::PlayerUnPoss;
	}

}
void AClickPlayerController::InputActionreleased()
{
	bActionKey = false;
}

// 입력 처리
void AClickPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	// RightClick 입력시 InputRightMouseButtonPressed 실행
	InputComponent->BindAction("RightClick", IE_Pressed, this, &AClickPlayerController::InputRightMouseButtonPressed);
	// RightClick relesed 시 InputRightMouseButtonReleased 실행
	InputComponent->BindAction("RightClick", IE_Released, this, &AClickPlayerController::InputRightMouseButtonReleased);

	// LeftClick 입력시 InputRightMouseButtonPressed 실행
	InputComponent->BindAction("LeftClick", IE_Pressed, this, &AClickPlayerController::InputLeftMouseButtonPressed);
	// LeftClick relesed 시 InputRightMouseButtonReleased 실행
	InputComponent->BindAction("LeftClick", IE_Released, this, &AClickPlayerController::InputLeftMouseButtonReleased);

	// S 입력시 InputStopKeyPressed 실행
	InputComponent->BindAction("StopKey", IE_Pressed, this, &AClickPlayerController::InputStopKeyPressed);
	// S 릴리즈시 InputStopKeyreleased 실행
	InputComponent->BindAction("StopKey", IE_Released, this, &AClickPlayerController::InputStopKeyreleased);

	// Action 입력시 InputActionpress 실행
	InputComponent->BindAction("Action", IE_Pressed, this, &AClickPlayerController::InputActionPress);
	// Action 릴리즈시 InputActionreleased 실행
	InputComponent->BindAction("Action", IE_Released, this, &AClickPlayerController::InputActionreleased);

	// Action 입력시 Input_Action_1 실행
	InputComponent->BindAction("Action_1", IE_Pressed, this, &AClickPlayerController::Input_Action_1);
	// Action 입력시 Input_Action_1 실행
	InputComponent->BindAction("Action_2", IE_Pressed, this, &AClickPlayerController::Input_Action_2);
	// Action 입력시 Input_Action_1 실행
	InputComponent->BindAction("Action_3", IE_Pressed, this, &AClickPlayerController::Input_Action_3);
	// Action 입력시 Input_Action_1 실행
	InputComponent->BindAction("Action_4", IE_Pressed, this, &AClickPlayerController::Input_Action_4);

	// ESC 입력시 InGameMenu실행
	InputComponent->BindAction("ESC", IE_Pressed, this, &AClickPlayerController::InGameMenu);

}

void AClickPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	if (Player->I_PlayerState == EPlayerState::PlayerPoss)
	{
		// 실시간으로 bClickRightMouse == true일시 MoveToMouseCursor()함수 실행
		if (bClickRightMouse)
		{
			//StopMoveObject();
			MoveToMouseCursor(0);
		}
		if (bClickLeftClick)
		{
			StopMoveObject();
			MoveToMouseCursor(1);
		}
		if (bStopKey)
		{
			StopMoveObject();
		}
	}	

	// 공격 쿨다운 관리
	if (bReload == true) {
		Reloading(DeltaTime);
	}
	else {
		if (bCoolTime == true)
		{
			// 공격
			CoolDown(DeltaTime);
		}

		if (bAttackCommand == true && bCoolTime == false)
		{
			FVector Location = AMyPawn->GetActorLocation();
			_MoveVector.Z = Location.Z;
			float distance = FVector::Dist(Location, _MoveVector);
			if (distance < 100.0f && AMyPawn->GetVelocity().IsNearlyZero())
			{
				GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Fire!!"));
				Fire(_AttDestination);
			}
		}
	}
	

}

void AClickPlayerController::InGameMenu()
{
	AteamProjectGameModeBase* GameMode = Cast<AteamProjectGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("InGameMenu Open!!!!")));
	if (GameMode) {
		GameMode->ChangeSideWidget(GameMode->GetInGameMenu());
	}
	this->SetPause(true);
	//Player->I_PlayerState = EPlayerState::PlayerUnPoss;
}

void AClickPlayerController::StopMoveObject()
{
	AttackCommandFalse();
	APawn* const MyPawn = GetPawn();
	FVector des = MyPawn->GetActorLocation();
	UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, des);
	InputStopKeyreleased();
}


void AClickPlayerController::SetNewDestination(const FVector Destination, int m_num)
{
	// GetPawn() 함수를 이용해  오브젝트를 가져옴
	APawn* const MyPawn = GetPawn();

	if (MyPawn)
	{
		// MyPawn과 Destination 사이의 거리
		float const Distance = FVector::Dist(Destination, MyPawn->GetActorLocation());
		// 우클릭 입력
		if (m_num == 0)
		{
			AttackCommandFalse();
			if (Distance > 120.0f)
			{
				// 거리가 120 이상일 시 이객체를 목적지로 이동시킴
				UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, Destination);
			}
		}
		// 좌클릭 입력
		else if (m_num == 1)
		{

			if (Distance > 800.0f)
			{
				AttackCommandTrue();
				// 거리가 800 이상일시 이객체를 목적지로 이동시킴
				FVector myLoc = MyPawn->GetActorLocation();
				FVector dis = {
					((Destination - myLoc)) * (1 - 800 / Distance) + myLoc,
				};
				UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, dis);
				/*FString disX = FString::SanitizeFloat(dis.X);
				FString disY = FString::SanitizeFloat(dis.Y);
				GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("X : "+ disX + " Y : " + disY));*/
				_AttDestination = Destination;
				_MoveVector = dis;
			}
			else
			{
				if (bCoolTime == false)
					Fire(Destination);
			}
		}
	}
}

void AClickPlayerController::MoveToMouseCursor(const int m_num)
{
	FHitResult Hit;		// 충돌 객체에 대한 정보저장
	// 마우스 커서 밑에 레이트레이스를 쏴서 부딫힌 좌표를 Hit에 저장
	GetHitResultUnderCursor(ECC_Visibility, false, Hit);

	if (Hit.bBlockingHit)
	{
		// 충동 결과가 있을시 Destination에 Hit의 정보 전달
		SetNewDestination(Hit.ImpactPoint, m_num);
	}
}

void AClickPlayerController::Fire(FVector Destination)
{
	APawn* const MyPawn = GetPawn();
	//FVector SpawnLocation = MyPawn->GetActorLocation();
	FRotator SpawnRotation = { 0,0,0 };
	UWorld* world = GetWorld();

	FVector myLoc = MyPawn->GetActorLocation();
	FVector lookAtDes = Destination;
	lookAtDes.Z = MyPawn->GetActorLocation().Z;
	FRotator DesRot = UKismetMathLibrary::FindLookAtRotation(myLoc, lookAtDes);
	MyPawn->SetActorRotation(DesRot);

	if (world)
	{
		FActorSpawnParameters SpawnParamater;
		SpawnParamater.Owner = this;
		SpawnParamater.Instigator = GetInstigator();
		FVector desNormal = (Destination - MyPawn->GetActorLocation()).GetSafeNormal();;
		FVector spawnLocation = MyPawn->GetActorLocation() + desNormal * 50;

		AMissileActor* Missile = world->SpawnActor<AMissileActor>(MissileClass, spawnLocation, SpawnRotation, SpawnParamater);
		FName tag = TEXT("Enemy");
		if (Missile)
		{
			Missile->SetParameter(Destination,tag, Damage);
		}
	}

	cur_Armo -= 1;
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString::Printf(TEXT("Armo IS %d"), cur_Armo));
	if (cur_Armo <= 0) {
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Reloading"));
		bReload = true;
	}
	AttackCommandFalse();
	CoolDownTrue();
}

void AClickPlayerController::GetItemBox(AActor& other)
{

}

void AClickPlayerController::UsingItem_1()
{
	float HP = Player->GetHP();
	HP += 30;
	if (HP >= 100)
		HP = 100;
	Player->SetHP(HP);
}

void AClickPlayerController::UsingItem_2()
{
	Player->state = TEXT("Poison");
	Player->PoisonDamage = 3.f;
	Player->PoisonTime = 10.f;
}

void AClickPlayerController::UsingItem_3()
{
	Player->state = TEXT("Buff");
	Player->HpRegen = 10.f;
	Player->BuffTime = 10.f;
}

void AClickPlayerController::UsingItem_4()
{
	StopMoveObject();
	// 붐
	APawn* const MyPawn = GetPawn();
	//FVector SpawnLocation = MyPawn->GetActorLocation();
	FRotator SpawnRotation = MyPawn->GetActorRotation();
	UWorld* world = GetWorld();

	FVector myLoc = MyPawn->GetActorLocation();

	if (world)
	{
		FActorSpawnParameters SpawnParamater;
		SpawnParamater.Owner = this;
		SpawnParamater.Instigator = GetInstigator();
		FVector spawnLocation = MyPawn->GetActorLocation() + MyPawn->GetActorForwardVector()*30;

		AItem_Boom* Booms = world->SpawnActor<AItem_Boom>(I_Boom, spawnLocation, SpawnRotation, SpawnParamater);
		FName tag = TEXT("Enemy");
		if (Booms)
		{
			//Booms->SetParameter(Destination, tag, Damage);
		}
	}
}

void AClickPlayerController::Input_Action_1()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("InPut 1"));
	if (Player->ItemArray[0] == 0) {
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("No Item"));
	}
	else if (Player->ItemArray[0] == 1) {
		UsingItem_1();
		Player->ItemAmount[1] -= 1;
		if (Player->ItemAmount[1] == 0) {
			Player->ItemAmount.Remove(1);
			Player->ItemArray[0] = 0;
		}
	}
	else if (Player->ItemArray[0] == 2) {
		UsingItem_2();
		Player->ItemAmount[2] -= 1;
		if (Player->ItemAmount[2] == 0) {
			Player->ItemAmount.Remove(2);
			Player->ItemArray[0] = 0;
		}
	}
	else if (Player->ItemArray[0] == 3) {
		UsingItem_3();
		Player->ItemAmount[3] -= 1;
		if (Player->ItemAmount[3] == 0) {
			Player->ItemAmount.Remove(3);
			Player->ItemArray[0] = 0;
		}
	}
}

void AClickPlayerController::Input_Action_2()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("InPut 2"));
	if (Player->ItemArray[1] == 0) {
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("No Item"));
	}
	else if (Player->ItemArray[1] == 1) {
		UsingItem_1();
		Player->ItemAmount[1] -= 1;
		if (Player->ItemAmount[1] == 0) {
			Player->ItemAmount.Remove(1);
			Player->ItemArray[1] = 0;
		}
	}
	else if (Player->ItemArray[1] == 2) {
		UsingItem_2();
		Player->ItemAmount[2] -= 1;
		if (Player->ItemAmount[2] == 0) {
			Player->ItemAmount.Remove(2);
			Player->ItemArray[1] = 0;
		}
	}
	else if (Player->ItemArray[1] == 3) {
		UsingItem_3();
		Player->ItemAmount[3] -= 1;
		if (Player->ItemAmount[3] == 0) {
			Player->ItemAmount.Remove(3);
			Player->ItemArray[1] = 0;
		}
	}
}

void AClickPlayerController::Input_Action_3()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("InPut 3"));
	if (Player->ItemArray[2] == 0) {
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("No Item"));
	}
	else if (Player->ItemArray[2] == 1) {
		UsingItem_1();
		Player->ItemAmount[1] -= 1;
		if (Player->ItemAmount[1] == 0) {
			Player->ItemAmount.Remove(1);
			Player->ItemArray[2] = 0;
		}
	}
	else if (Player->ItemArray[2] == 2) {
		UsingItem_2();
		Player->ItemAmount[2] -= 1;
		if (Player->ItemAmount[2] == 0) {
			Player->ItemAmount.Remove(2);
			Player->ItemArray[2] = 0;
		}
	}
	else if (Player->ItemArray[2] == 3) {
		UsingItem_3();
		Player->ItemAmount[3] -= 1;
		if (Player->ItemAmount[3] == 0) {
			Player->ItemAmount.Remove(3);
			Player->ItemArray[2] = 0;
		}
	}
}

void AClickPlayerController::Input_Action_4()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("InPut 4"));
	if (Player->ItemArray[3] == 0) {
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("No Item"));
	}
	else if (Player->ItemArray[3] == 1) {
		UsingItem_1();
		Player->ItemAmount[1] -= 1;
		if (Player->ItemAmount[1] == 0) {
			Player->ItemAmount.Remove(1);
			Player->ItemArray[3] = 0;
		}
	}
	else if (Player->ItemArray[3] == 2) {
		UsingItem_2();
		Player->ItemAmount[2] -= 1;
		if (Player->ItemAmount[2] == 0) {
			Player->ItemAmount.Remove(2);
			Player->ItemArray[3] = 0;
		}
	}
	else if (Player->ItemArray[3] == 3) {
		UsingItem_3();
		Player->ItemAmount[3] -= 1;
		if (Player->ItemAmount[3] == 0) {
			Player->ItemAmount.Remove(3);
			Player->ItemArray[3] = 0;
		}
	}
	else {
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Boom!!"));
		UsingItem_4();
	}
}

void AClickPlayerController::SetGun(int32 num)
{
	UtestGameInstance* tGameInstance = Cast<UtestGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (nullptr == tGameInstance) return;

	curGunData = tGameInstance->GunDataTableInstance(num);
	if (curGunData) {
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Set Gun"));

		GunCode = curGunData->ItemCode;


		ReloadTime = curGunData->ReloadTime;
		curReloadTime = ReloadTime;

		RPM = curGunData->RPM;

		Armo = curGunData->Armo;
		cur_Armo = Armo;
				
		Damage = curGunData->Damage;
		//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString::Printf(TEXT("Armo IS %d"), curGunData->Armo));
	}
	else {
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("No Find"));
	}
}

void AClickPlayerController::Reloading(float deltaTime)
{
	curReloadTime -= deltaTime;
	if (curReloadTime <= 0)
	{
		bReload = false;
		curReloadTime = ReloadTime;
		cur_Armo = Armo;
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Reloaded"));
	}
}

void AClickPlayerController::SetSkill(int32 s1, int32 s2, int32 s3)
{
	Armo = Armo + curGunData->Armo * 0.2 *s1;
	RPM = RPM - curGunData->RPM * 0.1 * s1;
}

void AClickPlayerController::SetOverlapSkillZone_true()
{
	bOverlapSkillZone = true;      
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Skill True"));

}

void AClickPlayerController::SetOverlapSkillZone_false()
{
	bOverlapSkillZone = false;
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Overlap Skill false"));
}

void AClickPlayerController::CoolDown(float deltaTime)
{
	coolTime -= deltaTime;
	if (coolTime <= 0)
	{
		CoolDownFalse();
		coolTime = RPM;
	}
}


