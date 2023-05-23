// Fill out your copyright notice in the Description page of Project Settings.

#include "Avatar.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundBase.h"

// Sets default values
AAvatar::AAvatar()
	: CurrentHealth(0.0f)
{
	PrimaryActorTick.bCanEverTick = false;
}

float AAvatar::GetHealth()
{
	return CurrentHealth;
}

float AAvatar::GetMaxHealth()
{
	if (IsValid(Attributes))
	{
		return Attributes->MaxHealth;
	}
	return 0.0f;
}

float AAvatar::GetPercentHealth()
{
	if (IsValid(Attributes))
	{
		if (Attributes->MaxHealth > 0)
		{
			return CurrentHealth / Attributes->MaxHealth;
		}
	}
	return 0.0f;
}

UTexture2D* AAvatar::GetPortrait()
{
	if (IsValid(Attributes))
	{
		return Attributes->Portrait;
	}
	return nullptr;
}

float AAvatar::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	
	float MaxHealth = GetMaxHealth();
	CurrentHealth = FMath::Clamp(CurrentHealth - Damage, 0.0f, MaxHealth);

	OnUpdateHealth();

	if (IsValid(ThudSound))
    {
		UGameplayStatics::PlaySoundAtLocation(this, ThudSound, GetActorLocation());
    }

	if (GetHealth() >= 0.0f)
	{
		
	}
	return Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);
}

TArray<TSubclassOf<UBaseItem>>AAvatar::GetGameInventory()
{
	UGameInstance* Inst = GetGameInstance();
	if (!Inst) return TArray<TSubclassOf<UBaseItem>>{};
	UMyGameInstance* DemoInst = Cast<UMyGameInstance>(Inst);
	if (!DemoInst) return TArray<TSubclassOf<UBaseItem>>{};

	TArray<TSubclassOf<UBaseItem>> inv = DemoInst->GetInventory();

	return inv;
}

int AAvatar::GetItemCount(TSubclassOf<UBaseItem> _item)
{
	UGameInstance* Inst = GetGameInstance();
	if (!Inst) return 0;
	UMyGameInstance* DemoInst = Cast<UMyGameInstance>(Inst);
	if (!DemoInst) return 0;

	
	int count = DemoInst->GetItemCount(_item);
	
	return count;
}

void AAvatar::Heal(float hp)
{
	CurrentHealth += hp;
	if (CurrentHealth > Attributes->MaxHealth)
	{
		CurrentHealth = Attributes->MaxHealth;
	}
	OnUpdateHealth();
}


void AAvatar::BeginPlay()
{
	CurrentHealth = GetMaxHealth();
	Super::BeginPlay();
}
