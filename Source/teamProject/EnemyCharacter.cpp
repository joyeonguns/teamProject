// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCharacter.h"
#include "GameplayTagContainer.h"
#include "GameplayTagsManager.h"
// 캡슐 컴포넌트 사용
#include <Engine/Classes/Components/CapsuleComponent.h>
#include "Components/SkeletalMeshComponent.h"
#include "Components/WidgetComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Enemy_Chat_UserWidget.h"
#include "Engine.h"

// Sets default values
AEnemyCharacter::AEnemyCharacter() 
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	maxHp = 100.0f;
	curHp = maxHp;

	// "Chating" 이라는 이름의 UI 서브오브젝트 Widget_Component 추가
	Widget_Component = CreateDefaultSubobject<UWidgetComponent>(TEXT("Chating"));

	// Widget_Component가 존재하면 실행
	if (Widget_Component)
	{
		// Ui를 오브젝트에 붙힘
		Widget_Component->SetupAttachment(RootComponent);
		Widget_Component->SetWidgetSpace(EWidgetSpace::Screen);
		Widget_Component->SetRelativeLocation(FVector(0.f, 0.f, 0.f));
		// EnemyUI 블루프린트 받음
		static ConstructorHelpers::FClassFinder<UUserWidget>widget_class(TEXT("/Game/UI/BP_EnemyUI"));
		if (widget_class.Succeeded()) {
			// 위젯 클래스 할당
			Widget_Component->SetWidgetClass(widget_class.Class);
		}
	}
}

// Called when the game starts or when spawned
void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Arrive!!"), curHp));
}

// Called every frame
void AEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);	
	// Widget_Component 형변환
	auto const uw = Cast<UEnemy_Chat_UserWidget>(Widget_Component->GetUserWidgetObject());
	if (uw) {
		// EnemyChat UI의 Set_EnemyChat 함수 호출
		uw->Set_EnemyChat(FString(" Patroll "));
	}

	if (curHp >= 100)
		curHp = 100;

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

// Called to bind functionality to input
void AEnemyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AEnemyCharacter::NotifyActorBeginOverlap(AActor* OtherActor)
{
	// ice Overlap On
	if (OtherActor->ActorHasTag("ice")) {
		bOvelap_ice = true;
	}
	// 독 Overlap On
	if (OtherActor->ActorHasTag("poison")) {
		bOvelap_Poison = true;
	}
}

void AEnemyCharacter::NotifyActorEndOverlap(AActor* OtherActor)
{
	// ice Overlap Off
	if (OtherActor->ActorHasTag("ice")) {
		bOvelap_ice = false;
	}
	// 독 Overlap Off
	if (OtherActor->ActorHasTag("poison")) {
		bOvelap_Poison = false;
	}
}


float AEnemyCharacter::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCasual)
{
	const float getDamage = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCasual);

	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Hit!!"), curHp));
	if (curHp <= Damage) {
		
		Dead();
	}
	else {
		curHp -= getDamage;
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("HP IS %f"), curHp));
	}
	return getDamage;
}

void AEnemyCharacter::DropItemBox()
{
	int random;
	random = rand() % 100;
	if (1) {
		UWorld* world = GetWorld();

		if (world) {
			FVector spwLocation = this->GetActorLocation();
			FRotator spwRotation = { 0,0,0 };

			FActorSpawnParameters spwParameter;
			spwParameter.Owner = this;
			spwParameter.Instigator = GetInstigator();


			ADropBox* ItemBox = world->SpawnActor<ADropBox>(DropBoxClass, spwLocation, spwRotation, spwParameter);

			if (ItemBox) {
				ItemBox->SetItem(itemCode,GunCode);
				
			}
		}
	}
}

void AEnemyCharacter::ApplyPoison(float _dmg)
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

void AEnemyCharacter::Poison_ing(float deltaTime)
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
		curHp -= PoisonDmg * deltaTime;
		if (curHp <= 0)
			Dead();
	}
}

void AEnemyCharacter::ApplyBuff()
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

void AEnemyCharacter::Buff_ing(float deltaTime)
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
		curHp += BuffRegen * deltaTime;
	}
}

void AEnemyCharacter::ApplyIce()
{
	// 최초 적용
	if (bstate_ice == false) {
		amuSpeed = GetCharacterMovement()->MaxWalkSpeed * 0.5f;
		GetMesh()->SetMaterial(0, ice_Material);
		bstate_ice = true;
	}

	iceDur = 3.0f;
}

void AEnemyCharacter::Ice_ing(float deltaTime)
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

void AEnemyCharacter::Dead()
{
	DropItemBox();
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Enemy_DEAD!!!")));
	this->Destroy();
}

