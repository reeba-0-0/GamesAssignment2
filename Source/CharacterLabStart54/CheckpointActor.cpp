// Fill out your copyright notice in the Description page of Project Settings.


#include "CheckpointActor.h"
#include "MyCharacter.h"

// Sets default values
ACheckpointActor::ACheckpointActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    //bReplicates = true;

    staticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
    RootComponent = staticMesh;
	
    staticMesh->OnComponentBeginOverlap.AddDynamic(this, &ACheckpointActor::OnOverlapBegin);
}

// Called when the game starts or when spawned
void ACheckpointActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACheckpointActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACheckpointActor::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

    if (HasAuthority() && OtherActor)
    {
        if (OtherActor)
        {
            UE_LOG(LogTemp, Warning, TEXT("%s fell out of the level!"), *OtherActor->GetName());

            // cast to character
            auto player = Cast<AMyCharacter>(OtherActor);

            if (player)
            {
                // do shit
            }
        }
    }
}

