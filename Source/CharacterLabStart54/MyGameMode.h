// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MyPlayerState.h"
#include "MyGameMode.generated.h"

/**
 * 
 */
UCLASS()
class CHARACTERLABSTART54_API AMyGameMode : public AGameModeBase
{
	GENERATED_BODY()
	AMyGameMode();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

public:

	UFUNCTION()
	void Win();

	UFUNCTION()
	void Lose();

	UFUNCTION()
	void StartCountdown();

	void HasPlayerWon();

	//UFUNCTION()
	//void EndGameTimer();

	UFUNCTION()
	void StartCountdownWithDelay();

	UFUNCTION()
	void UpdateTimerDisplay();

private:
	class AMyGameStateBase* gameStateRef;

	FTimerHandle gameTimerHandle;
	FTimerHandle delayTimerHandle;    
	FTimerHandle displayTimerHandle;
	FTimerHandle winTimerHandle;

	class AMyPlayerState* playerStateRef;
};
