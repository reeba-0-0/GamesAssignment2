// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameStateBase.h"
#include <Net/UnrealNetwork.h>

void AMyGameStateBase::BeginPlay()
{
    Super::BeginPlay();

    // start countdown timer when the game starts
    StartCountdown();
}

void AMyGameStateBase::IncrementPlayerCount()
{
	// increment playerNum
    if (HasAuthority())
    {
        connectedPlayers++;
    }
}

//void AMyGameState::PostLogin(APlayerController* NewPlayer)
//{
//    Super::PostLogin(NewPlayer);
//
//    if (NewPlayer)
//    {
//        UE_LOG(LogTemp, Warning, TEXT("player %s has connected"), *NewPlayer->GetName());
//        playerNum++;
//    }
//}
  

int AMyGameStateBase::GetConnectedPlayers()
{
    return connectedPlayers;
}

void AMyGameStateBase::StartCountdown()
{
    UE_LOG(LogTemp, Warning, TEXT("Countdown Started: %d seconds"), countdownTime);

	GetWorldTimerManager().SetTimer(gameTimerHandle, this, &AMyGameStateBase::UpdateCountdown, 1.0f, true);

}

void AMyGameStateBase::UpdateCountdown()
{
    if (countdownTime > 0)
    {
        UE_LOG(LogTemp, Warning, TEXT("Time Left: %d seconds"),(countdownTime));
        countdownTime--;
    }
    else
    {
        GetWorld()->GetTimerManager().ClearTimer(gameTimerHandle);
        bTimerFinished = true;
    }
}

bool AMyGameStateBase::ReturnTimerFinished()
{
    GetWorldTimerManager().ClearTimer(gameTimerHandle);

    return bTimerFinished;
}

bool AMyGameStateBase::MaxPlayersReached()
{
    return connectedPlayers == 4;
}

void AMyGameStateBase::OnRep_ConnectedPlayers()
{
    UE_LOG(LogTemp, Warning, TEXT("replicated Player Count: %d"), (connectedPlayers));
}

void AMyGameStateBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    DOREPLIFETIME(AMyGameStateBase, connectedPlayers);
}
