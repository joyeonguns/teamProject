// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCharacter.h"
#include "GameplayTagContainer.h"
#include "GameplayTagsManager.h"
// ĸ�� ������Ʈ ���
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

	// "Chating" �̶�� �̸��� UI ���������Ʈ Widget_Component �߰�
	Widget_Component = CreateDefaultSubobject<UWidgetComponent>(TEXT("Chating"));

	// Widget_Component�� �����ϸ� ����
	if (Widget_Component)
	{
		// Ui�� ������Ʈ�� ����
		Widget_Component->SetupAttachment(RootComponent);
		Widget_Component->SetWidgetSpace(EWidgetSpace::Screen);
		Widget_Component->SetRelativeLocation(FVector(0.f, 0.f, 0.f));
		// EnemyUI �������Ʈ ����
		static ConstructorHelpers::FClassFinder<UUserWidget>widget_class(TEXT("/Game/UI/BP_EnemyUI"));
		if (widget_class.Succeeded()) {
			// ���� Ŭ���� �Ҵ�
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
	// Widget_Component ����ȯ
	auto const uw = Cast<UEnemy_Chat_UserWidget>(Widget_Component->GetUserWidgetObject());
	if (uw) {
		// EnemyChat UI�� Set_EnemyChat �Լ� ȣ��
		uw->Set_EnemyChat(FString(" Patroll "));
	}

	if (curHp >= 100)
		curHp = 100;

	// Poison Apply
	if (bOvelap_Poison == true) {
		ApplyPoison(5.0);
		bOvelap_Poison = false;
	}
	// Poison ����
	if (bstate_Poison == true) {
		Poison_ing(DeltaTime);
	}

	// ice Apply
	if (bOvelap_ice == true) {
		ApplyIce();
		bOvelap_ice = false;
	}
	// ice ����
	if (bstate_ice == true) {
		Ice_ing(DeltaTime);
	}

	// Buff Apply
	if (bOvelap_Buff == true) {
		ApplyBuff();
		bOvelap_Buff = false;
	}
	// Buff ����
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
	// �� Overlap On
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
	// �� Overlap Off
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
	// ���� ����
	if (bstate_Poison == false) {
		// �ߵ� ����
		GetMesh()->SetMaterial(0, poison_Material);
		bstate_Poison = true;
	}

	// �ߵ� ����	
	PoisonDur = 5.0f;
	PoisonDmg = _dmg;
	state = "Poison";
}

void AEnemyCharacter::Poison_ing(float deltaTime)
{
	// �ߵ� �ð�
	PoisonDur -= deltaTime;

	if (0 >= PoisonDur) {
		// �ߵ� ����
		bstate_Poison = false;
		if (state == "Poison") {
			// �ߵ� ���� ����
			state = "nomal";
			GetMesh()->SetMaterial(0, nomal_Material);
		}
		// �ߵ� ������ �ʱ�ȭ
		PoisonDmg = 0;
	}
	else {
		// �ߵ� ������	ó��
		curHp -= PoisonDmg * deltaTime;
		if (curHp <= 0)
			Dead();
	}
}

void AEnemyCharacter::ApplyBuff()
{
	// ���� ����
	if (bstate_Buff == false) {
		// ���� ����
		GetMesh()->SetMaterial(0, buff_Material);
		bstate_Buff = true;
	}

	// ���� ����	
	BuffDur = 10.0f;
	BuffRegen = 5.0f;
	state = "Buff";
}

void AEnemyCharacter::Buff_ing(float deltaTime)
{
	// ���� �ð�
	BuffDur -= deltaTime;

	if (0 >= BuffDur) {
		// ���� ����
		bstate_Buff = false;
		if (state == "Buff") {
			// ���� ���� ����
			state = "nomal";
			GetMesh()->SetMaterial(0, nomal_Material);
		}
		// ���� ���� �ʱ�ȭ
		BuffRegen = 0;
	}
	else {
		// ���� ����	ó��
		curHp += BuffRegen * deltaTime;
	}
}

void AEnemyCharacter::ApplyIce()
{
	// ���� ����
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

