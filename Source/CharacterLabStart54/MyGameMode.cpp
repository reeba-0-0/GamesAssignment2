// MyGameMode.cpp

#include "MyGameMode.h"
#include "MyGameStateBase.h"
#include "MyPlayerState.h"
#include <Kismet/GameplayStatics.h>
#include <GameFramework/PlayerController.h>
#include <Engine/World.h>

AMyGameMode::AMyGameMode()
{
    PlayerStateClass = AMyPlayerState::StaticClass();
    GameStateClass = AMyGameStateBase::StaticClass();
}

void AMyGameMode::BeginPlay()
{
    gameStateRef = GetGameState<AMyGameStateBase>();
    StartCountdownWithDelay();   
}

void AMyGameMode::Tick(float DeltaTime)
{
}

void AMyGameMode::StartCountdownWithDelay()
{
    GetWorldTimerManager().SetTimer(delayTimerHandle, this, &AMyGameMode::StartCountdown, 5.0f, false);
}

void AMyGameMode::StartCountdown()
{
    UE_LOG(LogTemp, Warning, TEXT("Countdown Started: %d seconds"), gameStateRef->countdownTime);

    GetWorldTimerManager().SetTimer(winTimerHandle, this, &AMyGameMode::HasPlayerWon, 1.0f, true);
    GetWorldTimerManager().SetTimer(gameTimerHandle, this, &AMyGameMode::Lose, gameStateRef->countdownTime, false);
    GetWorldTimerManager().SetTimer(displayTimerHandle, this, &AMyGameMode::UpdateTimerDisplay, 1.0f, true);    
}

void AMyGameMode::HasPlayerWon()
{
    for (FConstPlayerControllerIterator Iterator = GetWorld()->GetPlayerControllerIterator(); Iterator; ++Iterator)
    {
        APlayerController* playerController = Iterator->Get();
        if (playerController)
        {
            AMyPlayerState* playerState = Cast<AMyPlayerState>(playerController->PlayerState);

            if (playerState && playerState->IsMaxCheckPoint())
            {
                UE_LOG(LogTemp, Warning, TEXT("Player %s reached the final checkpoint"), *playerController->GetName());
                GetWorldTimerManager().ClearTimer(winTimerHandle);
                Win();
                break;
            }
        }
    }
}

void AMyGameMode::UpdateTimerDisplay()
{
    float timeLeft = GetWorldTimerManager().GetTimerRemaining(gameTimerHandle);
    if (gameStateRef)
    {
        int timeLeftInt = FMath::Max(0, FMath::RoundToInt(timeLeft));
        gameStateRef->gameTimerTxt = "Timer: " + FString::FromInt(timeLeftInt);
        UE_LOG(LogTemp, Warning, TEXT("Time Left (tick): %d"), timeLeftInt);
    }
}

void AMyGameMode::Win()
{
    GetWorldTimerManager().ClearTimer(displayTimerHandle);

    UWorld* World = GetWorld();
    if (World)
    {
        World->ServerTravel("/Game/WinLevel?listen");
        UE_LOG(LogTemp, Warning, TEXT("You win!! yayayayy :> "));
    }
}

void AMyGameMode::Lose()
{
    GetWorldTimerManager().ClearTimer(displayTimerHandle);

    UWorld* World = GetWorld();
    if (World)
    {
        World->ServerTravel("/Game/LoseLevel?listen");
        UE_LOG(LogTemp, Warning, TEXT("Game Over :( You lose!"));
    }
}
