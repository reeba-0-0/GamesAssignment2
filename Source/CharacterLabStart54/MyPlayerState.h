// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "MyPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class CHARACTERLABSTART54_API AMyPlayerState : public APlayerState
{
	GENERATED_BODY()

private:

	UPROPERTY(Replicated)
	int currentHealth = 30;

	UPROPERTY(Replicated)
	int maxHealth = 30;

	UPROPERTY(Replicated)
	int currentCheckpoint = 0;

	UPROPERTY(Replicated)
	int maxCheckpoint = 3;

	UPROPERTY(Replicated)
	bool bReachedCheckpoint = false; // activate this when cp is reached and then immediately de-activate

public:

	UFUNCTION()
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent,
		AController* EventInstigator, AActor* DamageCauser) override;

	// set bool to active and then false after checking if player has collided with checkpoint box
	UFUNCTION()
	void ActivateCheckPoint();
	// check if checkpoint is reached to replenish health and activate niagara component in game mode
	UFUNCTION()
	bool IsCheckpointReached();

	UFUNCTION()
	void ReplenishHealth();

	UFUNCTION()
	bool IsMaxCheckPoint();
};
