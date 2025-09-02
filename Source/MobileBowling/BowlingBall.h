// BowlingBall.h
#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "BowlingBall.generated.h"

UCLASS()
class ABowlingBall : public AActor
{
    GENERATED_BODY()
public:
    ABowlingBall();

    virtual void BeginPlay() override;
    
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
    UStaticMeshComponent* BowlingBall = nullptr;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
    UStaticMeshComponent* AimArrow = nullptr;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Aiming")
    FTransform ResetTransform;

    UFUNCTION(BlueprintCallable)
    void ResetBall();
    UFUNCTION(BlueprintCallable)
    void ShowAimArrow(bool bShow);
    UFUNCTION(BlueprintCallable)
    void UpdateAim(const FVector& TargetWorld);
    
    UFUNCTION(BlueprintCallable)
    void ShootImpulse(const FVector& Dir, float Multiplier);

    UFUNCTION(BlueprintCallable)
    void SetAngleVisible(bool bShow);

private:
    bool bIsShot = false;
};