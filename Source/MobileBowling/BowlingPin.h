// BowlingPin.h
#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "BowlingPin.generated.h"

UCLASS()
class ABowlingPin : public AActor
{
    GENERATED_BODY()
public:
    ABowlingPin();

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta=(AllowPrivateAccess="true"))
    UStaticMeshComponent* StaticMeshComponent = nullptr;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Bowling")
    FTransform ResetTransform;

    UFUNCTION(BlueprintCallable)
    void ResetPin();
    UFUNCTION(BlueprintCallable)
    void HideThePin();

protected:
    virtual void BeginPlay() override;
};