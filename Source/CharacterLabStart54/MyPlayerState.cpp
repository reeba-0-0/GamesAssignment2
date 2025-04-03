#include "MyPlayerState.h"
#include <Net/UnrealNetwork.h>
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"

AMyPlayerState::AMyPlayerState()
{

}


float AMyPlayerState::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
    currentHealth -= DamageAmount;
    return currentHealth;
}

void AMyPlayerState::ActivateCheckPoint()
{
    if (!HasAuthority()) return; // ensure only the server modifies replicated variables

    if (currentCheckpoint < maxCheckpoint)
    {
        bReachedCheckpoint = true;
        currentCheckpoint++;
        if (currentCheckpoint <= maxCheckpoint)
        {
            ReplenishHealth();
        }
    }

    bReachedCheckpoint = false; // de-activate after
}


// server RPC: clients must call this to activate a checkpoint
void AMyPlayerState::ServerActivateCheckPoint_Implementation()
{
    ActivateCheckPoint();
}

bool AMyPlayerState::ServerActivateCheckPoint_Validate()
{
    return true; // always return true unless you need extra validation
}

// ensure clients properly update when bReachedCheckpoint changes
void AMyPlayerState::OnRep_CheckpointReached()
{
    UE_LOG(LogTemp, Log, TEXT("Checkpoint reached! Updating client visuals."));
}



void AMyPlayerState::ReplenishHealth()
{
    currentHealth = maxHealth;
}

bool AMyPlayerState::IsMaxCheckPoint()
{
    return currentCheckpoint == maxCheckpoint;
}

// replication settings
void AMyPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(AMyPlayerState, currentHealth);
    DOREPLIFETIME(AMyPlayerState, maxHealth);
    DOREPLIFETIME(AMyPlayerState, currentCheckpoint);
    DOREPLIFETIME(AMyPlayerState, maxCheckpoint);
    DOREPLIFETIME(AMyPlayerState, bReachedCheckpoint);
}

//void AMyPlayerState::MulticastActivateNiagaraEffect_Implementation()
//{
//    if (niagaraComponent)
//    {
//        niagaraComponent->Activate(); // Trigger the effect
//    }
//}



