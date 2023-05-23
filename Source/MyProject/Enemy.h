// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../../../../../../../../../Program Files (x86)/Windows Kits/10/Include/10.0.19041.0/um/Audioclient.h"
#include "GameFramework/Character.h"
#include "Enemy.generated.h"

UCLASS()
class MYPROJECT_API AEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	AEnemy();

protected:
	virtual void BeginPlay() override;

public:
	bool IsDead() const { return m_Dead; }
	void AttackTarget();
	// void MoveToLocation(const FVector& Vector);
	void ChaseTarget();
	virtual void Tick(float DeltaTime) override;
	void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent);

	UPROPERTY(BlueprintReadWrite)
	float attackRange;

	UFUNCTION(BlueprintImplementableEvent)
	void Attack(AActor* _target);

	
	UPROPERTY(BlueprintReadWrite)
	AActor* m_Target;
private:
	float m_Elapsed;
	bool m_Dead;
	bool m_Move;
};
