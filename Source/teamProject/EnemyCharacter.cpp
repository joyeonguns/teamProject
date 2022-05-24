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
}

// Called to bind functionality to input
void AEnemyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


float AEnemyCharacter::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCasual)
{
	const float getDamage = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCasual);

	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Hit!!"), curHp));
	if (curHp <= Damage) {
		DropItemBox();
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Enemy_DEAD!!!")));
		this->Destroy();
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

