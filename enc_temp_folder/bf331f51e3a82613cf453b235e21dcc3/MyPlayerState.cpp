#include "MyPlayerState.h"
#include <Net/UnrealNetwork.h>
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"

AMyPlayerState::AMyPlayerState()
{

}

//
//float AMyPlayerState::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
//{
//    currentHealth -= DamageAmount;
//    return currentHealth;
//}

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
    UE_LOG(LogTemp, Log, TEXT("Checkpoint reached"));

    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Checkpoint reached"));
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

       /* UWorld* World = GetWorld();
        if (World)
        {
            World->ServerTravel("/Game/LoseLevel?listen");
            UE_LOG(LogTemp, Warning, TEXT("Game Over :( You lose!"));
        }*/
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
    FString Output = FString((currentCheckpoint >= maxCheckpoint) ? "Is not max checkpoint" : "Is max checkpoint");

    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, Output);

    return currentCheckpoint >= maxCheckpoint;
}

// replication settings
void AMyPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    //DOREPLIFETIME(AMyPlayerState, currentHealth);
    //DOREPLIFETIME(AMyPlayerState, maxHealth);
    //DOREPLIFETIME(AMyPlayerState, currentCheckpoint);
    //DOREPLIFETIME(AMyPlayerState, maxCheckpoint);
    //DOREPLIFETIME(AMyPlayerState, bReachedCheckpoint);
}

//void AMyPlayerState::MulticastActivateNiagaraEffect_Implementation()
//{
//    if (niagaraComponent)
//    {
//        niagaraComponent->Activate(); // Trigger the effect
//    }
//}



