// // Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseItem.h"
#include "Engine/GameInstance.h"
#include "MyGameInstance.generated.h"

UCLASS()
class MYPROJECT_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	// INVENTORY
	UFUNCTION(BlueprintCallable)
	TArray<TSubclassOf<UBaseItem>> GetInventory();

	UFUNCTION(BlueprintCallable)
	int GetItemCount(TSubclassOf<UBaseItem> Item);

	UFUNCTION(BlueprintCallable)
	void UseItem(AAvatar* User);

	UFUNCTION(BlueprintCallable)
	void AddItemToInventory(UBaseItem* Item);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	TSubclassOf<UBaseItem> GetItemInHand() const { return m_ItemInHand; }

	UFUNCTION(BlueprintCallable)
	void SetItemInHand(TSubclassOf<UBaseItem> _item) { m_ItemInHand = _item; }

	// QUEST
	UFUNCTION(BlueprintCallable)
	void ResetGameCompletion();

	UFUNCTION(BlueprintCallable)
	bool IsQuestCompleted();

	UFUNCTION(BlueprintCallable)
	FTransform GetPlayerTransformBeforeQuest();

	void SetIsQuestCompleted();

	void SetPlayerTransformBeforeQuest(FTransform Transform);

private:
	TSubclassOf<UBaseItem> m_ItemInHand;
	TArray<TSubclassOf<UBaseItem>> Inventory;
	bool QuestCompleted;
	FTransform PlayerTransformBeforeQuest;
};
