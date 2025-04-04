// Fill out your copyright notice in the Description page of Project Settings.


#include "SlidingDoorActor.h"

// Sets default values
ASlidingDoorActor::ASlidingDoorActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bReplicates = true;

	staticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	RootComponent = staticMesh;

	NetUpdateFrequency = 1.f;
}



// Called when the game starts or when spawned
void ASlidingDoorActor::BeginPlay()
{
	Super::BeginPlay();
	
	TargetLocationUp = GetActorLocation();
	TargetLocationDown = GetActorLocation();
	TargetLocationDown.Z -= targetOffset;
}

// Called every frame
void ASlidingDoorActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	bMoveDown ? MoveSlidingDoorDown(DeltaTime) : MoveSlidingDoorUp(DeltaTime);

}

void ASlidingDoorActor::MoveSlidingDoorDown(float DeltaTime)
{
	FVector currentLocation = this->GetActorLocation();

	// move door down
	SetActorLocation(FMath::VInterpConstantTo(currentLocation, TargetLocationDown, DeltaTime, movingSpeed));

	// move door up
	if (currentLocation.Equals(TargetLocationDown))
	{
		if (HasAuthority())
		{
			ChangeDoorDirection(false);
		}
	}
}

void ASlidingDoorActor::MoveSlidingDoorUp(float DeltaTime)
{
	FVector currentLocation = this->GetActorLocation();

	// move door up
	SetActorLocation(FMath::VInterpConstantTo(currentLocation, TargetLocationUp, DeltaTime, movingSpeed));

	// move door up
	if (currentLocation.Equals(TargetLocationUp))
	{
		if (HasAuthority())
		{
			ChangeDoorDirection(true);
		}
	}
}

void ASlidingDoorActor::ChangeDoorDirection_Implementation(bool moveDown)
{
	bMoveDown = moveDown;
}
