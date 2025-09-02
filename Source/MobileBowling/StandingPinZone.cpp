// StandingPinZone.cpp
#include "StandingPinZone.h"

AStandingPinZone::AStandingPinZone()
{
    Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
    SetRootComponent(Box);
    Box->SetGenerateOverlapEvents(true);
}