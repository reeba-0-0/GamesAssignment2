// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameMode.h"

void AMyGameMode::Win()
{
    UWorld* World = GetWorld();

    if (World)
    {
        // open level as listen server (allows others to join)
        World->ServerTravel("/Game/Content/WinLevel?listen");
        UE_LOG(LogTemp, Warning, TEXT("You win!! yayayayy :> "));
    }
}
