// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
// 캡슐 컴포넌트 사용
#include <Engine/Classes/Components/CapsuleComponent.h>
// 카메라 설정
#include <Engine/Classes/Camera/CameraComponent.h>
// 컨트롤러
#include <Engine/Classes/GameFramework/CharacterMovementComponent.h>
// 스프링 암 설정
#include <Engine/Classes/GameFramework/SpringArmComponent.h>
#include "Perception/AISense_Sight.h"
#include "ClickPlayerController.h"
#include "Components/InputComponent.h"
#include "teamProjectGameModeBase.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{ 	
	setStimulus();
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// BeginPlay() 함수 이후에 Tick()함수 실행
	PrimaryActorTick.bStartWithTickEnabled = true;

	GetCapsuleComponent()->InitCapsuleSize(42.0f, 96.0f); // 캡슐 컴포넌트의 키기 설정

	// 캐릭터가 카메라의 회전을 따르지 않음
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	// 캐릭터가 움직일때 진행 방향을 바라본다
	GetCharacterMovement()->bOrientRotationToMovement = true;
	// 캐릭터의 회전속도가 초당 640도의 회전속도를 가진다.
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 640.0f, 0.0f);
	// 캐릭터가 평면만 움직임
	GetCharacterMovement()->bConstrainToPlane = true;
	// 캐릭터가 평면에 붙어서 시작
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	// 스프링 암 생성
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraSpringArm"));
	// 스프링 암 초기화
	SpringArmComponent->SetupAttachment(RootComponent);
	// 스프링 암의 회전이 루트, 상위 컴포넌트에 따르지않고 월드 좌표계를 따른다. 
	SpringArmComponent->SetUsingAbsoluteRotation(true);
	// 카메라와 캐릭터사이의 거리 800.0f;
	SpringArmComponent->TargetArmLength = 1200.0f;
	// 스프링 암의 회전값
	SpringArmComponent->SetRelativeRotation(FRotator(-60.0f, 45.0f, 0.0f));
	// 카메라가 벽을 뚫고 갈지 말지
	SpringArmComponent->bDoCollisionTest = false;

	// 카메라 컴포넌트 생성
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	// 카메라 컴포넌트 초기화
	CameraComponent->SetupAttachment(SpringArmComponent, USpringArmComponent::SocketName);
	// 폰의 회전이 카메라회전에 영향을 안미침
	CameraComponent->bUsePawnControlRotation = false;

	MaxHP = 100.f;
	curHP = MaxHP;		

	ItemArray[0] = 1;
	ItemAmount.Emplace(1, 1);

	ItemArray[3] = 4;
	ItemAmount.Emplace(4, 1);

	
	// 세팅
	MaxGold = 1000;
	CurGold = MaxGold;

	//	
	
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// 최대 채력
	//curHP += HpRegen * DeltaTime;
	if (curHP >= 100)
		curHP = 100;

	// Poison Apply
	if (bOvelap_Poison == true) {
		ApplyPoison(5.0);
		bOvelap_Poison = false;
	}
	// Poison 상태
	if (bstate_Poison == true) {
		Poison_ing(DeltaTime);
	}

	// ice Apply
	if (bOvelap_ice == true) {
		ApplyIce();
		bOvelap_ice = false;
	}
	// ice 상태
	if (bstate_ice == true) {
		Ice_ing(DeltaTime);
	}

	// Buff Apply
	if (bOvelap_Buff == true) {
		ApplyBuff();
		bOvelap_Buff = false;
	}
	// Buff 상태
	if (bstate_Buff == true) {
		Buff_ing(DeltaTime);
	}
}

void APlayerCharacter::NotifyActorBeginOverlap(AActor* OtherActor)
{
	// 아이템 박스획득
	if (OtherActor->ActorHasTag("ItemBox")) {
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Overrap Item"));
		OverrapItemBox_True();
		ItemBox = Cast<ADropBox>(OtherActor);
	}
	// ice Overlap On
	if (OtherActor->ActorHasTag("ice")) {
		bOvelap_ice = true;
	}
	// 독 Overlap On
	if (OtherActor->ActorHasTag("poison")) {
		bOvelap_Poison = true;
	}
}

void APlayerCharacter::NotifyActorEndOverlap(AActor* OtherActor)
{
	if (OtherActor->ActorHasTag("ItemBox")) {
		OverrapItemBox_False();
	}
	// ice Overlap Off
	if (OtherActor->ActorHasTag("ice")) {
		bOvelap_ice = false;
	}
	// 독 Overlap Off
	if (OtherActor->ActorHasTag("poison")) {
		bOvelap_Poison = false;
	}
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAction("Action", IE_Pressed, this, &APlayerCharacter::InputActionPress);
	// Action_1 릴리즈시 InputAction_1released 실행
	PlayerInputComponent->BindAction("Action", IE_Released, this, &APlayerCharacter::InputActionreleased);
}

void APlayerCharacter::setStimulus()
{
	stimulus = CreateDefaultSubobject<UAIPerceptionStimuliSourceComponent>(TEXT("stimulus"));
	stimulus->RegisterForSense(TSubclassOf<UAISense_Sight>());
	stimulus->RegisterWithPerceptionSystem();
}

void APlayerCharacter::InputActionPress()
{
	bActionKey = true;
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Action"));
	if (bOverrapItemBox == true) {
		GetItem();
	}
}

void APlayerCharacter::InputActionreleased()
{
	bActionKey = false;
}

void APlayerCharacter::OverrapItemBox_True()
{
	bOverrapItemBox = true;
}

void APlayerCharacter::OverrapItemBox_False()
{
	bOverrapItemBox = false;
}

float APlayerCharacter::GetHP()
{
	return curHP;
}

void APlayerCharacter::SetHP(float value)
{
	curHP = value;
}

float APlayerCharacter::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCasual)
{
	const float getDamage = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCasual);

	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Hit!!"), curHp));
	if (curHP <= 0) {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Player_DEAD!!!")));
		Dead();
	}
	else {
		curHP -= getDamage;
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("HP IS %f"), curHP));
	}
	return getDamage;
}

void APlayerCharacter::SetSkill()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("set-skill"));
	// 스킬 1
	GetCharacterMovement()->MaxWalkSpeed = 600 +s1_level*100;	
	
	// 스킬 2

	// 스킬 3

	// 스킬 4

	AClickPlayerController* PlayerContRoller = Cast<AClickPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	PlayerContRoller->SetSkill(s1_level, s1_level, s1_level);
}

void APlayerCharacter::Dead()
{
	GetMesh()->SetCollisionProfileName(TEXT("Regdoll"));
	GetMesh()->SetSimulatePhysics(true);
	AteamProjectGameModeBase* GameMode = Cast<AteamProjectGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	GameMode->ChangeSideWidget(GameMode->GetDeadWidget());
}

void APlayerCharacter::GetItem()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Get Item"));
	
	int32 getItem = ItemBox->GetItemCode();
	int32 num = 0;
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("num : " + FString::FromInt(num)));


	if (ItemArray.Find(getItem, num) && getItem !=0) {
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Item++"));
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Item : " + FString::FromInt(num)));
		
		ItemAmount[getItem] += 1;
	}
	else {
		num++;
		for (int i : ItemArray) {
			if (i == 0) {
				GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("i : " + FString::FromInt(i)));
				break;
			}
			num++;
		}
		if (num < 4) {
			ItemArray[num] = getItem;
			ItemAmount.Emplace(getItem, 1);
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("New Item"));
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("num : " + FString::FromInt(num)));
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("code : " + FString::FromInt(getItem)));
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Amount : " + FString::FromInt(ItemAmount[getItem])));
		}
	}
	


	ItemBox->Destroy();
}

void APlayerCharacter::ApplyPoison(float _dmg)
{
	// 최초 적용
	if (bstate_Poison == false) {
		// 중독 설정
		GetMesh()->SetMaterial(0, poison_Material);
		bstate_Poison = true;
	}

	// 중독 갱신	
	PoisonDur = 5.0f;
	PoisonDmg = _dmg;
	state = "Poison";
}

void APlayerCharacter::Poison_ing(float deltaTime)
{
	// 중독 시간
	PoisonDur -= deltaTime;
	
	if (0 >= PoisonDur) {
		// 중독 해제
		bstate_Poison = false;
		if (state == "Poison") {
			// 중독 상태 해제
			state = "nomal";			
			GetMesh()->SetMaterial(0, nomal_Material);
		}						
		// 중독 데미지 초기화
		PoisonDmg = 0;
	}
	else {
		// 중독 데미지	처리
		curHP -= PoisonDmg * deltaTime;
		if (curHP <= 0)
			Dead();
	}
}

void APlayerCharacter::ApplyBuff()
{
	// 최초 적용
	if (bstate_Buff == false) {
		// 버프 설정
		GetMesh()->SetMaterial(0, buff_Material);
		bstate_Buff = true;
	}

	// 버프 적용	
	BuffDur = 10.0f;
	BuffRegen = 5.0f;
	state = "Buff";
}

void APlayerCharacter::Buff_ing(float deltaTime)
{
	// 버프 시간
	BuffDur -= deltaTime;

	if (0 >= BuffDur) {
		// 버프 해제
		bstate_Buff = false;
		if (state == "Buff") {
			// 버프 상태 해제
			state = "nomal";			
			GetMesh()->SetMaterial(0, nomal_Material);
		}			
		// 버프 리젠 초기화
		BuffRegen = 0;
	}
	else {
		// 버프 리젠	처리
		curHP += BuffRegen * deltaTime;
	}
}

void APlayerCharacter::ApplyIce()
{
	// 최초 적용
	if (bstate_ice == false) {
		amuSpeed = GetCharacterMovement()->MaxWalkSpeed * 0.5f;
		GetMesh()->SetMaterial(0, ice_Material);
		bstate_ice = true;
	}
	
	iceDur = 3.0f;
}

void APlayerCharacter::Ice_ing(float deltaTime)
{
	iceDur -= deltaTime;

	if (0 >= iceDur) {
		GetCharacterMovement()->MaxWalkSpeed += amuSpeed;
		GetMesh()->SetMaterial(0, nomal_Material);
		bstate_ice = false;
	}
	else {
		GetCharacterMovement()->MaxWalkSpeed = amuSpeed;
	}
}



