// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SlidingDoorActor.generated.h"

UCLASS()
class CHARACTERLABSTART54_API ASlidingDoorActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties

	ASlidingDoorActor();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* staticMesh;

	UPROPERTY()
	float movingSpeed = 25.f;

	UPROPERTY()
	FTimerHandle delayTimerHandle;

public:
	UFUNCTION(NetMulticast, Reliable)
	void MoveSlidingDoor(float DeltaTime);

	UFUNCTION(Server, Reliable)
	void ServerCallSlidingDoor(float DeltaTime);


};
