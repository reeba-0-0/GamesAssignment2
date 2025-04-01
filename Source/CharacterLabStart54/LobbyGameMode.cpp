// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyGameMode.h"
#include "MyGameStateBase.h"

void ALobbyGameMode::MovePlayers()
{
    gameStateRef = GetGameState<AMyGameStateBase>();

    if (gameStateRef)
    {
        // get playerNum
        playerNum = gameStateRef->GetConnectedPlayers();
    }
	// check if playerNum == max

    if (playerNum == 3)
    {
        // server travel to start level
        UWorld* World = GetWorld();
        if (World)
        {
            // open level as listen server (allows others to join)
            World->ServerTravel("/Game/Content/BasicLevel?listen");
            UE_LOG(LogTemp, Warning, TEXT("Hosting Game..."));
        }
    }
}
