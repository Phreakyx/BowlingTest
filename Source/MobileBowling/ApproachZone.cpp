// ApproachZone.cpp
#include "ApproachZone.h"
#include "Components/BoxComponent.h"
#include "BowlingBall.h"

AApproachZone::AApproachZone()
{
    PrimaryActorTick.bCanEverTick = true;
    Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box")); // keep name stable if reparented
    SetRootComponent(Box);
    Box->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    Box->SetGenerateOverlapEvents(true); // make sure events can fire
}

void AApproachZone::BeginPlay()
{
    Super::BeginPlay();
    if (!ensure(IsValid(Box))) return; // guard against stale component
    Box->OnComponentBeginOverlap.AddDynamic(this, &AApproachZone::OnBoxBeginOverlap); // bind ongoing events
    Box->OnComponentEndOverlap.AddDynamic(this, &AApproachZone::OnBoxEndOverlap); // bind ongoing events
    
    if (!bDidInitialScan)
    {
        bDidInitialScan = true;

        if (IsValid(Box))
        {
            TArray<AActor*> Overlapping;
            Box->GetOverlappingActors(Overlapping, ABowlingBall::StaticClass()); // initial seed
            bInBox = Overlapping.Num() > 0; // establish initial state
        }
    }     
}

void AApproachZone::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);        
}

void AApproachZone::OnBoxBeginOverlap(UPrimitiveComponent*, AActor* OtherActor,
                                    UPrimitiveComponent*, int32, bool, const FHitResult&)
{
    if (Cast<ABowlingBall>(OtherActor)) bInBox = true; // handle new entry
}

void AApproachZone::OnBoxEndOverlap(UPrimitiveComponent*, AActor* OtherActor,
                                  UPrimitiveComponent*, int32)
{
    if (Cast<ABowlingBall>(OtherActor)) bInBox = false; // handle exit
}
