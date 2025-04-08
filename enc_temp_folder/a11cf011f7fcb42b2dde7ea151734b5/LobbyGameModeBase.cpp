// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyGameModeBase.h"
#include "MyGameStateBase.h"

ALobbyGameModeBase::ALobbyGameModeBase()
{
    GameStateClass = AMyGameStateBase::StaticClass();
}

void ALobbyGameModeBase::MovePlayers()
{
    gameStateRef = GetGameState<AMyGameStateBase>();

    // check if playerNum == max
    if (gameStateRef && gameStateRef->MaxPlayersReached())
    {
        gameStateRef->UpdatePlayerConnectPlayers();

        // server travel to start level
        UWorld* World = GetWorld();
        if (World)
        {
            // open level as listen server (allows others to join)
            World->ServerTravel("/Game/BasicLevel?listen");
            UE_LOG(LogTemp, Warning, TEXT("Hosting Game..."));
        }
    }
}


void ALobbyGameModeBase::PostLogin(APlayerController* NewPlayer)
{
    Super::PostLogin(NewPlayer);

    MovePlayers();
}