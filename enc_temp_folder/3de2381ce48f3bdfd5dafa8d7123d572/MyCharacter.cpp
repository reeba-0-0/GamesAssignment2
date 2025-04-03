// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "InputAction.h"
#include "InputMappingContext.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Components/CapsuleComponent.h" 
#include "Kismet/GameplayStatics.h"
#include "FallOffLevel.h"
#include <WorldPartition/WorldPartitionActorDescView.h>
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"


// Sets default values
AMyCharacter::AMyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bReplicates = true;
	

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(GetCapsuleComponent());
	SpringArm->SetRelativeLocation(FVector(0.0f, 0.0f, 20.0f));
	SpringArm->SetRelativeRotation(FRotator(-30.f, 0.f, 0.f));

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Pawn Camera"));
	Camera->SetupAttachment(SpringArm);

	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Pawn, ECR_Block);
}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* PlayerController = Cast<APlayerController>(GetController());

	if (PlayerController) 
	{
		UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
		Subsystem->AddMappingContext(characterMappingContext, 0);
	}
	
	lastPos = GetActorLocation();
}

void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EIC = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	EIC->BindAction(MoveForwardAction, ETriggerEvent::Triggered, this, &AMyCharacter::MoveForwardHandler);
	EIC->BindAction(StrafeAction, ETriggerEvent::Triggered, this, &AMyCharacter::StrafeHandler);
	EIC->BindAction(LookUpAction, ETriggerEvent::Triggered, this, &AMyCharacter::LookUpHandler);
	EIC->BindAction(TurnAction, ETriggerEvent::Triggered, this, &AMyCharacter::TurnHandler);
	EIC->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
	EIC->BindAction(PushAction, ETriggerEvent::Triggered, this, &AMyCharacter::PushHandler);
	EIC->BindAction(DiveAction, ETriggerEvent::Triggered, this, &AMyCharacter::DiveHandler);
}


void AMyCharacter::MoveForwardHandler(const FInputActionValue& Value)
{
	AddMovementInput(GetActorForwardVector() * Value.Get<float>());
}

void AMyCharacter::StrafeHandler(const FInputActionValue& Value)
{
	AddMovementInput(GetActorRightVector() * Value.Get<float>());
}

void AMyCharacter::TurnHandler(const FInputActionValue& Value)
{
	AddControllerYawInput(Value.Get<float>());
}

void AMyCharacter::LookUpHandler(const FInputActionValue& Value)
{
	AddControllerPitchInput(Value.Get<float>());
}

void AMyCharacter::PushHandler(const FInputActionValue& Value)
{
	//if they are in the safe zone do not allow them to push other players 157
	if (bInSafeZone) return;

	FVector Start = GetActorLocation();
	FVector ForwardVector = GetActorForwardVector();
	FVector End = Start + (ForwardVector * 100.0f); // 100 cm forward

	FHitResult Hit;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this); // Ignore self

	// Perform line trace
	bool bHit = GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_Pawn, Params);

	if (bHit)
	{
		AMyCharacter* TargetCharacter = Cast<AMyCharacter>(Hit.GetActor());

		if (TargetCharacter)
		{
			UE_LOG(LogTemp, Warning, TEXT("Push hit: %s"), *TargetCharacter->GetName());

			// Call Client_Push on the target character
			TargetCharacter->Server_Push(TargetCharacter);
		}
	}

	// Debug line (optional)
	DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, 2.0f, 0, 2.0f);
}

void AMyCharacter::DiveHandler(const FInputActionValue& Value)
{
	Server_Dive();
}

void AMyCharacter::Server_Dive_Implementation()
{
	UE_LOG(LogTemp, Warning, TEXT("Server_Dive executed on the server"));

	if (!bCanDive) return; // Prevent spamming
	bCanDive = false; // Disable diving

	UE_LOG(LogTemp, Warning, TEXT("Server_Dive executed on the server"));

	FVector diveForce
		= GetActorForwardVector() * launchForce;
	LaunchCharacter(diveForce, true, false);

	// Set a cooldown before the player can dive again
	GetWorldTimerManager().SetTimer(diveCooldownHandle, this, &AMyCharacter::ResetDive, diveCooldown, false);
	
}

void AMyCharacter::Client_PlaySound_Implementation()
{
	if (Sound)
	{
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), Sound, GetActorLocation());
	}
}

void AMyCharacter::ResetDive()
{
	bCanDive = true;
	UE_LOG(LogTemp, Warning, TEXT("Dive cooldown reset"));
}

void AMyCharacter::Server_Push_Implementation(ACharacter* TargetCharacter)
{
	UE_LOG(LogTemp, Warning, TEXT("Client_Push executed on the client"));

	FVector pushDirection = TargetCharacter->GetActorForwardVector() * -1000.0f; // push backward
	TargetCharacter->LaunchCharacter(pushDirection, true, false);

	UE_LOG(LogTemp, Warning, TEXT("%s was pushed!"), *TargetCharacter->GetName());
}

