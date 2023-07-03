#include "Class.h"
#include "cpp-sdk/ICore.h"

static void HandlingNameHashGetter(js::LazyPropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldValue()) return;
    alt::IVehicle* vehicle = ctx.GetExtraInternalFieldValue<alt::IVehicle>();

    ctx.Return(vehicle->GetHandling()->GetHandlingNameHash());
}

static void MassGetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldValue()) return;
    alt::IVehicle* vehicle = ctx.GetExtraInternalFieldValue<alt::IVehicle>();

    ctx.Return(vehicle->GetHandling()->GetMass());
}

static void MassSetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldValue()) return;
    alt::IVehicle* vehicle = ctx.GetExtraInternalFieldValue<alt::IVehicle>();

    float value;
    if(!ctx.GetValue(value)) return;

    vehicle->ReplaceHandling();
    vehicle->GetHandling()->SetMass(value);
}

static void InitialDragCoeffGetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldValue()) return;
    alt::IVehicle* vehicle = ctx.GetExtraInternalFieldValue<alt::IVehicle>();

    ctx.Return(vehicle->GetHandling()->GetInitialDragCoeff());
}

static void InitialDragCoeffSetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldValue()) return;
    alt::IVehicle* vehicle = ctx.GetExtraInternalFieldValue<alt::IVehicle>();

    float value;
    if(!ctx.GetValue(value)) return;

    vehicle->ReplaceHandling();
    vehicle->GetHandling()->SetInitialDragCoeff(value);
}

static void DownforceModifierGetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldValue()) return;
    alt::IVehicle* vehicle = ctx.GetExtraInternalFieldValue<alt::IVehicle>();

    ctx.Return(vehicle->GetHandling()->GetDownforceModifier());
}

static void DownforceModifierSetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldValue()) return;
    alt::IVehicle* vehicle = ctx.GetExtraInternalFieldValue<alt::IVehicle>();

    float value;
    if(!ctx.GetValue(value)) return;

    vehicle->ReplaceHandling();
    vehicle->GetHandling()->SetDownforceModifier(value);
}

static void unkFloat1Getter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldValue()) return;
    alt::IVehicle* vehicle = ctx.GetExtraInternalFieldValue<alt::IVehicle>();

    ctx.Return(vehicle->GetHandling()->GetunkFloat1());
}

static void unkFloat1Setter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldValue()) return;
    alt::IVehicle* vehicle = ctx.GetExtraInternalFieldValue<alt::IVehicle>();

    float value;
    if(!ctx.GetValue(value)) return;

    vehicle->ReplaceHandling();
    vehicle->GetHandling()->SetunkFloat1(value);
}

static void unkFloat2Getter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldValue()) return;
    alt::IVehicle* vehicle = ctx.GetExtraInternalFieldValue<alt::IVehicle>();

    ctx.Return(vehicle->GetHandling()->GetunkFloat2());
}

static void unkFloat2Setter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldValue()) return;
    alt::IVehicle* vehicle = ctx.GetExtraInternalFieldValue<alt::IVehicle>();

    float value;
    if(!ctx.GetValue(value)) return;

    vehicle->ReplaceHandling();
    vehicle->GetHandling()->SetunkFloat2(value);
}

static void unkFloat4Getter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldValue()) return;
    alt::IVehicle* vehicle = ctx.GetExtraInternalFieldValue<alt::IVehicle>();

    ctx.Return(vehicle->GetHandling()->GetunkFloat4());
}

static void unkFloat4Setter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldValue()) return;
    alt::IVehicle* vehicle = ctx.GetExtraInternalFieldValue<alt::IVehicle>();

    float value;
    if(!ctx.GetValue(value)) return;

    vehicle->ReplaceHandling();
    vehicle->GetHandling()->SetunkFloat4(value);
}

static void unkFloat5Getter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldValue()) return;
    alt::IVehicle* vehicle = ctx.GetExtraInternalFieldValue<alt::IVehicle>();

    ctx.Return(vehicle->GetHandling()->GetunkFloat5());
}

static void unkFloat5Setter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldValue()) return;
    alt::IVehicle* vehicle = ctx.GetExtraInternalFieldValue<alt::IVehicle>();

    float value;
    if(!ctx.GetValue(value)) return;

    vehicle->ReplaceHandling();
    vehicle->GetHandling()->SetunkFloat5(value);
}

static void CentreOfMassOffsetGetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldValue()) return;
    alt::IVehicle* vehicle = ctx.GetExtraInternalFieldValue<alt::IVehicle>();

    ctx.Return(vehicle->GetHandling()->GetCentreOfMassOffset());
}

static void CentreOfMassOffsetSetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldValue()) return;
    alt::IVehicle* vehicle = ctx.GetExtraInternalFieldValue<alt::IVehicle>();

    alt::Vector3f pos;
    if(!ctx.GetValue(pos)) return;

    vehicle->ReplaceHandling();
    vehicle->GetHandling()->SetCentreOfMassOffset(pos);
}

static void InertiaMultiplierGetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldValue()) return;
    alt::IVehicle* vehicle = ctx.GetExtraInternalFieldValue<alt::IVehicle>();

    ctx.Return(vehicle->GetHandling()->GetInertiaMultiplier());
}

static void InertiaMultiplierSetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldValue()) return;
    alt::IVehicle* vehicle = ctx.GetExtraInternalFieldValue<alt::IVehicle>();

    alt::Vector3f pos;
    if(!ctx.GetValue(pos)) return;

    vehicle->ReplaceHandling();
    vehicle->GetHandling()->SetInertiaMultiplier(pos);
}

static void PercentSubmergedGetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldValue()) return;
    alt::IVehicle* vehicle = ctx.GetExtraInternalFieldValue<alt::IVehicle>();

    ctx.Return(vehicle->GetHandling()->GetPercentSubmerged());
}

static void PercentSubmergedSetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldValue()) return;
    alt::IVehicle* vehicle = ctx.GetExtraInternalFieldValue<alt::IVehicle>();

    float value;
    if(!ctx.GetValue(value)) return;

    vehicle->ReplaceHandling();
    vehicle->GetHandling()->SetPercentSubmerged(value);
}

static void PercentSubmergedRatioGetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldValue()) return;
    alt::IVehicle* vehicle = ctx.GetExtraInternalFieldValue<alt::IVehicle>();

    ctx.Return(vehicle->GetHandling()->GetPercentSubmergedRatio());
}

static void PercentSubmergedRatioSetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldValue()) return;
    alt::IVehicle* vehicle = ctx.GetExtraInternalFieldValue<alt::IVehicle>();

    float value;
    if(!ctx.GetValue(value)) return;

    vehicle->ReplaceHandling();
    vehicle->GetHandling()->SetPercentSubmergedRatio(value);
}

static void DriveBiasFrontGetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldValue()) return;
    alt::IVehicle* vehicle = ctx.GetExtraInternalFieldValue<alt::IVehicle>();

    ctx.Return(vehicle->GetHandling()->GetDriveBiasFront());
}

static void DriveBiasFrontSetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldValue()) return;
    alt::IVehicle* vehicle = ctx.GetExtraInternalFieldValue<alt::IVehicle>();

    float value;
    if(!ctx.GetValue(value)) return;

    vehicle->ReplaceHandling();
    vehicle->GetHandling()->SetDriveBiasFront(value);
}

static void AccelerationGetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldValue()) return;
    alt::IVehicle* vehicle = ctx.GetExtraInternalFieldValue<alt::IVehicle>();

    ctx.Return(vehicle->GetHandling()->GetAcceleration());
}

static void AccelerationSetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldValue()) return;
    alt::IVehicle* vehicle = ctx.GetExtraInternalFieldValue<alt::IVehicle>();

    float value;
    if(!ctx.GetValue(value)) return;

    vehicle->ReplaceHandling();
    vehicle->GetHandling()->SetAcceleration(value);
}

static void InitialDriveGearsGetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldValue()) return;
    alt::IVehicle* vehicle = ctx.GetExtraInternalFieldValue<alt::IVehicle>();

    ctx.Return(vehicle->GetHandling()->GetInitialDriveGears());
}

static void InitialDriveGearsSetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldValue()) return;
    alt::IVehicle* vehicle = ctx.GetExtraInternalFieldValue<alt::IVehicle>();

    uint32_t value;
    if(!ctx.GetValue(value)) return;

    vehicle->ReplaceHandling();
    vehicle->GetHandling()->SetInitialDriveGears(value);
}

static void DriveInertiaGetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldValue()) return;
    alt::IVehicle* vehicle = ctx.GetExtraInternalFieldValue<alt::IVehicle>();

    ctx.Return(vehicle->GetHandling()->GetDriveInertia());
}

static void DriveInertiaSetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldValue()) return;
    alt::IVehicle* vehicle = ctx.GetExtraInternalFieldValue<alt::IVehicle>();

    float value;
    if(!ctx.GetValue(value)) return;

    vehicle->ReplaceHandling();
    vehicle->GetHandling()->SetDriveInertia(value);
}

static void ClutchChangeRateScaleUpShiftGetter(js::PropertyContext& ctx)
{
    if (!ctx.CheckExtraInternalFieldValue()) return;
    alt::IVehicle* vehicle = ctx.GetExtraInternalFieldValue<alt::IVehicle>();

    ctx.Return(vehicle->GetHandling()->GetClutchChangeRateScaleUpShift());
}

static void ClutchChangeRateScaleUpShiftSetter(js::PropertyContext& ctx)
{
    if (!ctx.CheckExtraInternalFieldValue()) return;
    alt::IVehicle* vehicle = ctx.GetExtraInternalFieldValue<alt::IVehicle>();

    float value;
    if (!ctx.GetValue(value)) return;

    vehicle->ReplaceHandling();
    vehicle->GetHandling()->SetClutchChangeRateScaleUpShift(value);
}

static void ClutchChangeRateScaleDownShiftGetter(js::PropertyContext& ctx)
{
    if (!ctx.CheckExtraInternalFieldValue()) return;
    alt::IVehicle* vehicle = ctx.GetExtraInternalFieldValue<alt::IVehicle>();

    ctx.Return(vehicle->GetHandling()->GetClutchChangeRateScaleDownShift());
}

static void ClutchChangeRateScaleDownShiftSetter(js::PropertyContext& ctx)
{
    if (!ctx.CheckExtraInternalFieldValue()) return;
    alt::IVehicle* vehicle = ctx.GetExtraInternalFieldValue<alt::IVehicle>();

    float value;
    if (!ctx.GetValue(value)) return;

    vehicle->ReplaceHandling();
    vehicle->GetHandling()->SetClutchChangeRateScaleDownShift(value);
}


static void InitialDriveForceGetter(js::PropertyContext& ctx)
{
    if (!ctx.CheckExtraInternalFieldValue()) return;
    alt::IVehicle* vehicle = ctx.GetExtraInternalFieldValue<alt::IVehicle>();

    ctx.Return(vehicle->GetHandling()->GetInitialDriveForce());
}

static void InitialDriveForceSetter(js::PropertyContext& ctx)
{
    if (!ctx.CheckExtraInternalFieldValue()) return;
    alt::IVehicle* vehicle = ctx.GetExtraInternalFieldValue<alt::IVehicle>();

    float value;
    if (!ctx.GetValue(value)) return;

    vehicle->ReplaceHandling();
    vehicle->GetHandling()->SetInitialDriveForce(value);
}

static void DriveMaxFlatVelGetter(js::PropertyContext& ctx)
{
    if (!ctx.CheckExtraInternalFieldValue()) return;
    alt::IVehicle* vehicle = ctx.GetExtraInternalFieldValue<alt::IVehicle>();

    ctx.Return(vehicle->GetHandling()->GetDriveMaxFlatVel());
}

static void DriveMaxFlatVelSetter(js::PropertyContext& ctx)
{
    if (!ctx.CheckExtraInternalFieldValue()) return;
    alt::IVehicle* vehicle = ctx.GetExtraInternalFieldValue<alt::IVehicle>();

    float value;
    if (!ctx.GetValue(value)) return;

    vehicle->ReplaceHandling();
    vehicle->GetHandling()->SetDriveMaxFlatVel(value);
}

static void InitialDriveMaxFlatVelGetter(js::PropertyContext& ctx)
{
    if (!ctx.CheckExtraInternalFieldValue()) return;
    alt::IVehicle* vehicle = ctx.GetExtraInternalFieldValue<alt::IVehicle>();

    ctx.Return(vehicle->GetHandling()->GetInitialDriveMaxFlatVel());
}

static void InitialDriveMaxFlatVelSetter(js::PropertyContext& ctx)
{
    if (!ctx.CheckExtraInternalFieldValue()) return;
    alt::IVehicle* vehicle = ctx.GetExtraInternalFieldValue<alt::IVehicle>();

    float value;
    if (!ctx.GetValue(value)) return;

    vehicle->ReplaceHandling();
    vehicle->GetHandling()->SetInitialDriveMaxFlatVel(value);
}

static void BrakeForceGetter(js::PropertyContext& ctx)
{
    if (!ctx.CheckExtraInternalFieldValue()) return;
    alt::IVehicle* vehicle = ctx.GetExtraInternalFieldValue<alt::IVehicle>();

    ctx.Return(vehicle->GetHandling()->GetBrakeForce());
}

static void BrakeForceSetter(js::PropertyContext& ctx)
{
    if (!ctx.CheckExtraInternalFieldValue()) return;
    alt::IVehicle* vehicle = ctx.GetExtraInternalFieldValue<alt::IVehicle>();

    float value;
    if (!ctx.GetValue(value)) return;

    vehicle->ReplaceHandling();
    vehicle->GetHandling()->SetBrakeForce(value);
}

static void BrakeBiasFrontGetter(js::PropertyContext& ctx)
{
    if (!ctx.CheckExtraInternalFieldValue()) return;
    alt::IVehicle* vehicle = ctx.GetExtraInternalFieldValue<alt::IVehicle>();

    ctx.Return(vehicle->GetHandling()->GetBrakeBiasFront());
}

static void BrakeBiasFrontSetter(js::PropertyContext& ctx)
{
    if (!ctx.CheckExtraInternalFieldValue()) return;
    alt::IVehicle* vehicle = ctx.GetExtraInternalFieldValue<alt::IVehicle>();

    float value;
    if (!ctx.GetValue(value)) return;

    vehicle->ReplaceHandling();
    vehicle->GetHandling()->SetBrakeBiasFront(value);
}

static void BrakeBiasRearGetter(js::PropertyContext& ctx)
{
    if (!ctx.CheckExtraInternalFieldValue()) return;
    alt::IVehicle* vehicle = ctx.GetExtraInternalFieldValue<alt::IVehicle>();

    ctx.Return(vehicle->GetHandling()->GetBrakeBiasRear());
}

static void BrakeBiasRearSetter(js::PropertyContext& ctx)
{
    if (!ctx.CheckExtraInternalFieldValue()) return;
    alt::IVehicle* vehicle = ctx.GetExtraInternalFieldValue<alt::IVehicle>();

    float value;
    if (!ctx.GetValue(value)) return;

    vehicle->ReplaceHandling();
    vehicle->GetHandling()->SetBrakeBiasRear(value);
}

static void HandBrakeForceGetter(js::PropertyContext& ctx)
{
    if (!ctx.CheckExtraInternalFieldValue()) return;
    alt::IVehicle* vehicle = ctx.GetExtraInternalFieldValue<alt::IVehicle>();

    ctx.Return(vehicle->GetHandling()->GetHandBrakeForce());
}

static void HandBrakeForceSetter(js::PropertyContext& ctx)
{
    if (!ctx.CheckExtraInternalFieldValue()) return;
    alt::IVehicle* vehicle = ctx.GetExtraInternalFieldValue<alt::IVehicle>();

    float value;
    if (!ctx.GetValue(value)) return;

    vehicle->ReplaceHandling();
    vehicle->GetHandling()->SetHandBrakeForce(value);
}

static void SteeringLockGetter(js::PropertyContext& ctx)
{
    if (!ctx.CheckExtraInternalFieldValue()) return;
    alt::IVehicle* vehicle = ctx.GetExtraInternalFieldValue<alt::IVehicle>();

    ctx.Return(vehicle->GetHandling()->GetSteeringLock());
}

static void SteeringLockSetter(js::PropertyContext& ctx)
{
    if (!ctx.CheckExtraInternalFieldValue()) return;
    alt::IVehicle* vehicle = ctx.GetExtraInternalFieldValue<alt::IVehicle>();

    float value;
    if (!ctx.GetValue(value)) return;

    vehicle->ReplaceHandling();
    vehicle->GetHandling()->SetSteeringLock(value);
}

static void SteeringLockRatioGetter(js::PropertyContext& ctx)
{
    if (!ctx.CheckExtraInternalFieldValue()) return;
    alt::IVehicle* vehicle = ctx.GetExtraInternalFieldValue<alt::IVehicle>();

    ctx.Return(vehicle->GetHandling()->GetSteeringLockRatio());
}

static void SteeringLockRatioSetter(js::PropertyContext& ctx)
{
    if (!ctx.CheckExtraInternalFieldValue()) return;
    alt::IVehicle* vehicle = ctx.GetExtraInternalFieldValue<alt::IVehicle>();

    float value;
    if (!ctx.GetValue(value)) return;

    vehicle->ReplaceHandling();
    vehicle->GetHandling()->SetSteeringLockRatio(value);
}

static void TractionCurveMaxGetter(js::PropertyContext& ctx)
{
    if (!ctx.CheckExtraInternalFieldValue()) return;
    alt::IVehicle* vehicle = ctx.GetExtraInternalFieldValue<alt::IVehicle>();

    ctx.Return(vehicle->GetHandling()->GetTractionCurveMax());
}

static void TractionCurveMaxSetter(js::PropertyContext& ctx)
{
    if (!ctx.CheckExtraInternalFieldValue()) return;
    alt::IVehicle* vehicle = ctx.GetExtraInternalFieldValue<alt::IVehicle>();

    float value;
    if (!ctx.GetValue(value)) return;

    vehicle->ReplaceHandling();
    vehicle->GetHandling()->SetTractionCurveMax(value);
}

static void TractionCurveMaxRatioGetter(js::PropertyContext& ctx)
{
    if (!ctx.CheckExtraInternalFieldValue()) return;
    alt::IVehicle* vehicle = ctx.GetExtraInternalFieldValue<alt::IVehicle>();

    ctx.Return(vehicle->GetHandling()->GetTractionCurveMaxRatio());
}

static void TractionCurveMaxRatioSetter(js::PropertyContext& ctx)
{
    if (!ctx.CheckExtraInternalFieldValue()) return;
    alt::IVehicle* vehicle = ctx.GetExtraInternalFieldValue<alt::IVehicle>();

    float value;
    if (!ctx.GetValue(value)) return;

    vehicle->ReplaceHandling();
    vehicle->GetHandling()->SetTractionCurveMaxRatio(value);
}

static void TractionCurveMinGetter(js::PropertyContext& ctx)
{
    if (!ctx.CheckExtraInternalFieldValue()) return;
    alt::IVehicle* vehicle = ctx.GetExtraInternalFieldValue<alt::IVehicle>();

    ctx.Return(vehicle->GetHandling()->GetTractionCurveMin());
}

static void TractionCurveMinSetter(js::PropertyContext& ctx)
{
    if (!ctx.CheckExtraInternalFieldValue()) return;
    alt::IVehicle* vehicle = ctx.GetExtraInternalFieldValue<alt::IVehicle>();

    float value;
    if (!ctx.GetValue(value)) return;

    vehicle->ReplaceHandling();
    vehicle->GetHandling()->SetTractionCurveMin(value);
}

static void TractionCurveMinRatioGetter(js::PropertyContext& ctx)
{
    if (!ctx.CheckExtraInternalFieldValue()) return;
    alt::IVehicle* vehicle = ctx.GetExtraInternalFieldValue<alt::IVehicle>();

    ctx.Return(vehicle->GetHandling()->GetTractionCurveMinRatio());
}

static void TractionCurveMinRatioSetter(js::PropertyContext& ctx)
{
    if (!ctx.CheckExtraInternalFieldValue()) return;
    alt::IVehicle* vehicle = ctx.GetExtraInternalFieldValue<alt::IVehicle>();

    float value;
    if (!ctx.GetValue(value)) return;

    vehicle->ReplaceHandling();
    vehicle->GetHandling()->SetTractionCurveMinRatio(value);
}

static void TractionCurveMinRatioGetter(js::PropertyContext& ctx)
{
    if (!ctx.CheckExtraInternalFieldValue()) return;
    alt::IVehicle* vehicle = ctx.GetExtraInternalFieldValue<alt::IVehicle>();

    ctx.Return(vehicle->GetHandling()->GetTractionCurveMinRatio());
}

static void TractionCurveMinRatioSetter(js::PropertyContext& ctx)
{
    if (!ctx.CheckExtraInternalFieldValue()) return;
    alt::IVehicle* vehicle = ctx.GetExtraInternalFieldValue<alt::IVehicle>();

    float value;
    if (!ctx.GetValue(value)) return;

    vehicle->ReplaceHandling();
    vehicle->GetHandling()->SetTractionCurveMinRatio(value);
}

static void TractionCurveLateralGetter(js::PropertyContext& ctx)
{
    if (!ctx.CheckExtraInternalFieldValue()) return;
    alt::IVehicle* vehicle = ctx.GetExtraInternalFieldValue<alt::IVehicle>();

    ctx.Return(vehicle->GetHandling()->GetTractionCurveLateral());
}

static void TractionCurveLateralSetter(js::PropertyContext& ctx)
{
    if (!ctx.CheckExtraInternalFieldValue()) return;
    alt::IVehicle* vehicle = ctx.GetExtraInternalFieldValue<alt::IVehicle>();

    float value;
    if (!ctx.GetValue(value)) return;

    vehicle->ReplaceHandling();
    vehicle->GetHandling()->SetTractionCurveLateral(value);
}

static void TractionCurveLateralRatioGetter(js::PropertyContext& ctx)
{
    if (!ctx.CheckExtraInternalFieldValue()) return;
    alt::IVehicle* vehicle = ctx.GetExtraInternalFieldValue<alt::IVehicle>();

    ctx.Return(vehicle->GetHandling()->GetTractionCurveLateralRatio());
}

static void TractionCurveLateralRatioSetter(js::PropertyContext& ctx)
{
    if (!ctx.CheckExtraInternalFieldValue()) return;
    alt::IVehicle* vehicle = ctx.GetExtraInternalFieldValue<alt::IVehicle>();

    float value;
    if (!ctx.GetValue(value)) return;

    vehicle->ReplaceHandling();
    vehicle->GetHandling()->SetTractionCurveLateralRatio(value);
}

static void TractionSpringDeltaMaxGetter(js::PropertyContext& ctx)
{
    if (!ctx.CheckExtraInternalFieldValue()) return;
    alt::IVehicle* vehicle = ctx.GetExtraInternalFieldValue<alt::IVehicle>();

    ctx.Return(vehicle->GetHandling()->GetTractionSpringDeltaMax());
}

static void TractionSpringDeltaMaxSetter(js::PropertyContext& ctx)
{
    if (!ctx.CheckExtraInternalFieldValue()) return;
    alt::IVehicle* vehicle = ctx.GetExtraInternalFieldValue<alt::IVehicle>();

    float value;
    if (!ctx.GetValue(value)) return;

    vehicle->ReplaceHandling();
    vehicle->GetHandling()->SetTractionSpringDeltaMax(value);
}

static void TractionSpringDeltaMaxRatioGetter(js::PropertyContext& ctx)
{
    if (!ctx.CheckExtraInternalFieldValue()) return;
    alt::IVehicle* vehicle = ctx.GetExtraInternalFieldValue<alt::IVehicle>();

    ctx.Return(vehicle->GetHandling()->GetTractionSpringDeltaMaxRatio());
}

static void TractionSpringDeltaMaxRatioSetter(js::PropertyContext& ctx)
{
    if (!ctx.CheckExtraInternalFieldValue()) return;
    alt::IVehicle* vehicle = ctx.GetExtraInternalFieldValue<alt::IVehicle>();

    float value;
    if (!ctx.GetValue(value)) return;

    vehicle->ReplaceHandling();
    vehicle->GetHandling()->SetTractionSpringDeltaMaxRatio(value);
}

static void LowSpeedTractionLossMultGetter(js::PropertyContext& ctx)
{
    if (!ctx.CheckExtraInternalFieldValue()) return;
    alt::IVehicle* vehicle = ctx.GetExtraInternalFieldValue<alt::IVehicle>();

    ctx.Return(vehicle->GetHandling()->GetLowSpeedTractionLossMult());
}

static void LowSpeedTractionLossMultSetter(js::PropertyContext& ctx)
{
    if (!ctx.CheckExtraInternalFieldValue()) return;
    alt::IVehicle* vehicle = ctx.GetExtraInternalFieldValue<alt::IVehicle>();

    float value;
    if (!ctx.GetValue(value)) return;

    vehicle->ReplaceHandling();
    vehicle->GetHandling()->SetLowSpeedTractionLossMult(value);
}

static void CamberStiffnessGetter(js::PropertyContext& ctx)
{
    if (!ctx.CheckExtraInternalFieldValue()) return;
    alt::IVehicle* vehicle = ctx.GetExtraInternalFieldValue<alt::IVehicle>();

    ctx.Return(vehicle->GetHandling()->GetCamberStiffness());
}

static void CamberStiffnessSetter(js::PropertyContext& ctx)
{
    if (!ctx.CheckExtraInternalFieldValue()) return;
    alt::IVehicle* vehicle = ctx.GetExtraInternalFieldValue<alt::IVehicle>();

    float value;
    if (!ctx.GetValue(value)) return;

    vehicle->ReplaceHandling();
    vehicle->GetHandling()->SetCamberStiffness(value);
}

static void TractionBiasFrontGetter(js::PropertyContext& ctx)
{
    if (!ctx.CheckExtraInternalFieldValue()) return;
    alt::IVehicle* vehicle = ctx.GetExtraInternalFieldValue<alt::IVehicle>();

    ctx.Return(vehicle->GetHandling()->GetTractionBiasFront());
}

static void TractionBiasFrontSetter(js::PropertyContext& ctx)
{
    if (!ctx.CheckExtraInternalFieldValue()) return;
    alt::IVehicle* vehicle = ctx.GetExtraInternalFieldValue<alt::IVehicle>();

    float value;
    if (!ctx.GetValue(value)) return;

    vehicle->ReplaceHandling();
    vehicle->GetHandling()->SetTractionBiasFront(value);
}

static void TractionBiasRearGetter(js::PropertyContext& ctx)
{
    if (!ctx.CheckExtraInternalFieldValue()) return;
    alt::IVehicle* vehicle = ctx.GetExtraInternalFieldValue<alt::IVehicle>();

    ctx.Return(vehicle->GetHandling()->GetTractionBiasRear());
}

static void TractionBiasRearSetter(js::PropertyContext& ctx)
{
    if (!ctx.CheckExtraInternalFieldValue()) return;
    alt::IVehicle* vehicle = ctx.GetExtraInternalFieldValue<alt::IVehicle>();

    float value;
    if (!ctx.GetValue(value)) return;

    vehicle->ReplaceHandling();
    vehicle->GetHandling()->SetTractionBiasRear(value);
}

static void TractionLossMultGetter(js::PropertyContext& ctx)
{
    if (!ctx.CheckExtraInternalFieldValue()) return;
    alt::IVehicle* vehicle = ctx.GetExtraInternalFieldValue<alt::IVehicle>();

    ctx.Return(vehicle->GetHandling()->GetTractionLossMult());
}

static void TractionLossMultSetter(js::PropertyContext& ctx)
{
    if (!ctx.CheckExtraInternalFieldValue()) return;
    alt::IVehicle* vehicle = ctx.GetExtraInternalFieldValue<alt::IVehicle>();

    float value;
    if (!ctx.GetValue(value)) return;

    vehicle->ReplaceHandling();
    vehicle->GetHandling()->SetTractionLossMult(value);
}

static void SuspensionForceGetter(js::PropertyContext& ctx)
{
    if (!ctx.CheckExtraInternalFieldValue()) return;
    alt::IVehicle* vehicle = ctx.GetExtraInternalFieldValue<alt::IVehicle>();

    ctx.Return(vehicle->GetHandling()->GetSuspensionForce());
}

static void SuspensionForceSetter(js::PropertyContext& ctx)
{
    if (!ctx.CheckExtraInternalFieldValue()) return;
    alt::IVehicle* vehicle = ctx.GetExtraInternalFieldValue<alt::IVehicle>();

    float value;
    if (!ctx.GetValue(value)) return;

    vehicle->ReplaceHandling();
    vehicle->GetHandling()->SetSuspensionForce(value);
}

static void SuspensionCompDampGetter(js::PropertyContext& ctx)
{
    if (!ctx.CheckExtraInternalFieldValue()) return;
    alt::IVehicle* vehicle = ctx.GetExtraInternalFieldValue<alt::IVehicle>();

    ctx.Return(vehicle->GetHandling()->GetSuspensionCompDamp());
}

static void SuspensionCompDampSetter(js::PropertyContext& ctx)
{
    if (!ctx.CheckExtraInternalFieldValue()) return;
    alt::IVehicle* vehicle = ctx.GetExtraInternalFieldValue<alt::IVehicle>();

    float value;
    if (!ctx.GetValue(value)) return;

    vehicle->ReplaceHandling();
    vehicle->GetHandling()->SetSuspensionCompDamp(value);
}

static void SuspensionReboundDampGetter(js::PropertyContext& ctx)
{
    if (!ctx.CheckExtraInternalFieldValue()) return;
    alt::IVehicle* vehicle = ctx.GetExtraInternalFieldValue<alt::IVehicle>();

    ctx.Return(vehicle->GetHandling()->GetSuspensionReboundDamp());
}

static void SuspensionReboundDampSetter(js::PropertyContext& ctx)
{
    if (!ctx.CheckExtraInternalFieldValue()) return;
    alt::IVehicle* vehicle = ctx.GetExtraInternalFieldValue<alt::IVehicle>();

    float value;
    if (!ctx.GetValue(value)) return;

    vehicle->ReplaceHandling();
    vehicle->GetHandling()->SetSuspensionReboundDamp(value);
}

static void SuspensionUpperLimitGetter(js::PropertyContext& ctx)
{
    if (!ctx.CheckExtraInternalFieldValue()) return;
    alt::IVehicle* vehicle = ctx.GetExtraInternalFieldValue<alt::IVehicle>();

    ctx.Return(vehicle->GetHandling()->GetSuspensionUpperLimit());
}

static void SuspensionUpperLimitSetter(js::PropertyContext& ctx)
{
    if (!ctx.CheckExtraInternalFieldValue()) return;
    alt::IVehicle* vehicle = ctx.GetExtraInternalFieldValue<alt::IVehicle>();

    float value;
    if (!ctx.GetValue(value)) return;

    vehicle->ReplaceHandling();
    vehicle->GetHandling()->SetSuspensionUpperLimit(value);
}

static void SuspensionLowerLimitGetter(js::PropertyContext& ctx)
{
    if (!ctx.CheckExtraInternalFieldValue()) return;
    alt::IVehicle* vehicle = ctx.GetExtraInternalFieldValue<alt::IVehicle>();

    ctx.Return(vehicle->GetHandling()->GetSuspensionLowerLimit());
}

static void SuspensionLowerLimitSetter(js::PropertyContext& ctx)
{
    if (!ctx.CheckExtraInternalFieldValue()) return;
    alt::IVehicle* vehicle = ctx.GetExtraInternalFieldValue<alt::IVehicle>();

    float value;
    if (!ctx.GetValue(value)) return;

    vehicle->ReplaceHandling();
    vehicle->GetHandling()->SetSuspensionLowerLimit(value);
}

static void SuspensionRaiseGetter(js::PropertyContext& ctx)
{
    if (!ctx.CheckExtraInternalFieldValue()) return;
    alt::IVehicle* vehicle = ctx.GetExtraInternalFieldValue<alt::IVehicle>();

    ctx.Return(vehicle->GetHandling()->GetSuspensionRaise());
}

static void SuspensionRaiseSetter(js::PropertyContext& ctx)
{
    if (!ctx.CheckExtraInternalFieldValue()) return;
    alt::IVehicle* vehicle = ctx.GetExtraInternalFieldValue<alt::IVehicle>();

    float value;
    if (!ctx.GetValue(value)) return;

    vehicle->ReplaceHandling();
    vehicle->GetHandling()->SetSuspensionRaise(value);
}

static void SuspensionBiasFrontGetter(js::PropertyContext& ctx)
{
    if (!ctx.CheckExtraInternalFieldValue()) return;
    alt::IVehicle* vehicle = ctx.GetExtraInternalFieldValue<alt::IVehicle>();

    ctx.Return(vehicle->GetHandling()->GetSuspensionBiasFront());
}

static void SuspensionBiasFrontSetter(js::PropertyContext& ctx)
{
    if (!ctx.CheckExtraInternalFieldValue()) return;
    alt::IVehicle* vehicle = ctx.GetExtraInternalFieldValue<alt::IVehicle>();

    float value;
    if (!ctx.GetValue(value)) return;

    vehicle->ReplaceHandling();
    vehicle->GetHandling()->SetSuspensionBiasFront(value);
}

static void SuspensionBiasRearGetter(js::PropertyContext& ctx)
{
    if (!ctx.CheckExtraInternalFieldValue()) return;
    alt::IVehicle* vehicle = ctx.GetExtraInternalFieldValue<alt::IVehicle>();

    ctx.Return(vehicle->GetHandling()->GetSuspensionBiasRear());
}

static void SuspensionBiasRearSetter(js::PropertyContext& ctx)
{
    if (!ctx.CheckExtraInternalFieldValue()) return;
    alt::IVehicle* vehicle = ctx.GetExtraInternalFieldValue<alt::IVehicle>();

    float value;
    if (!ctx.GetValue(value)) return;

    vehicle->ReplaceHandling();
    vehicle->GetHandling()->SetSuspensionBiasRear(value);
}

static void AntiRollBarForceGetter(js::PropertyContext& ctx)
{
    if (!ctx.CheckExtraInternalFieldValue()) return;
    alt::IVehicle* vehicle = ctx.GetExtraInternalFieldValue<alt::IVehicle>();

    ctx.Return(vehicle->GetHandling()->GetAntiRollBarForce());
}

static void AntiRollBarForceSetter(js::PropertyContext& ctx)
{
    if (!ctx.CheckExtraInternalFieldValue()) return;
    alt::IVehicle* vehicle = ctx.GetExtraInternalFieldValue<alt::IVehicle>();

    float value;
    if (!ctx.GetValue(value)) return;

    vehicle->ReplaceHandling();
    vehicle->GetHandling()->SetAntiRollBarForce(value);
}

static void AntiRollBarBiasFrontGetter(js::PropertyContext& ctx)
{
    if (!ctx.CheckExtraInternalFieldValue()) return;
    alt::IVehicle* vehicle = ctx.GetExtraInternalFieldValue<alt::IVehicle>();

    ctx.Return(vehicle->GetHandling()->GetAntiRollBarBiasFront());
}

static void AntiRollBarBiasFrontSetter(js::PropertyContext& ctx)
{
    if (!ctx.CheckExtraInternalFieldValue()) return;
    alt::IVehicle* vehicle = ctx.GetExtraInternalFieldValue<alt::IVehicle>();

    float value;
    if (!ctx.GetValue(value)) return;

    vehicle->ReplaceHandling();
    vehicle->GetHandling()->SetAntiRollBarBiasFront(value);
}

static void AntiRollBarBiasRearGetter(js::PropertyContext& ctx)
{
    if (!ctx.CheckExtraInternalFieldValue()) return;
    alt::IVehicle* vehicle = ctx.GetExtraInternalFieldValue<alt::IVehicle>();

    ctx.Return(vehicle->GetHandling()->GetAntiRollBarBiasRear());
}

static void AntiRollBarBiasRearSetter(js::PropertyContext& ctx)
{
    if (!ctx.CheckExtraInternalFieldValue()) return;
    alt::IVehicle* vehicle = ctx.GetExtraInternalFieldValue<alt::IVehicle>();

    float value;
    if (!ctx.GetValue(value)) return;

    vehicle->ReplaceHandling();
    vehicle->GetHandling()->SetAntiRollBarBiasRear(value);
}

static void RollCentreHeightFrontGetter(js::PropertyContext& ctx)
{
    if (!ctx.CheckExtraInternalFieldValue()) return;
    alt::IVehicle* vehicle = ctx.GetExtraInternalFieldValue<alt::IVehicle>();

    ctx.Return(vehicle->GetHandling()->GetRollCentreHeightFront());
}

static void RollCentreHeightFrontSetter(js::PropertyContext& ctx)
{
    if (!ctx.CheckExtraInternalFieldValue()) return;
    alt::IVehicle* vehicle = ctx.GetExtraInternalFieldValue<alt::IVehicle>();

    float value;
    if (!ctx.GetValue(value)) return;

    vehicle->ReplaceHandling();
    vehicle->GetHandling()->SetRollCentreHeightFront(value);
}

static void RollCentreHeightRearGetter(js::PropertyContext& ctx)
{
    if (!ctx.CheckExtraInternalFieldValue()) return;
    alt::IVehicle* vehicle = ctx.GetExtraInternalFieldValue<alt::IVehicle>();

    ctx.Return(vehicle->GetHandling()->GetRollCentreHeightRear());
}

static void RollCentreHeightRearSetter(js::PropertyContext& ctx)
{
    if (!ctx.CheckExtraInternalFieldValue()) return;
    alt::IVehicle* vehicle = ctx.GetExtraInternalFieldValue<alt::IVehicle>();

    float value;
    if (!ctx.GetValue(value)) return;

    vehicle->ReplaceHandling();
    vehicle->GetHandling()->SetRollCentreHeightRear(value);
}

static void CollisionDamageMultGetter(js::PropertyContext& ctx)
{
    if (!ctx.CheckExtraInternalFieldValue()) return;
    alt::IVehicle* vehicle = ctx.GetExtraInternalFieldValue<alt::IVehicle>();

    ctx.Return(vehicle->GetHandling()->GetCollisionDamageMult());
}

static void CollisionDamageMultSetter(js::PropertyContext& ctx)
{
    if (!ctx.CheckExtraInternalFieldValue()) return;
    alt::IVehicle* vehicle = ctx.GetExtraInternalFieldValue<alt::IVehicle>();

    float value;
    if (!ctx.GetValue(value)) return;

    vehicle->ReplaceHandling();
    vehicle->GetHandling()->SetCollisionDamageMult(value);
}

static void WeaponDamageMultGetter(js::PropertyContext& ctx)
{
    if (!ctx.CheckExtraInternalFieldValue()) return;
    alt::IVehicle* vehicle = ctx.GetExtraInternalFieldValue<alt::IVehicle>();

    ctx.Return(vehicle->GetHandling()->GetWeaponDamageMult());
}

static void WeaponDamageMultSetter(js::PropertyContext& ctx)
{
    if (!ctx.CheckExtraInternalFieldValue()) return;
    alt::IVehicle* vehicle = ctx.GetExtraInternalFieldValue<alt::IVehicle>();

    float value;
    if (!ctx.GetValue(value)) return;

    vehicle->ReplaceHandling();
    vehicle->GetHandling()->SetWeaponDamageMult(value);
}

static void DeformationDamageMultGetter(js::PropertyContext& ctx)
{
    if (!ctx.CheckExtraInternalFieldValue()) return;
    alt::IVehicle* vehicle = ctx.GetExtraInternalFieldValue<alt::IVehicle>();

    ctx.Return(vehicle->GetHandling()->GetDeformationDamageMult());
}

static void DeformationDamageMultSetter(js::PropertyContext& ctx)
{
    if (!ctx.CheckExtraInternalFieldValue()) return;
    alt::IVehicle* vehicle = ctx.GetExtraInternalFieldValue<alt::IVehicle>();

    float value;
    if (!ctx.GetValue(value)) return;

    vehicle->ReplaceHandling();
    vehicle->GetHandling()->SetDeformationDamageMult(value);
}

static void EngineDamageMultGetter(js::PropertyContext& ctx)
{
    if (!ctx.CheckExtraInternalFieldValue()) return;
    alt::IVehicle* vehicle = ctx.GetExtraInternalFieldValue<alt::IVehicle>();

    ctx.Return(vehicle->GetHandling()->GetEngineDamageMult());
}

static void EngineDamageMultSetter(js::PropertyContext& ctx)
{
    if (!ctx.CheckExtraInternalFieldValue()) return;
    alt::IVehicle* vehicle = ctx.GetExtraInternalFieldValue<alt::IVehicle>();

    float value;
    if (!ctx.GetValue(value)) return;

    vehicle->ReplaceHandling();
    vehicle->GetHandling()->SetEngineDamageMult(value);
}

static void PetrolTankVolumeGetter(js::PropertyContext& ctx)
{
    if (!ctx.CheckExtraInternalFieldValue()) return;
    alt::IVehicle* vehicle = ctx.GetExtraInternalFieldValue<alt::IVehicle>();

    ctx.Return(vehicle->GetHandling()->GetPetrolTankVolume());
}

static void PetrolTankVolumeSetter(js::PropertyContext& ctx)
{
    if (!ctx.CheckExtraInternalFieldValue()) return;
    alt::IVehicle* vehicle = ctx.GetExtraInternalFieldValue<alt::IVehicle>();

    float value;
    if (!ctx.GetValue(value)) return;

    vehicle->ReplaceHandling();
    vehicle->GetHandling()->SetPetrolTankVolume(value);
}

static void OilVolumeGetter(js::PropertyContext& ctx)
{
    if (!ctx.CheckExtraInternalFieldValue()) return;
    alt::IVehicle* vehicle = ctx.GetExtraInternalFieldValue<alt::IVehicle>();

    ctx.Return(vehicle->GetHandling()->GetOilVolume());
}

static void OilVolumeSetter(js::PropertyContext& ctx)
{
    if (!ctx.CheckExtraInternalFieldValue()) return;
    alt::IVehicle* vehicle = ctx.GetExtraInternalFieldValue<alt::IVehicle>();

    float value;
    if (!ctx.GetValue(value)) return;

    vehicle->ReplaceHandling();
    vehicle->GetHandling()->SetOilVolume(value);
}

static void SeatOffsetDistXGetter(js::PropertyContext& ctx)
{
    if (!ctx.CheckExtraInternalFieldValue()) return;
    alt::IVehicle* vehicle = ctx.GetExtraInternalFieldValue<alt::IVehicle>();

    ctx.Return(vehicle->GetHandling()->GetSeatOffsetDistX());
}

static void SeatOffsetDistXSetter(js::PropertyContext& ctx)
{
    if (!ctx.CheckExtraInternalFieldValue()) return;
    alt::IVehicle* vehicle = ctx.GetExtraInternalFieldValue<alt::IVehicle>();

    float value;
    if (!ctx.GetValue(value)) return;

    vehicle->ReplaceHandling();
    vehicle->GetHandling()->SetSeatOffsetDistX(value);
}

static void SeatOffsetDistYGetter(js::PropertyContext& ctx)
{
    if (!ctx.CheckExtraInternalFieldValue()) return;
    alt::IVehicle* vehicle = ctx.GetExtraInternalFieldValue<alt::IVehicle>();

    ctx.Return(vehicle->GetHandling()->GetSeatOffsetDistY());
}

static void SeatOffsetDistYSetter(js::PropertyContext& ctx)
{
    if (!ctx.CheckExtraInternalFieldValue()) return;
    alt::IVehicle* vehicle = ctx.GetExtraInternalFieldValue<alt::IVehicle>();

    float value;
    if (!ctx.GetValue(value)) return;

    vehicle->ReplaceHandling();
    vehicle->GetHandling()->SetSeatOffsetDistY(value);
}

static void SeatOffsetDistZGetter(js::PropertyContext& ctx)
{
    if (!ctx.CheckExtraInternalFieldValue()) return;
    alt::IVehicle* vehicle = ctx.GetExtraInternalFieldValue<alt::IVehicle>();

    ctx.Return(vehicle->GetHandling()->GetSeatOffsetDistZ());
}

static void SeatOffsetDistZSetter(js::PropertyContext& ctx)
{
    if (!ctx.CheckExtraInternalFieldValue()) return;
    alt::IVehicle* vehicle = ctx.GetExtraInternalFieldValue<alt::IVehicle>();

    float value;
    if (!ctx.GetValue(value)) return;

    vehicle->ReplaceHandling();
    vehicle->GetHandling()->SetSeatOffsetDistZ(value);
}

static void MonetaryValueGetter(js::PropertyContext& ctx)
{
    if (!ctx.CheckExtraInternalFieldValue()) return;
    alt::IVehicle* vehicle = ctx.GetExtraInternalFieldValue<alt::IVehicle>();

    ctx.Return(vehicle->GetHandling()->GetMonetaryValue());
}

static void MonetaryValueSetter(js::PropertyContext& ctx)
{
    if (!ctx.CheckExtraInternalFieldValue()) return;
    alt::IVehicle* vehicle = ctx.GetExtraInternalFieldValue<alt::IVehicle>();

    uint32_t value;
    if (!ctx.GetValue(value)) return;

    vehicle->ReplaceHandling();
    vehicle->GetHandling()->SetMonetaryValue(value);
}

static void ModelFlagsGetter(js::PropertyContext& ctx)
{
    if (!ctx.CheckExtraInternalFieldValue()) return;
    alt::IVehicle* vehicle = ctx.GetExtraInternalFieldValue<alt::IVehicle>();

    ctx.Return(vehicle->GetHandling()->GetModelFlags());
}

static void ModelFlagsSetter(js::PropertyContext& ctx)
{
    if (!ctx.CheckExtraInternalFieldValue()) return;
    alt::IVehicle* vehicle = ctx.GetExtraInternalFieldValue<alt::IVehicle>();

    uint32_t value;
    if (!ctx.GetValue(value)) return;

    vehicle->ReplaceHandling();
    vehicle->GetHandling()->SetModelFlags(value);
}

static void HandlingFlagsGetter(js::PropertyContext& ctx)
{
    if (!ctx.CheckExtraInternalFieldValue()) return;
    alt::IVehicle* vehicle = ctx.GetExtraInternalFieldValue<alt::IVehicle>();

    ctx.Return(vehicle->GetHandling()->GetHandlingFlags());
}

static void HandlingFlagsSetter(js::PropertyContext& ctx)
{
    if (!ctx.CheckExtraInternalFieldValue()) return;
    alt::IVehicle* vehicle = ctx.GetExtraInternalFieldValue<alt::IVehicle>();

    uint32_t value;
    if (!ctx.GetValue(value)) return;

    vehicle->ReplaceHandling();
    vehicle->GetHandling()->SetHandlingFlags(value);
}

static void DamageFlagsGetter(js::PropertyContext& ctx)
{
    if (!ctx.CheckExtraInternalFieldValue()) return;
    alt::IVehicle* vehicle = ctx.GetExtraInternalFieldValue<alt::IVehicle>();

    ctx.Return(vehicle->GetHandling()->GetDamageFlags());
}

static void DamageFlagsSetter(js::PropertyContext& ctx)
{
    if (!ctx.CheckExtraInternalFieldValue()) return;
    alt::IVehicle* vehicle = ctx.GetExtraInternalFieldValue<alt::IVehicle>();

    uint32_t value;
    if (!ctx.GetValue(value)) return;

    vehicle->ReplaceHandling();
    vehicle->GetHandling()->SetDamageFlags(value);
}

static void IsModified(js::PropertyContext& ctx)
{
    if (!ctx.CheckExtraInternalFieldValue()) return;
    alt::IVehicle* vehicle = ctx.GetExtraInternalFieldValue<alt::IVehicle>();

    ctx.Return(vehicle->IsHandlingModified());
}

static void Reset(js::FunctionContext& ctx)
{
    if (!ctx.CheckExtraInternalFieldValue()) return;
    alt::IVehicle* vehicle = ctx.GetExtraInternalFieldValue<alt::IVehicle>();

    vehicle->ResetHandling();
}

// clang-format off
extern js::Class handlingClass("Handling", [](js::ClassTemplate& tpl)
{
    tpl.StaticProperty("handlingNameHash", HandlingNameHashGetter);
    tpl.Property("mass", MassGetter, MassSetter);
    tpl.Property("initialDragCoeff", InitialDragCoeffGetter, InitialDragCoeffSetter);
    tpl.Property("downforceModifier", DownforceModifierGetter, DownforceModifierSetter);
    tpl.Property("unkFloat1", unkFloat1Getter, unkFloat1Setter);
    tpl.Property("unkFloat2", unkFloat2Getter, unkFloat2Setter);
    tpl.Property("unkFloat4", unkFloat4Getter, unkFloat4Setter);
    tpl.Property("unkFloat5", unkFloat5Getter, unkFloat5Setter);
    tpl.Property("centreOfMassOffset", CentreOfMassOffsetGetter, CentreOfMassOffsetSetter);
    tpl.Property("inertiaMultiplier", InertiaMultiplierGetter, InertiaMultiplierSetter);
    tpl.Property("percentSubmerged", PercentSubmergedGetter, PercentSubmergedSetter);
    tpl.Property("percentSubmergedRatio", PercentSubmergedRatioGetter, PercentSubmergedRatioSetter);
    tpl.Property("driveBiasFront", DriveBiasFrontGetter, DriveBiasFrontSetter);
    tpl.Property("acceleration", AccelerationGetter, AccelerationSetter);
    tpl.Property("initialDriveGears", InitialDriveGearsGetter, InitialDriveGearsSetter);
    tpl.Property("driveInertia", DriveInertiaGetter, DriveInertiaSetter);
    tpl.Property("clutchChangeRateScaleUpShift", ClutchChangeRateScaleUpShiftGetter, ClutchChangeRateScaleUpShiftSetter);
    tpl.Property("clutchChangeRateScaleDownShift", ClutchChangeRateScaleDownShiftGetter, ClutchChangeRateScaleDownShiftSetter);
    tpl.Property("initialDriveForce", InitialDriveForceGetter, InitialDriveForceSetter);
    tpl.Property("driveMaxFlatVel", DriveMaxFlatVelGetter, DriveMaxFlatVelSetter);
    tpl.Property("initialDriveMaxFlatVel", InitialDriveMaxFlatVelGetter, InitialDriveMaxFlatVelSetter);
    tpl.Property("brakeForce", BrakeForceGetter, BrakeForceSetter);
    tpl.Property("brakeBiasFront", BrakeBiasFrontGetter, BrakeBiasFrontSetter);
    tpl.Property("brakeBiasRear", BrakeBiasRearGetter, BrakeBiasRearSetter);
    tpl.Property("handBrakeForce", HandBrakeForceGetter, HandBrakeForceSetter);
    tpl.Property("steeringLock", SteeringLockGetter, SteeringLockSetter);
    tpl.Property("steeringLockRatio", SteeringLockRatioGetter, SteeringLockRatioSetter);
    tpl.Property("tractionCurveMax", TractionCurveMaxGetter, TractionCurveMaxSetter);
    tpl.Property("tractionCurveMaxRatio", TractionCurveMaxRatioGetter, TractionCurveMaxRatioSetter);
    tpl.Property("tractionCurveMin", TractionCurveMinGetter, TractionCurveMinSetter);
    tpl.Property("tractionCurveMinRatio", TractionCurveMinRatioGetter, TractionCurveMinRatioSetter);
    tpl.Property("tractionCurveLateral", TractionCurveLateralGetter, TractionCurveLateralSetter);
    tpl.Property("tractionCurveLateralRatio", TractionCurveLateralRatioGetter, TractionCurveLateralRatioSetter);
    tpl.Property("tractionSpringDeltaMax", TractionSpringDeltaMaxGetter, TractionSpringDeltaMaxSetter);
    tpl.Property("tractionSpringDeltaMaxRatio", TractionSpringDeltaMaxRatioGetter, TractionSpringDeltaMaxRatioSetter);
    tpl.Property("lowSpeedTractionLossMult", LowSpeedTractionLossMultGetter, LowSpeedTractionLossMultSetter);
    tpl.Property("camberStiffness", CamberStiffnessGetter, CamberStiffnessSetter);
    tpl.Property("tractionBiasFront", TractionBiasFrontGetter, TractionBiasFrontSetter);
    tpl.Property("tractionBiasRear", TractionBiasRearGetter, TractionBiasRearSetter);
    tpl.Property("tractionLossMult", TractionLossMultGetter, TractionLossMultSetter);
    tpl.Property("suspensionForce", SuspensionForceGetter, SuspensionForceSetter);
    tpl.Property("suspensionCompDamp", SuspensionCompDampGetter, SuspensionCompDampSetter);
    tpl.Property("suspensionReboundDamp", SuspensionReboundDampGetter, SuspensionReboundDampSetter);
    tpl.Property("suspensionUpperLimit", SuspensionUpperLimitGetter, SuspensionUpperLimitSetter);
    tpl.Property("suspensionLowerLimit", SuspensionLowerLimitGetter, SuspensionLowerLimitSetter);
    tpl.Property("suspensionRaise", SuspensionRaiseGetter, SuspensionRaiseSetter);
    tpl.Property("suspensionBiasFront", SuspensionBiasFrontGetter, SuspensionBiasFrontSetter);
    tpl.Property("suspensionBiasRear", SuspensionBiasRearGetter, SuspensionBiasRearSetter);
    tpl.Property("antiRollBarForce", AntiRollBarForceGetter, AntiRollBarForceSetter);
    tpl.Property("antiRollBarBiasFront", AntiRollBarBiasFrontGetter, AntiRollBarBiasFrontSetter);
    tpl.Property("antiRollBarBiasRear", AntiRollBarBiasRearGetter, AntiRollBarBiasRearSetter);
    tpl.Property("rollCentreHeightFront", RollCentreHeightFrontGetter, RollCentreHeightFrontSetter);
    tpl.Property("rollCentreHeightRear", RollCentreHeightRearGetter, RollCentreHeightRearSetter);
    tpl.Property("collisionDamageMult", CollisionDamageMultGetter, CollisionDamageMultSetter);
    tpl.Property("weaponDamageMult", WeaponDamageMultGetter, WeaponDamageMultSetter);
    tpl.Property("deformationDamageMult", DeformationDamageMultGetter, DeformationDamageMultSetter);
    tpl.Property("engineDamageMult", EngineDamageMultGetter, EngineDamageMultSetter);
    tpl.Property("petrolTankVolume", PetrolTankVolumeGetter, PetrolTankVolumeSetter);
    tpl.Property("oilVolume", OilVolumeGetter, OilVolumeSetter);
    tpl.Property("seatOffsetDistX", SeatOffsetDistXGetter, SeatOffsetDistXSetter);
    tpl.Property("seatOffsetDistY", SeatOffsetDistYGetter, SeatOffsetDistYSetter);
    tpl.Property("seatOffsetDistZ", SeatOffsetDistZGetter, SeatOffsetDistZSetter);
    tpl.Property("monetaryValue", MonetaryValueGetter, MonetaryValueSetter);
    tpl.Property("modelFlags", ModelFlagsGetter, ModelFlagsSetter);
    tpl.Property("handlingFlags", HandlingFlagsGetter, HandlingFlagsSetter);
    tpl.Property("damageFlags", DamageFlagsGetter, DamageFlagsSetter);
    tpl.Property("isModified", IsModified);

    tpl.Method("reset", Reset);
}, true);
