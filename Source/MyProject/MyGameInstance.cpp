// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"

#include "Avatar.h"
#include "MyCharacter.h"
#include "EnvironmentQuery/EnvQueryTypes.h"

TArray<TSubclassOf<UBaseItem>> UMyGameInstance::GetInventory()
{
	return Inventory;
}

int UMyGameInstance::GetItemCount(TSubclassOf<UBaseItem> _item)
{
	if (Inventory.Num() == 0) return 0;
	int i = 0;
	for (auto item : Inventory)
	{
		if (item == _item)
		{
			i++;
		}
	}
	return i;
}


void UMyGameInstance::UseItem(AAvatar* User)
{
	if (m_ItemInHand == nullptr) return;
	if (&Inventory == nullptr) return;
	UBaseItem* item = Cast<UBaseItem>(m_ItemInHand.GetDefaultObject());
	if (item == nullptr) return;

	item->Use(User);
	Inventory.RemoveSingle(*m_ItemInHand);
	Inventory.Shrink();
	if (Inventory.Num() != 0)
	{
		const TSubclassOf<UBaseItem> firstItem = Inventory[0];
		if (!firstItem) return;
		m_ItemInHand = firstItem;
	}
	else
	{
		m_ItemInHand = nullptr;
	}
}

void UMyGameInstance::AddItemToInventory(UBaseItem* Item)
{
	TSubclassOf<UBaseItem> base = Item->GetClass();
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, "Press E to Interact");
	m_ItemInHand = base;
	Inventory.Add(base);
}

void UMyGameInstance::ResetGameCompletion()
{
	QuestCompleted = false;
}

bool UMyGameInstance::IsQuestCompleted()
{
	return QuestCompleted;
}

FTransform UMyGameInstance::GetPlayerTransformBeforeQuest()
{
	return PlayerTransformBeforeQuest;
}

void UMyGameInstance::SetIsQuestCompleted()
{
	QuestCompleted = true;
}

void UMyGameInstance::SetPlayerTransformBeforeQuest(FTransform Transform)
{
	PlayerTransformBeforeQuest = Transform;
}
