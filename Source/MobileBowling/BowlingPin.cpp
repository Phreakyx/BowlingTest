// BowlingPin.cpp
#include "BowlingPin.h"

ABowlingPin::ABowlingPin()
{
    PrimaryActorTick.bCanEverTick = false;

    StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh")); // stable name
    SetRootComponent(StaticMeshComponent);

    StaticMeshComponent->SetCollisionProfileName(TEXT("PhysicsActor"));
    StaticMeshComponent->SetSimulatePhysics(true);
}

void ABowlingPin::BeginPlay()
{
    Super::BeginPlay();
    ResetTransform = GetActorTransform();
}

void ABowlingPin::ResetPin()
{
    StaticMeshComponent->SetSimulatePhysics(false);
    SetActorTransform(ResetTransform, false, nullptr, ETeleportType::TeleportPhysics);
    bWasHit = false;
}

void ABowlingPin::HideThePin()
{
    StaticMeshComponent->SetSimulatePhysics(true);
    SetActorLocation(FVector(0.f, -500.f, 0.f), false, nullptr, ETeleportType::None);
}