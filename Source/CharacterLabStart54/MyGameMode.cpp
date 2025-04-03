// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameMode.h"
#include "MyGameStateBase.h"
#include <Kismet/GameplayStatics.h>

AMyGameMode::AMyGameMode()
{
    PlayerStateClass = AMyPlayerState::StaticClass();
    GameStateClass = AMyGameStateBase::StaticClass();
}

void AMyGameMode::Win()
{
    UWorld* World = GetWorld();

    if (World)
    {
        // open level as listen server (allows others to join)
        World->ServerTravel("/Game/WinLevel?listen");
        UE_LOG(LogTemp, Warning, TEXT("You win!! yayayayy :> "));
    }
}

void AMyGameMode::Lose()
{
    // make player lose if timer is over and 3rd checkpoint isn't reached
    UWorld* World = GetWorld();

    if (World)
    {
        // open level as listen server (allows others to join)
        World->ServerTravel("/Game/LoseLevel?listen");
    }
    
}



