// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "InputAction.h"
#include "InputMappingContext.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Components/CapsuleComponent.h" 

// Sets default values
AMyCharacter::AMyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(GetCapsuleComponent());
	SpringArm->SetRelativeLocation(FVector(0.0f, 0.0f, 20.0f));
	SpringArm->SetRelativeRotation(FRotator(-30.f, 0.f, 0.f));

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Pawn Camera"));
	Camera->SetupAttachment(SpringArm);

	AutoPossessPlayer = EAutoReceiveInput::Player0;

}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* PlayerController = Cast<APlayerController>(GetController());

	if (PlayerController) {
		UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
		Subsystem->AddMappingContext(characterMappingContext, 0);
	}
	
}

// Called every frame
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
}


void AMyCharacter::MoveForwardHandler(const FInputActionValue& Value)
{
	UE_LOG(LogTemp, Warning, TEXT("Forward Triggered value is: %f"), Value.Get<float>());
	AddMovementInput(GetActorForwardVector() * Value.Get<float>());
}

void AMyCharacter::StrafeHandler(const FInputActionValue& Value)
{
	UE_LOG(LogTemp, Warning, TEXT("Strafe Triggered value is: %f"), Value.Get<float>());
	AddMovementInput(GetActorRightVector() * Value.Get<float>());
}

void AMyCharacter::TurnHandler(const FInputActionValue& Value)
{
	UE_LOG(LogTemp, Warning, TEXT("Turn Triggered value is: %f"), Value.Get<float>());
	AddControllerYawInput(Value.Get<float>());
}

void AMyCharacter::LookUpHandler(const FInputActionValue& Value)
{
	AddControllerPitchInput(Value.Get<float>());
}

