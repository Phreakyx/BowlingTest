// StandingPinZone.h
#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "StandingPinZone.generated.h"

UCLASS()
class AStandingPinZone : public AActor
{
    GENERATED_BODY()
public:
    AStandingPinZone();

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    UBoxComponent* Box = nullptr;
};