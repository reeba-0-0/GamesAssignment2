// Fill out your copyright notice in the Description page of Project Settings.


#include "SafeZoneTrigger.h"
#include <Components/BoxComponent.h>
#include "MyCharacter.h"

// Sets default values
ASafeZoneTrigger::ASafeZoneTrigger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	triggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	RootComponent = triggerBox;

	// Register the overlap event
	triggerBox->OnComponentBeginOverlap.AddDynamic(this, &ASafeZoneTrigger::OnOverlapBegin);
	triggerBox->OnComponentEndOverlap.AddDynamic(this, &ASafeZoneTrigger::OnOverlapEnd);

}

// Called when the game starts or when spawned
void ASafeZoneTrigger::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASafeZoneTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASafeZoneTrigger::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (HasAuthority() && OtherActor)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s is in the safe zone"), *OtherActor->GetName());

		//cast to my character
		auto player = Cast<AMyCharacter>(OtherActor);

		if (player)
		{
			player->bInSafeZone = true;
		}

	}
}

void ASafeZoneTrigger::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) 
{
	if (HasAuthority() && OtherActor)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s is not in the safe zone"), *OtherActor->GetName());

		//cast to my character
		auto player = Cast<AMyCharacter>(OtherActor);

		if (player)
		{
			player->bInSafeZone = false;
		}

	}
}


