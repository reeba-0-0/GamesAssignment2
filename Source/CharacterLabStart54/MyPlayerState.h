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
public:

	UPROPERTY(Replicated, BlueprintReadOnly)
	int currentHealth = 30;

	UPROPERTY()
	int maxHealth = 30;

	UPROPERTY(Replicated, BlueprintReadOnly)
	int currentCheckpoint = 0;

	
	UPROPERTY()
	int maxCheckpoint = 3;

	bool bReachedCheckpoint = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Effects", meta = (AllowPrivateAccess = "true"))
	class UNiagaraComponent* niagaraComponent;


public:

	/*virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent,
		AController* EventInstigator, AActor* DamageCauser) override;*/

	UFUNCTION()
	void ActivateCheckPoint();



	UFUNCTION()
	void ReplenishHealth();



	UFUNCTION()
	bool IsMaxCheckPoint();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION()
	void ReduceHealth();

	UFUNCTION()
	int GetHealth();

	UFUNCTION()
	bool NoHealthLeft();

	UFUNCTION()
	void KillPlayer();
};
