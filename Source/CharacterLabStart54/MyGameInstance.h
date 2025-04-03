// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MyGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class CHARACTERLABSTART54_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:

	UFUNCTION(Exec)
	void TesterFunction();

	UFUNCTION(Exec)
	void PrintMessage(FString message);

	UFUNCTION(Exec)
	void HostGame();

	UFUNCTION(Exec)
	void JoinGame(FString IPAddress);
};
