// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"
#include "AIController.h"
#include "Avatar.h"
#include "GameFramework/DamageType.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AEnemy::AEnemy()
	: m_Elapsed(0.0f)
	  , m_Dead(false)
	  , m_Target(false)
	  , m_Move(false)
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();
}

void AEnemy::AttackTarget()
{
	if ((m_Target->GetActorLocation() - GetActorLocation()).Size() < attackRange)
	{
		ChaseTarget();
	}
	else
	{
		m_Elapsed += GetWorld()->DeltaTimeSeconds;
		if (m_Elapsed > 2.0f)
		{
			Attack(m_Target);
			m_Elapsed = 0;
		}
	}
}

void AEnemy::ChaseTarget()
{
	m_Move = true;
	AEnemy* _ai = Cast<AEnemy>(GetController());
	// _ai->MoveToLocation(m_Target->GetActorLocation());
}

void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!IsDead())
	{
		// if (m_Target != nullptr)
		// {
		// 	
		// 	AttackTarget();
		// 	
		// }
		m_Elapsed += GetWorld()->DeltaTimeSeconds;
		if (m_Elapsed > 2.0f)
		{
			UGameplayStatics::ApplyDamage(m_Target, 10.0f, Controller, this, UDamageType::StaticClass());
			
			m_Elapsed = 0;
		}
	}
}


// Called to bind functionality to input
void AEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}
