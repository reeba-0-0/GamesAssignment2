#include "MyActor.h"
#include "Net/UnrealNetwork.h"

// Sets default values
AMyActor::AMyActor()
{
	// Set this actor to call Tick() every frame
	PrimaryActorTick.bCanEverTick = true;

	// Enable replication for the actor
	bReplicates = true;

	// Set default rotation speed
	RotationSpeed = 200.f;
}

// Called when the game starts or when spawned
void AMyActor::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority())
	{
		SetReplicates(true);
		SetReplicateMovement(true);
	}
}

// Called every frame
void AMyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (HasAuthority())
	{
		FRotator currentRotation = GetActorRotation();

		currentRotation.Yaw += RotationSpeed;

		AddActorLocalRotation(currentRotation * DeltaTime);
	}
}

// Replication of the RotationSpeed property
void AMyActor::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	// Replicate the RotationSpeed variable
	DOREPLIFETIME(AMyActor, RotationSpeed);
}

// Called when the RotationSpeed property is updated
void AMyActor::OnRep_RotationSpeed()
{

	UE_LOG(LogTemp, Warning, TEXT("RotationSpeed updated to: %f"), RotationSpeed);
}
