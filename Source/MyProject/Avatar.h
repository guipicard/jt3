// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CharacterAttribute.h"
#include "CoreMinimal.h"
#include "MyGameInstance.h"
#include "GameFramework/Character.h"
#include "Avatar.generated.h"

class UBaseItem;
UCLASS()
class MYPROJECT_API AAvatar : public ACharacter
{
	GENERATED_BODY()

public:
	AAvatar();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class UCharacterAttribute* Attributes;

	UFUNCTION(BlueprintCallable)
	float GetHealth();
	UFUNCTION(BlueprintCallable)
	float GetMaxHealth();
	UFUNCTION(BlueprintCallable)
	float GetPercentHealth();
	UFUNCTION(BlueprintCallable)
	UTexture2D* GetPortrait();

	UPROPERTY(EditAnywhere)
	USoundBase* ThudSound;

	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	UFUNCTION(BlueprintCallable)
	TArray<TSubclassOf<UBaseItem>> GetGameInventory();

	UFUNCTION(BlueprintCallable)
	int GetItemCount(TSubclassOf<UBaseItem> _item);

	void Heal(float hp);
	
private:
	float CurrentHealth;

protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent)
	void OnUpdateHealth();
};
