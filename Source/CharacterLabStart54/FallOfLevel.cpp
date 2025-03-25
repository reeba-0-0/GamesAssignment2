// Fill out your copyright notice in the Description page of Project Settings.


#include "FallOfLevel.h"
#include "MyCharacter.h"
#include <Components/BoxComponent.h>

// Sets default values
AFallOfLevel::AFallOfLevel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	RootComponent = TriggerBox;

	// Register the overlap event
	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &AFallOfLevel::OnOverlapBegin);

}

// Called when the game starts or when spawned
void AFallOfLevel::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFallOfLevel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFallOfLevel::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult& SweepResult)
{
    if (HasAuthority() && OtherActor)
    {
        UE_LOG(LogTemp, Warning, TEXT("%s fell out of the level!"), *OtherActor->GetName());

		//cast to my character
		auto player = Cast<AMyCharacter>(OtherActor);

		if (player)
		{
			player->SetActorLocation(player->LastPos);

			player->Client_PlaySound();
		}

    }
}