#pragma once

#include "GameFramework/RotatingMovementComponent.h"

#include <memory>
#include "PIPCamera.h"
#include "common/common_utils/Signal.hpp"
#include "common/common_utils/UniqueValueMap.hpp"
#include "FixedWingPawnEvents.h"

#include "FixedWingPawn.generated.h"

UCLASS()
class AIRSIM_API AFixedWingPawn : public APawn
{
    GENERATED_BODY()
	
public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Debugging")

    AFixedWingPawn();
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaSeconds) override;
    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
    virtual void NotifyHit(class UPrimitiveComponent* MyComp, class AActor* Other, class UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation,
        FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit) override;

    //interface
    void initializeForBeginPlay();
    const common_utils::UniqueValueMap<std::string, APIPCamera*> getCameras() const;
    FixedWingPawnEvents* getPawnEvents()
    {
        return &pawn_events_;
    };
    //called by API to set control speed & deflection
    void setElevatorDeflection(const std::vector<FixedWingPawnEvents::FixedWingElevatorInfo>& elevator_info);
    void setAileronDeflection(const std::vector<FixedWingPawnEvents::FixedWingAileronInfo>& aileron_info);
    void setRudderDeflection(const std::vector<FixedWingPawnEvents::FixedWingRudderInfo>& rudder_info);

private: //variables
    //Unreal components
    //static constexpr size_t control_count = 3; // 3 controls for 3 control surfaces
    UPROPERTY() APIPCamera* camera_front_left_;
    UPROPERTY() APIPCamera* camera_front_right_;
    UPROPERTY() APIPCamera* camera_front_center_;
    UPROPERTY() APIPCamera* camera_back_center_;
    UPROPERTY() APIPCamera* camera_bottom_center_;

    //UPROPERTY() UMovementComponent* control_positions[control_count];
    UPROPERTY() URotatingMovementComponent* elevator_position_;
    UPROPERTY() URotatingMovementComponent* aileron_position_;
    UPROPERTY() URotatingMovementComponent* rudder_position_;
	
    FixedWingPawnEvents pawn_events_;
};
