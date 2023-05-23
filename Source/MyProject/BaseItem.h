#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "BaseItem.generated.h"

UCLASS(BlueprintType, Blueprintable)
class MYPROJECT_API UBaseItem : public UObject
{
	GENERATED_BODY()

public:

	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item")
	UTexture2D* m_Icon;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
	FText m_Name;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item", meta = (MultiLine = true))
	FText m_Description;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
	UStaticMesh* m_Mesh;

	
	virtual void Use(AActor* User);

	UFUNCTION(BlueprintImplementableEvent)
	void OnPickup(UMyGameInstance* GameInstance);

	UPROPERTY(BlueprintReadWrite, Category = "Item")
	AActor* m_Container;
	
};
