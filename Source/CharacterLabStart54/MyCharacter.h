// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "MyCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class UInputMappingContext;
class UInputAction;

UCLASS()
class CHARACTERLABSTART54_API AMyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	UPROPERTY(EditAnywhere)
	USpringArmComponent* SpringArm;

	UPROPERTY(EditAnywhere)
	UCameraComponent* Camera;

	UPROPERTY(EditAnywhere)
	UInputMappingContext* characterMappingContext;

	UPROPERTY(EditAnywhere)
	UInputAction* MoveForwardAction;

	UPROPERTY(EditAnywhere)
	UInputAction* StrafeAction;

	UPROPERTY(EditAnywhere)
	UInputAction* TurnAction;

	UPROPERTY(EditAnywhere)
	UInputAction* LookUpAction;

	UPROPERTY(EditAnywhere)
	UInputAction* JumpAction;

	void MoveForwardHandler(const FInputActionValue& Value);
	void StrafeHandler(const FInputActionValue& Value);
	void TurnHandler(const FInputActionValue& Value);
	void LookUpHandler(const FInputActionValue& Value);

};
