// LaunchBowlingPlayerController.h
#pragma once
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputActionValue.h"
#include "LaunchBowlingPlayerController.generated.h"

class UInputMappingContext;
class UInputAction;
class ABowlingBall;

UCLASS()
class ALaunchBowlingPlayerController : public APlayerController
{
    GENERATED_BODY()
public:
    virtual void BeginPlay() override;
    virtual void SetupInputComponent() override;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    AActor* BowlingBallBP_Ref = nullptr;

    // Enhanced Input assets
    UPROPERTY(EditDefaultsOnly, Category = "Input")
    UInputMappingContext* IMC_Bowling = nullptr;

    UPROPERTY(EditDefaultsOnly, Category = "Input")
    UInputAction* IA_Aim = nullptr;        // Axis2D (Mouse2D)
    UPROPERTY(EditDefaultsOnly, Category = "Input")
    UInputAction* IA_Primary = nullptr;    // Digital (LMB)

private:
    void OnAim(const FInputActionValue& Value);      // Mouse delta, optional
    void OnPrimary(const FInputActionValue& Value);  // LMB press
};
