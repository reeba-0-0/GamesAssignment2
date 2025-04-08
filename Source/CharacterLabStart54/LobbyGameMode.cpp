// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyGameMode.h"
#include "MyGameStateBase.h"

void ALobbyGameMode::MovePlayers()
{
    gameStateRef = GetGameState<AMyGameStateBase>();

    gameStateRef->UpdatePlayerConnectPlayers();

	// check if playerNum == max
    if (gameStateRef && gameStateRef->MaxPlayersReached())
    {
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


void ALobbyGameMode::PostLogin(APlayerController* NewPlayer)
{
    Super::PostLogin(NewPlayer);

    MovePlayers();
}