// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "MyGameState.generated.h"

/**
 * 
 */
UCLASS()
class CHARACTERLABSTART54_API AMyGameState : public AGameState
{
	GENERATED_BODY()

public:
	UFUNCTION()
	void IncrementPlayerCount();

	//virtual void PostLogin(APlayerController* NewPlayer) override;

	UFUNCTION()
	int GetConnectedPlayers();

	UFUNCTION()
	void StartCountdown();

	UFUNCTION()
	void UpdateCountdown();


	UFUNCTION()
	bool ReturnTimerFinished();

	UFUNCTION()
	bool MaxPlayersReached();


private:

	int maxConnectedPlayers = 3;
	
	FTimerHandle gameTimerHandle;

	int countdownTime = 60;

	bool bTimerFinished = false;

protected:
	UPROPERTY(ReplicatedUsing = OnRep_ConnectedPlayers)
	int connectedPlayers = 1;

	UFUNCTION()
	void OnRep_ConnectedPlayers();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};

