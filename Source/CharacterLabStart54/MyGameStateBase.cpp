#include "MyGameStateBase.h"
// Fill out your copyright notice in the Description page of Project Settings.
#include "MyGameInstance.h"


#include "MyGameStateBase.h"
#include <Net/UnrealNetwork.h>
#include "MyGameMode.h"

void AMyGameStateBase::BeginPlay()
{
    Super::BeginPlay();
    
}

void AMyGameStateBase::IncrementPlayerCount()
{
	// increment playerNum
    if (HasAuthority())
    {
        connectedPlayers++;
    }
}

int AMyGameStateBase::GetConnectedPlayers()
{
    return connectedPlayers;
}

bool AMyGameStateBase::MaxPlayersReached()
{
    return PlayerArray.Num() >= MAX_CONNECTED_PLAYERS;
}

void AMyGameStateBase::OnRep_ConnectedPlayers()
{
    UE_LOG(LogTemp, Warning, TEXT("replicated Player Count: %d"), (connectedPlayers));
}

void AMyGameStateBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    DOREPLIFETIME(AMyGameStateBase, connectedPlayers);
    DOREPLIFETIME(AMyGameStateBase, gameTimerTxt);
}

void AMyGameStateBase::HostGame()
{
    auto gameInstanceRef = GetGameInstance<UMyGameInstance>();

    if (gameInstanceRef)
    {
        gameInstanceRef->HostGame();
    }
}

void AMyGameStateBase::JoinGame(FString IPAddress)
{
    auto gameInstanceRef = GetGameInstance<UMyGameInstance>();


    if (gameInstanceRef)
    {
        gameInstanceRef->JoinGame(IPAddress);
    }
}
