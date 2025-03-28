// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerState.h"

float AMyPlayerState::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	currentHealth -= DamageAmount;

	return currentHealth;
}

void AMyPlayerState::ActivateCheckPoint()
{
	// check if player has collided and if bool is false
	if (bReachedCheckpoint == false)
	{
		bReachedCheckpoint = true;
	}

	bReachedCheckpoint = false;
}

bool AMyPlayerState::IsCheckpointReached()
{
	return bReachedCheckpoint;
}

void AMyPlayerState::ReplenishHealth()
{
	currentHealth = maxHealth;
}

bool AMyPlayerState::IsMaxCheckPoint()
{
	return currentCheckpoint == maxCheckpoint;
}

