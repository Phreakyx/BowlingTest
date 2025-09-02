// BowlingGameMode.cpp
#include "BowlingGameMode.h"
#include "EngineUtils.h"
#include "GutterZone.h"
#include "StandingPinZone.h"
#include "BowlingPin.h"
#include "Engine/Engine.h"

void ABowlingGameMode::BeginPlay()
{
    Super::BeginPlay();

    for (TActorIterator<AGutterZone> It(GetWorld()); It; ++It) { GutterRef = *It; break; }
    for (TActorIterator<AStandingPinZone> It(GetWorld()); It; ++It) { StandingZoneRef = *It; break; }
}

void ABowlingGameMode::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

    if (GutterRef.IsValid() && GutterRef->bInBox)
    {
        GEngine->AddOnScreenDebugMessage(INDEX_NONE, 1.0f, FColor::Cyan, TEXT("Knocked All Pins"));
    }

    if (StandingZoneRef.IsValid() && StandingZoneRef->Box)
    {
        TArray<AActor*> Pins;
        StandingZoneRef->Box->GetOverlappingActors(Pins, ABowlingPin::StaticClass());
        const bool bAllDown = (Pins.Num() == 0);
        // Use bAllDown to trigger scoring/reset as needed.
    }
}