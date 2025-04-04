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
}



// Called when the game starts or when spawned
void ASlidingDoorActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASlidingDoorActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	MoveSlidingDoor(DeltaTime);

}

void ASlidingDoorActor::MoveSlidingDoor_Implementation(float DeltaTime)
{
	FVector currentLocation = this->GetActorLocation();
	float targetLocationZ = currentLocation.Z - 200.f;

	FVector targetLocationDown = FVector(currentLocation.X, currentLocation.Y, targetLocationZ);
	FVector targetLocationUp = FVector(currentLocation.X, currentLocation.Y, -targetLocationZ);

	// move door down

	SetActorLocation(FMath::VInterpConstantTo(currentLocation, targetLocationDown, DeltaTime, movingSpeed));

	// delay
	/*GetWorldTimerManager().SetTimer(delayTimerHandle, this, );*/

	// move door up

	if (currentLocation.Equals(targetLocationDown))
	{
		SetActorLocation(FMath::VInterpConstantTo(currentLocation, targetLocationUp, DeltaTime, movingSpeed));
	}
}


void ASlidingDoorActor::ServerCallSlidingDoor_Implementation(float DeltaTime)
{
	MoveSlidingDoor(DeltaTime);
}

