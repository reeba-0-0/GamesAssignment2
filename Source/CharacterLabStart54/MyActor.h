#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyActor.generated.h"

UCLASS()
class CHARACTERLABSTART54_API AMyActor: public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMyActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// The speed of rotation (will be replicated)
	UPROPERTY(Replicated, ReplicatedUsing = OnRep_RotationSpeed)
	float RotationSpeed;

	// The function that will be called when the RotationSpeed property changes
	UFUNCTION()
	void OnRep_RotationSpeed();

	// Function to start replication
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
