// LaunchBowlingPlayerController.cpp
#include "LaunchBowlingPlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/EngineTypes.h"
#include "BowlingBall.h"

void ALaunchBowlingPlayerController::BeginPlay()
{
    Super::BeginPlay();

    // Ensure game input focus
    FInputModeGameAndUI Mode;
    SetInputMode(Mode);

    if (ULocalPlayer* LP = GetLocalPlayer())
    {
        if (UEnhancedInputLocalPlayerSubsystem* Subsys =
                ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LP))
        {
            if (IMC_Bowling)
            {
                // Optionally clear old mappings when iterating
                Subsys->ClearAllMappings();
                Subsys->AddMappingContext(IMC_Bowling, 0); // ensure non-null and added
            }
        }
    }
}

void ALaunchBowlingPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();
    if (UEnhancedInputComponent* EIC = Cast<UEnhancedInputComponent>(InputComponent))
    {
        if (IA_Aim)
        {
            EIC->BindAction(IA_Aim, ETriggerEvent::Triggered, this, &ALaunchBowlingPlayerController::OnAim);
        }
        if (IA_Primary)
        {
            EIC->BindAction(IA_Primary, ETriggerEvent::Triggered, this, &ALaunchBowlingPlayerController::OnPrimary);
        }
    }
}   

void ALaunchBowlingPlayerController::OnAim(const FInputActionValue& Value)
{
    FHitResult Hit;
    const auto TraceQ = UEngineTypes::ConvertToTraceType(ECollisionChannel::ECC_Visibility);
    if (GetHitResultUnderCursorByChannel(TraceQ, /*bTraceComplex*/ true, Hit))
    {
        if (IsValid(BowlingBallBP_Ref))
        {
            Cast<ABowlingBall>(BowlingBallBP_Ref)->ShowAimArrow(true);
            Cast<ABowlingBall>(BowlingBallBP_Ref)->UpdateAim(Hit.ImpactPoint);
        }
    }
}

void ALaunchBowlingPlayerController::OnPrimary(const FInputActionValue& Value)
{
    if (!IsValid(BowlingBallBP_Ref)) return;

    FHitResult Hit;
    const auto TraceQ = UEngineTypes::ConvertToTraceType(ECollisionChannel::ECC_Visibility);
    if (GetHitResultUnderCursorByChannel(TraceQ, /*bTraceComplex*/ true, Hit))
    {
        const FVector BallLoc = BowlingBallBP_Ref->GetActorLocation();
        FVector Dist = (Hit.ImpactPoint - BallLoc);
        FVector Dir = (Hit.ImpactPoint - BallLoc);
        Dir = Dir.GetSafeNormal();

        double Multiplier = FMath::Clamp(Dist.Size() * 15.f, 0.0, 20000);
        Cast<ABowlingBall>(BowlingBallBP_Ref)->ShootImpulse(Dir, Multiplier); // forwards to AddImpulse after enabling physics
    }
}
