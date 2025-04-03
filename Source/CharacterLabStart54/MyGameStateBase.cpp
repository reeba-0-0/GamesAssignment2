#include "MyGameStateBase.h"
// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameStateBase.h"
#include <Net/UnrealNetwork.h>
#include "MyGameMode.h"

void AMyGameStateBase::BeginPlay()
{
    Super::BeginPlay();

    if (HasAuthority())
    {
        StartCountdownWithDelay();
    }

    // start countdown timer when the game starts
    //StartCountdown();
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
    if (HasAuthority())
    {
        UE_LOG(LogTemp, Warning, TEXT("Countdown Started: %d seconds"), countdownTime);

	    GetWorldTimerManager().SetTimer(gameTimerHandle, this, &AMyGameStateBase::EndGameTimer, countdownTime, false);
    }
}

void AMyGameStateBase::EndGameTimer()
{
    Cast<AMyGameMode>(GetWorld()->GetAuthGameMode())->Lose();
}

void AMyGameStateBase::StartCountdownWithDelay()
{
    GetWorldTimerManager().SetTimer(delayTimerHandle, this, &AMyGameStateBase::StartCountdown, 5.0f, false);
}

bool AMyGameStateBase::ReturnTimerFinished()
{
    //GetWorldTimerManager().ClearTimer(gameTimerHandle);

    return bTimerFinished;
}

bool AMyGameStateBase::MaxPlayersReached()
{
    return connectedPlayers >= MAX_CONNECTED_PLAYERS;
}

void AMyGameStateBase::OnRep_ConnectedPlayers()
{
    UE_LOG(LogTemp, Warning, TEXT("replicated Player Count: %d"), (connectedPlayers));
}

void AMyGameStateBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    DOREPLIFETIME(AMyGameStateBase, connectedPlayers);
    DOREPLIFETIME(AMyGameStateBase, GameTimerTxt);
}
