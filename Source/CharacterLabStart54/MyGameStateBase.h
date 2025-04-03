// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "MyGameStateBase.generated.h"

/**
 * 
 */
UCLASS()
class CHARACTERLABSTART54_API AMyGameStateBase : public AGameStateBase
{
	GENERATED_BODY()
	virtual void BeginPlay() override;

public:
	UFUNCTION()
	void IncrementPlayerCount();

	//virtual void PostLogin(APlayerController* NewPlayer) override;

	UFUNCTION()
	int GetConnectedPlayers();

	UFUNCTION()
	void StartCountdown();

	UFUNCTION()
	void EndGameTimer();

	UFUNCTION()
	void StartCountdownWithDelay();

	UFUNCTION()
	bool ReturnTimerFinished();

	UFUNCTION()
	bool MaxPlayersReached();


private:

	UPROPERTY(EditAnywhere)
	int MAX_CONNECTED_PLAYERS = 3;

	FTimerHandle gameTimerHandle;
	FTimerHandle delayTimerHandle;

	int countdownTime = 5;
	int delayTime = 5;

	bool bTimerFinished = false;

protected:
	UPROPERTY(ReplicatedUsing = OnRep_ConnectedPlayers)
	int connectedPlayers = 1;

	UFUNCTION()
	void OnRep_ConnectedPlayers();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:
	UPROPERTY(Replicated, BlueprintReadOnly)
	FString GameTimerTxt = "";

};
