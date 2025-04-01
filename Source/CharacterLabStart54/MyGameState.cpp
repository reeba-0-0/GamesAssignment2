//// Fill out your copyright notice in the Description page of Project Settings.
//
//
//#include "MyGameState.h"
//#include <Net/UnrealNetwork.h>
//
//void AMyGameState::BeginPlay()
//{
//    Super::BeginPlay();
//
//    // start countdown timer when the game starts
//    StartCountdown();
//}
//
//void AMyGameState::IncrementPlayerCount()
//{
//	// increment playerNum
//    if (HasAuthority())
//    {
//        connectedPlayers++;
//    }
//}
//
////void AMyGameState::PostLogin(APlayerController* NewPlayer)
////{
////    Super::PostLogin(NewPlayer);
////
////    if (NewPlayer)
////    {
////        UE_LOG(LogTemp, Warning, TEXT("player %s has connected"), *NewPlayer->GetName());
////        playerNum++;
////    }
////}
//  
//
//int AMyGameState::GetConnectedPlayers()
//{
//    return connectedPlayers;
//}
//
//void AMyGameState::StartCountdown()
//{
//    UE_LOG(LogTemp, Warning, TEXT("Countdown Started: %d seconds"), countdownTime);
//
//	GetWorldTimerManager().SetTimer(gameTimerHandle, this, &AMyGameState::UpdateCountdown, 1.0f, true);
//
//}
//
//void AMyGameState::UpdateCountdown()
//{
//    if (countdownTime > 0)
//    {
//        UE_LOG(LogTemp, Warning, TEXT("Time Left: %d seconds"),(countdownTime));
//        countdownTime--;
//    }
//    else
//    {
//        GetWorld()->GetTimerManager().ClearTimer(gameTimerHandle);
//        bTimerFinished = true;
//    }
//}
//
//bool AMyGameState::ReturnTimerFinished()
//{
//    GetWorldTimerManager().ClearTimer(gameTimerHandle);
//
//    return bTimerFinished;
//}
//
//bool AMyGameState::MaxPlayersReached()
//{
//    return connectedPlayers == 4;
//}
//
//void AMyGameState::OnRep_ConnectedPlayers()
//{
//    UE_LOG(LogTemp, Warning, TEXT("replicated Player Count: %d"), (connectedPlayers));
//}
//
//void AMyGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
//{
//    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
//    DOREPLIFETIME(AMyGameState, connectedPlayers);
//}
