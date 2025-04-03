// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"


void UMyGameInstance::TesterFunction()
{
	UE_LOG(LogTemp, Warning, TEXT("TestFunctionFromConsole was called from the console!"));

}

void UMyGameInstance::PrintMessage(FString message)
{
	UE_LOG(LogTemp, Warning, TEXT("Received message: %s"), *message);
}

void UMyGameInstance::HostGame()
{
    UWorld* World = GetWorld();
    if (World)
    {
        // open level as listen server (allows others to join)
        World->ServerTravel("/Game/LobbyLevel?listen"); 
        UE_LOG(LogTemp, Warning, TEXT("Hosting Game..."));
    }
}

void UMyGameInstance::JoinGame(FString IPAddress)
{
    APlayerController* PlayerController = GetFirstLocalPlayerController();
    if (PlayerController)
    {
        PlayerController->ClientTravel(IPAddress, TRAVEL_Absolute);
        UE_LOG(LogTemp, Warning, TEXT("Joining Game at %s..."), *IPAddress);
    }
}
