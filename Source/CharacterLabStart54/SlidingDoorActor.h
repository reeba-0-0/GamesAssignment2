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

	UPROPERTY(EditAnywhere)
	float movingSpeed = 25.f;

	UPROPERTY(EditAnywhere)
	float targetOffset = 200.f;

	UPROPERTY()
	FTimerHandle delayTimerHandle;

	FVector TargetLocationDown;
	FVector TargetLocationUp;

	bool bMoveDown = true;

public:
	void MoveSlidingDoorDown(float DeltaTime);
	void MoveSlidingDoorUp(float DeltaTime);

	UFUNCTION(NetMulticast, Reliable)
	void ChangeDoorDirection(bool moveDown);
};
