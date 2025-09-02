// GutterZone.cpp
#include "GutterZone.h"
#include "Components/BoxComponent.h"
#include "BowlingBall.h"

AGutterZone::AGutterZone()
{
    PrimaryActorTick.bCanEverTick = true; // one-time bootstrap Tick
    Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box")); // keep name stable if reparented
    SetRootComponent(Box);
    Box->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    Box->SetGenerateOverlapEvents(true); // make sure events can fire
}

void AGutterZone::BeginPlay()
{
    Super::BeginPlay();
    if (!ensure(IsValid(Box))) return; // guard against stale component
    Box->OnComponentBeginOverlap.AddDynamic(this, &AGutterZone::OnBoxBeginOverlap); // bind ongoing events
    Box->OnComponentEndOverlap.AddDynamic(this, &AGutterZone::OnBoxEndOverlap); // bind ongoing events
    
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

void AGutterZone::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);        
}

void AGutterZone::OnBoxBeginOverlap(UPrimitiveComponent*, AActor* OtherActor,
                                    UPrimitiveComponent*, int32, bool, const FHitResult&)
{
    if (Cast<ABowlingBall>(OtherActor)) bInBox = true; // handle new entry
}

void AGutterZone::OnBoxEndOverlap(UPrimitiveComponent*, AActor* OtherActor,
                                  UPrimitiveComponent*, int32)
{
    if (Cast<ABowlingBall>(OtherActor)) bInBox = false; // handle exit
}
