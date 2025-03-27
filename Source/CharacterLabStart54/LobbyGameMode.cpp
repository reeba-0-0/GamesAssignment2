// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyGameMode.h"
#include "MyGameState.h"

void ALobbyGameMode::MovePlayers()
{
	// get playerNum
    int playerNum = gameStateRef->GetPlayerNum();

	// check if playerNum == 4

    if (playerNum == 4)
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
