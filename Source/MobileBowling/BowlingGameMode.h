// BowlingGameMode.h
#pragma once
#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BowlingGameMode.generated.h"

class AGutterZone;
class AStandingPinZone;
class ABowlingPin;

UCLASS()
class ABowlingGameMode : public AGameModeBase
{
    GENERATED_BODY()
public:
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaSeconds) override;

private:
    TWeakObjectPtr<AGutterZone> GutterRef;
    TWeakObjectPtr<AStandingPinZone> StandingZoneRef;
};