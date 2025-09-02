// BowlingBall.cpp
#include "BowlingBall.h"

ABowlingBall::ABowlingBall()
{
    BowlingBall = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BowlingBall"));
    SetRootComponent(BowlingBall);
    BowlingBall->SetSimulatePhysics(false);

    AimArrow = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("AimArrow"));
    AimArrow->SetupAttachment(BowlingBall);
    AimArrow->SetHiddenInGame(true);
}

void ABowlingBall::BeginPlay()
{
    Super::BeginPlay();
    ResetTransform = GetActorTransform(); // cache spawn pose for reset
    if (AimArrow)
    {
        AimArrow->SetVisibility(false, true); // hidden until aiming
    }
}

void ABowlingBall::ShootImpulse(const FVector& Dir, float Multiplier)
{
    if (!bIsShot)
    {
        BowlingBall->SetSimulatePhysics(true);
        BowlingBall->AddImpulse(Dir * Multiplier, NAME_None, /*bVelChange*/ false);
        if (AimArrow)
        {
            AimArrow->SetVisibility(false, true); // hidden until aiming
        }

        bIsShot = true;
    }
}

void ABowlingBall::SetAngleVisible(bool bShow)
{
    if (AimArrow)
    {
        AimArrow->SetHiddenInGame(!bShow);
    }
}

void ABowlingBall::ShowAimArrow(bool bShow)
{
    if (AimArrow)
    {
        AimArrow->SetVisibility(bShow, true); // toggle arrow
    }
}

void ABowlingBall::UpdateAim(const FVector& TargetWorld)
{
    if (!BowlingBall || !AimArrow) return;

    FVector Origin = BowlingBall->GetComponentLocation();
    FVector Dir = TargetWorld - Origin;
    Dir.Z = 0.f;
    float Dist = FMath::Clamp(Dir.Size(), 0.f, 20000.f);
    FVector Fwd = Dir.GetSafeNormal();

    // Face target and scale length along X
    FRotator YawOnly = FRotationMatrix::MakeFromX(Fwd).Rotator();
    AimArrow->SetWorldLocation(Origin);
    AimArrow->SetWorldRotation(YawOnly);
    FVector Scale = AimArrow->GetComponentScale();
    Scale.X = 0.2f + (Dist / 1000.f);
    AimArrow->SetWorldScale3D(Scale);
}

void ABowlingBall::ResetBall()
{
    if (!BowlingBall) return;
    BowlingBall->SetSimulatePhysics(false);
    BowlingBall->SetPhysicsLinearVelocity(FVector::ZeroVector);
    BowlingBall->SetPhysicsAngularVelocityInDegrees(FVector::ZeroVector);
    SetActorTransform(ResetTransform, false, nullptr, ETeleportType::TeleportPhysics);
    ShowAimArrow(false);
    BowlingBall->SetSimulatePhysics(true); // if gameplay expects physics after reset
}