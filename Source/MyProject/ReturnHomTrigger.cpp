
#include "ReturnHomTrigger.h"

#include "MyGameInstance.h"
#include "MyCharacter.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"

AReturnHomTrigger::AReturnHomTrigger()
{
	PrimaryActorTick.bCanEverTick = false;
	PlatformSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("PlatformSceneRoot"));
	RootComponent = PlatformSceneRoot;

	PlatformCollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("PlatformCollisionBox"));
	PlatformCollisionBox->SetupAttachment(PlatformSceneRoot);
}

void AReturnHomTrigger::BeginPlay()
{
	Super::BeginPlay();
	
}

void AReturnHomTrigger::ActivateTrigger(AActor* OtherActor)
{
	if (!OtherActor) return;
	
	UGameInstance* inst = GetGameInstance();
	UMyGameInstance* DemoInst = Cast<UMyGameInstance>(inst);
	if (DemoInst == nullptr) return;
	
	DemoInst->SetIsQuestCompleted();
	
	UGameplayStatics::OpenLevel(GetWorld(), "Village");
}
