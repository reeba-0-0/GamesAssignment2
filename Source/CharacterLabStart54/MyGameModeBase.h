// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MyGameState.h"
#include "MyGameModeBase.generated.h"


/**
 * 
 */
UCLASS()
class CHARACTERLABSTART54_API AMyGameModeBase : public AGameModeBase
{
	GENERATED_BODY()


private:
	class AMyGameState* gameStateRef;
};

