// Fill out your copyright notice in the Description page of Project Settings.


#include "FallOffLevel.h"
#include "MyCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include <Components/BoxComponent.h>
#include "MyPlayerState.h"

// Sets default values
AFallOffLevel::AFallOffLevel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	triggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	RootComponent = triggerBox;

	// Register the overlap event
	triggerBox->OnComponentBeginOverlap.AddDynamic(this, &AFallOffLevel::OnOverlapBegin);

}

// Called when the game starts or when spawned
void AFallOffLevel::BeginPlay()
{
	Super::BeginPlay();
 
}

// Called every frame
void AFallOffLevel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFallOffLevel::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
    bool bFromSweep, const FHitResult& SweepResult)
{
    if (HasAuthority() && OtherActor)
    {
        if (OtherActor)
        {
            UE_LOG(LogTemp, Warning, TEXT("%s fell out of the level!"), *OtherActor->GetName());

            // cast to character
            auto player = Cast<AMyCharacter>(OtherActor);
            player->bFalling = true;
            
            if (player)
            {
                //player->bFalling = true;
                // set respawn offset of a random value
                FVector respawnOffset = FVector(FMath::RandRange(-50, 50), FMath::RandRange(-50, 50), 0);
                
                // set location to last player location + offset
                FVector respawnLocation = player->lastPos + respawnOffset;

               /* UE_LOG(LogTemp, Warning, TEXT("Respawn Location: %`s"), *respawnLocation.ToString());*/

                player->SetActorLocation(respawnLocation); // move player to new location
                player->Client_PlaySound(); // play sound on respawn
            }
        }
    }

    if (OtherActor)
    {
        auto player = Cast<AMyCharacter>(OtherActor);

        AMyPlayerState* playerState = Cast<AMyPlayerState>(player->GetPlayerState());
        if (playerState)
        {
            playerState->ReduceHealth();
            int health = playerState->GetHealth();

        }
    }
}
