// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CheckpointActor.generated.h"

UCLASS()
class CHARACTERLABSTART54_API ACheckpointActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACheckpointActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
		bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION(NetMulticast, Reliable)
	void MulticastActivateNiagaraEffect();

	UFUNCTION(Server, Reliable)
	void ServerCallNiagaraEffect();

	UFUNCTION(NetMulticast, Reliable)
	void MulticastDeactivateNiagaraEffect();

	UFUNCTION(Server, Reliable)
	void ServerUncallNiagaraEffect();

private:

	UPROPERTY(EditAnywhere)
	class UNiagaraComponent* niagaraComponent;

	TArray<FString> ActorNames;

	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* staticMesh;

	UPROPERTY(EditAnywhere, Category = "Trigger")
	class UBoxComponent* triggerBox;
	
	UPROPERTY()
	class AMyPlayerState* playerStateRef;
};
