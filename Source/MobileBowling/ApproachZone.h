// ApproachZone.h
#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "ApproachZone.generated.h"

UCLASS()
class AApproachZone : public AActor
{
    GENERATED_BODY()
public:
    AApproachZone();

    UPROPERTY(VisibleAnywhere, Category="Gutter")
    bool bInBox = false;
    
protected:
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaSeconds) override;

    UFUNCTION()
    void OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                           UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
                           bool bFromSweep, const FHitResult& SweepResult);

    UFUNCTION()
    void OnBoxEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                         UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Gutter", meta=(AllowPrivateAccess="true"))
    class UBoxComponent* Box = nullptr;

private:
    bool bDidInitialScan = false;
};
