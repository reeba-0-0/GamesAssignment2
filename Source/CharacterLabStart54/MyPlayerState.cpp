#include "MyPlayerState.h"
#include <Net/UnrealNetwork.h>
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"

AMyPlayerState::AMyPlayerState()
{

}

void AMyPlayerState::ActivateCheckPoint()
{
    bReachedCheckpoint = currentCheckpoint < maxCheckpoint;

    if (bReachedCheckpoint)
    {
        currentCheckpoint++;

        ReplenishHealth();


        //LOGGING
        UE_LOG(LogTemp, Log, TEXT("current checkpoint: %d"), currentCheckpoint);

        FString Output = TEXT("Current Checkpoint: ") + FString::FromInt(currentCheckpoint);

        GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, Output);
    }
}

void AMyPlayerState::ReduceHealth()
{
    currentHealth -= 10;

    if (currentHealth <= 0.0f && GetWorld())
    {
        APlayerController* PC = Cast<APlayerController>(GetOwner());
        if (PC)
        {
            // Travel just this player to the Lose level
            PC->ClientTravel("/Game/LoseLevel", ETravelType::TRAVEL_Absolute);
            UE_LOG(LogTemp, Warning, TEXT("Player %s has been sent to Lose Level."), *GetPlayerName());
        }
    }
}

int AMyPlayerState::GetHealth()
{
    return currentHealth;
}

bool AMyPlayerState::NoHealthLeft()
{
    return currentHealth <= 0;
}

void AMyPlayerState::KillPlayer()
{
    if (HasAuthority())
    {
        if (currentHealth <= 0.f)
        {
            Destroy();
        }
    }
}


void AMyPlayerState::ReplenishHealth()
{
    currentHealth = maxHealth;
}

bool AMyPlayerState::IsMaxCheckPoint()
{
    return currentCheckpoint >= maxCheckpoint;
}

// replication settings
void AMyPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(AMyPlayerState, currentHealth);
    //DOREPLIFETIME(AMyPlayerState, maxHealth);
    DOREPLIFETIME(AMyPlayerState, currentCheckpoint);
    //DOREPLIFETIME(AMyPlayerState, maxCheckpoint);
}

//void AMyPlayerState::MulticastActivateNiagaraEffect_Implementation()
//{
//    if (niagaraComponent)
//    {
//        niagaraComponent->Activate(); // Trigger the effect
//    }
//}



