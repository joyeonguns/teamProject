// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
// ĸ�� ������Ʈ ���
#include <Engine/Classes/Components/CapsuleComponent.h>
// ī�޶� ����
#include <Engine/Classes/Camera/CameraComponent.h>
// ��Ʈ�ѷ�
#include <Engine/Classes/GameFramework/CharacterMovementComponent.h>
// ������ �� ����
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
	// BeginPlay() �Լ� ���Ŀ� Tick()�Լ� ����
	PrimaryActorTick.bStartWithTickEnabled = true;

	GetCapsuleComponent()->InitCapsuleSize(42.0f, 96.0f); // ĸ�� ������Ʈ�� Ű�� ����

	// ĳ���Ͱ� ī�޶��� ȸ���� ������ ����
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	// ĳ���Ͱ� �����϶� ���� ������ �ٶ󺻴�
	GetCharacterMovement()->bOrientRotationToMovement = true;
	// ĳ������ ȸ���ӵ��� �ʴ� 640���� ȸ���ӵ��� ������.
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 640.0f, 0.0f);
	// ĳ���Ͱ� ��鸸 ������
	GetCharacterMovement()->bConstrainToPlane = true;
	// ĳ���Ͱ� ��鿡 �پ ����
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	// ������ �� ����
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraSpringArm"));
	// ������ �� �ʱ�ȭ
	SpringArmComponent->SetupAttachment(RootComponent);
	// ������ ���� ȸ���� ��Ʈ, ���� ������Ʈ�� �������ʰ� ���� ��ǥ�踦 ������. 
	SpringArmComponent->SetUsingAbsoluteRotation(true);
	// ī�޶�� ĳ���ͻ����� �Ÿ� 800.0f;
	SpringArmComponent->TargetArmLength = 1200.0f;
	// ������ ���� ȸ����
	SpringArmComponent->SetRelativeRotation(FRotator(-60.0f, 45.0f, 0.0f));
	// ī�޶� ���� �հ� ���� ����
	SpringArmComponent->bDoCollisionTest = false;

	// ī�޶� ������Ʈ ����
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	// ī�޶� ������Ʈ �ʱ�ȭ
	CameraComponent->SetupAttachment(SpringArmComponent, USpringArmComponent::SocketName);
	// ���� ȸ���� ī�޶�ȸ���� ������ �ȹ�ħ
	CameraComponent->bUsePawnControlRotation = false;

	MaxHP = 100.f;
	curHP = MaxHP;		

	ItemArray[0] = 1;
	ItemAmount.Emplace(1, 1);

	ItemArray[3] = 4;
	ItemAmount.Emplace(4, 1);

	/*static ConstructorHelpers::FObjectFinder<UGunData> GunStructObject(TEXT("DataTable'/Game/DataTable/GunDataTable.GunDataTable'"));
	if (GunStructObject.Succeeded()) {
		GunDataTable = GunStructObject.Object;
	}*/


	MaxGold = 1000;
	CurGold = MaxGold;
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

	curHP += HpRegen * DeltaTime;
	if (curHP >= 100)
		curHP = 100;

	if (state == "Poison") {
		curHP -= PoisonDamage * DeltaTime;
		PoisonTime -= 1 * DeltaTime;
		if (PoisonTime <= 0) {
			PoisonTime = 0;
			PoisonDamage = 0;
			state = "Nomal";
		}
		
	}
	else if (state == "Buff") {
		BuffTime -= 1 * DeltaTime;
		if (BuffTime <= 0) {
			BuffTime = 0;
			HpRegen = 0;
			state = "Nomal";
		}
	}
}

void APlayerCharacter::NotifyActorBeginOverlap(AActor* OtherActor)
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Search Item"));
	if (OtherActor->ActorHasTag("ItemBox")) {
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Overrap Item"));
		OverrapItemBox_True();
		ItemBox = Cast<ADropBox>(OtherActor);
	}
}

void APlayerCharacter::NotifyActorEndOverlap(AActor* OtherActor)
{
	if (OtherActor->ActorHasTag("ItemBox")) {
		OverrapItemBox_False();
	}
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAction("Action", IE_Pressed, this, &APlayerCharacter::InputActionPress);
	// Action_1 ������� InputAction_1released ����
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
		//DropItemBox();
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Player_DEAD!!!")));
		//this->Destroy();
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
	// ��ų 1
	GetCharacterMovement()->MaxWalkSpeed = 600 +s1_level*100;	
	
	// ��ų 2

	// ��ų 3

	// ��ų 4

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
	/*int j = 0;
	for (int i : ItemArray) {
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("" + FString::FromInt(j) + " : " + FString::FromInt(i)));
		j++;
	}*/
	
	int32 getItem = ItemBox->GetItemCode();
	int32 num = 0;
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("num : " + FString::FromInt(num)));


	//ItemAmount[1] += 1;

	if (ItemArray.Find(getItem, num) && getItem !=0) {
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Item++"));
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Item : " + FString::FromInt(num)));
		//ItemAmount[num] = ItemAmount[num] + 1;
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


