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
	AMyPlayerState();
private:

	UPROPERTY(Replicated)
	int currentHealth = 30;

	UPROPERTY(Replicated)
	int maxHealth = 30;

	UPROPERTY(Replicated)
	int currentCheckpoint = 0;

	UPROPERTY(Replicated)
	int maxCheckpoint = 3;

	UPROPERTY(ReplicatedUsing = OnRep_CheckpointReached) // ensure proper client updates
		bool bReachedCheckpoint = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Effects", meta = (AllowPrivateAccess = "true"))
	class UNiagaraComponent* niagaraComponent;


public:

	UFUNCTION()
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent,
		AController* EventInstigator, AActor* DamageCauser) override;

	UFUNCTION()
	void ActivateCheckPoint();



	UFUNCTION()
	void ReplenishHealth();



	UFUNCTION()
	bool IsMaxCheckPoint();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	// server function for checkpoint activation
	UFUNCTION(Server, Reliable, WithValidation)
	void ServerActivateCheckPoint();
	//void ServerActivateCheckPoint_Implementation();
	//bool ServerActivateCheckPoint_Validate();

	// OnRep function for bReachedCheckpoint
	UFUNCTION()
	void OnRep_CheckpointReached();

	/*UFUNCTION(NetMulticast, Reliable)
	void MulticastActivateNiagaraEffect();*/
};
