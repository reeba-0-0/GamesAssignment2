// Fill out your copyright notice in the Description page of Project Settings.


#include "CheckpointActor.h"
#include "MyCharacter.h"
#include <Components/BoxComponent.h>
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "MyGameStateBase.h"
#include <Kismet/GameplayStatics.h>
#include "MyPlayerState.h"

// Sets default values
ACheckpointActor::ACheckpointActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    bReplicates = true;

    staticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
    RootComponent = staticMesh;
	
    triggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
    triggerBox->SetupAttachment(staticMesh);

    // create and attach niagara component
    niagaraComponent = CreateDefaultSubobject<UNiagaraComponent>(TEXT("NiagaraComponent"));
    niagaraComponent->SetupAttachment(RootComponent);
    niagaraComponent->SetAutoActivate(false);

    triggerBox->OnComponentBeginOverlap.AddDynamic(this, &ACheckpointActor::OnOverlapBegin);
    triggerBox->OnComponentEndOverlap.AddDynamic(this, &ACheckpointActor::OnOverlapEnd);
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
        //check if the actor has already hit the checkpoint
        for (FString name : ActorNames)
        {
            if (name == OtherActor->GetActorLabel()) 
            {
                return;
            }
        }

        // cast to character
        auto player = Cast<AMyCharacter>(OtherActor);

        //set the players last valid position
        if (player)
        {
            ActorNames.Add(player->GetActorLabel());
            player->lastPos = GetActorLocation();
           
        }

        APlayerController* playerController = Cast<APlayerController>(player->GetController());
        
        if (playerController)
        {
            playerStateRef = Cast<AMyPlayerState>(playerController->PlayerState);

            if (playerStateRef)
            {
                playerStateRef->ActivateCheckPoint();
            }
        }
    }

    if (HasAuthority())
    {
        MulticastActivateNiagaraEffect();
    }
    else
    {
        ServerCallNiagaraEffect();
    }
}

void ACheckpointActor::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    if (HasAuthority() && OtherActor)
    {
        // cast to character
        auto player = Cast<AMyCharacter>(OtherActor);

        player->lastPos = GetActorLocation();
    }
}

void ACheckpointActor::ServerCallNiagaraEffect_Implementation()
{
    MulticastActivateNiagaraEffect();
}

void ACheckpointActor::MulticastActivateNiagaraEffect_Implementation()
{
    if (niagaraComponent)
    {
        niagaraComponent->SetActive(true); // trigger effect
    }
}

