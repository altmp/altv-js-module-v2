#include "Class.h"
#include "cpp-sdk/ICore.h"
#include "helpers/ClassInstanceCache.h"

static void HandlingNameHashGetter(js::LazyPropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldJSValue()) return;
    uint32_t modelHash = ctx.GetExtraInternalFieldJSValue<uint32_t>();
    auto handling = alt::ICore::Instance().GetHandlingData(modelHash);

    ctx.Return(handling->GetHandlingNameHash());
}

static void MassGetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldJSValue()) return;
    uint32_t modelHash = ctx.GetExtraInternalFieldJSValue<uint32_t>();
    auto handling = alt::ICore::Instance().GetHandlingData(modelHash);

    ctx.Return(handling->GetMass());
}

static void MassSetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldJSValue()) return;
    uint32_t modelHash = ctx.GetExtraInternalFieldJSValue<uint32_t>();
    auto handling = alt::ICore::Instance().GetHandlingData(modelHash);

    float value;
    if(!ctx.GetValue(value)) return;

    handling->SetMass(value);
}

static void InitialDragCoeffGetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldJSValue()) return;
    uint32_t modelHash = ctx.GetExtraInternalFieldJSValue<uint32_t>();
    auto handling = alt::ICore::Instance().GetHandlingData(modelHash);

    ctx.Return(handling->GetInitialDragCoeff());
}

static void InitialDragCoeffSetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldJSValue()) return;
    uint32_t modelHash = ctx.GetExtraInternalFieldJSValue<uint32_t>();
    auto handling = alt::ICore::Instance().GetHandlingData(modelHash);

    float value;
    if(!ctx.GetValue(value)) return;

    handling->SetInitialDragCoeff(value);
}

static void DownforceModifierGetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldJSValue()) return;
    uint32_t modelHash = ctx.GetExtraInternalFieldJSValue<uint32_t>();
    auto handling = alt::ICore::Instance().GetHandlingData(modelHash);

    ctx.Return(handling->GetDownforceModifier());
}

static void DownforceModifierSetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldJSValue()) return;
    uint32_t modelHash = ctx.GetExtraInternalFieldJSValue<uint32_t>();
    auto handling = alt::ICore::Instance().GetHandlingData(modelHash);

    float value;
    if(!ctx.GetValue(value)) return;

    handling->SetDownforceModifier(value);
}

static void unkFloat1Getter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldJSValue()) return;
    uint32_t modelHash = ctx.GetExtraInternalFieldJSValue<uint32_t>();
    auto handling = alt::ICore::Instance().GetHandlingData(modelHash);

    ctx.Return(handling->GetunkFloat1());
}

static void unkFloat1Setter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldJSValue()) return;
    uint32_t modelHash = ctx.GetExtraInternalFieldJSValue<uint32_t>();
    auto handling = alt::ICore::Instance().GetHandlingData(modelHash);

    float value;
    if(!ctx.GetValue(value)) return;

    handling->SetunkFloat1(value);
}

static void unkFloat2Getter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldJSValue()) return;
    uint32_t modelHash = ctx.GetExtraInternalFieldJSValue<uint32_t>();
    auto handling = alt::ICore::Instance().GetHandlingData(modelHash);

    ctx.Return(handling->GetunkFloat2());
}

static void unkFloat2Setter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldJSValue()) return;
    uint32_t modelHash = ctx.GetExtraInternalFieldJSValue<uint32_t>();
    auto handling = alt::ICore::Instance().GetHandlingData(modelHash);

    float value;
    if(!ctx.GetValue(value)) return;

    handling->SetunkFloat2(value);
}

static void unkFloat4Getter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldJSValue()) return;
    uint32_t modelHash = ctx.GetExtraInternalFieldJSValue<uint32_t>();
    auto handling = alt::ICore::Instance().GetHandlingData(modelHash);

    ctx.Return(handling->GetunkFloat4());
}

static void unkFloat4Setter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldJSValue()) return;
    uint32_t modelHash = ctx.GetExtraInternalFieldJSValue<uint32_t>();
    auto handling = alt::ICore::Instance().GetHandlingData(modelHash);

    float value;
    if(!ctx.GetValue(value)) return;

    handling->SetunkFloat4(value);
}

static void unkFloat5Getter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldJSValue()) return;
    uint32_t modelHash = ctx.GetExtraInternalFieldJSValue<uint32_t>();
    auto handling = alt::ICore::Instance().GetHandlingData(modelHash);

    ctx.Return(handling->GetunkFloat4());
}

static void unkFloat5Setter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldJSValue()) return;
    uint32_t modelHash = ctx.GetExtraInternalFieldJSValue<uint32_t>();
    auto handling = alt::ICore::Instance().GetHandlingData(modelHash);

    float value;
    if(!ctx.GetValue(value)) return;

    handling->SetunkFloat5(value);
}

static void CentreOfMassOffsetGetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldJSValue()) return;
    uint32_t modelHash = ctx.GetExtraInternalFieldJSValue<uint32_t>();
    auto handling = alt::ICore::Instance().GetHandlingData(modelHash);

    ctx.Return(handling->GetCentreOfMassOffset());
}

static void CentreOfMassOffsetSetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldJSValue()) return;
    uint32_t modelHash = ctx.GetExtraInternalFieldJSValue<uint32_t>();
    auto handling = alt::ICore::Instance().GetHandlingData(modelHash);

    alt::Vector3f pos;
    if(!ctx.GetValue(pos)) return;

    handling->SetCentreOfMassOffset(pos);
}

static void InertiaMultiplierGetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldJSValue()) return;
    uint32_t modelHash = ctx.GetExtraInternalFieldJSValue<uint32_t>();
    auto handling = alt::ICore::Instance().GetHandlingData(modelHash);

    ctx.Return(handling->GetInertiaMultiplier());
}

static void InertiaMultiplierSetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldJSValue()) return;
    uint32_t modelHash = ctx.GetExtraInternalFieldJSValue<uint32_t>();
    auto handling = alt::ICore::Instance().GetHandlingData(modelHash);

    alt::Vector3f pos;
    if(!ctx.GetValue(pos)) return;

    handling->SetInertiaMultiplier(pos);
}

static void PercentSubmergedGetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldJSValue()) return;
    uint32_t modelHash = ctx.GetExtraInternalFieldJSValue<uint32_t>();
    auto handling = alt::ICore::Instance().GetHandlingData(modelHash);

    ctx.Return(handling->GetPercentSubmerged());
}

static void PercentSubmergedSetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldJSValue()) return;
    uint32_t modelHash = ctx.GetExtraInternalFieldJSValue<uint32_t>();
    auto handling = alt::ICore::Instance().GetHandlingData(modelHash);

    float value;
    if(!ctx.GetValue(value)) return;

    handling->SetPercentSubmerged(value);
}

static void PercentSubmergedRatioGetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldJSValue()) return;
    uint32_t modelHash = ctx.GetExtraInternalFieldJSValue<uint32_t>();
    auto handling = alt::ICore::Instance().GetHandlingData(modelHash);

    ctx.Return(handling->GetPercentSubmergedRatio());
}

static void PercentSubmergedRatioSetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldJSValue()) return;
    uint32_t modelHash = ctx.GetExtraInternalFieldJSValue<uint32_t>();
    auto handling = alt::ICore::Instance().GetHandlingData(modelHash);

    float value;
    if(!ctx.GetValue(value)) return;

    handling->SetPercentSubmergedRatio(value);
}

static void DriveBiasFrontGetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldJSValue()) return;
    uint32_t modelHash = ctx.GetExtraInternalFieldJSValue<uint32_t>();
    auto handling = alt::ICore::Instance().GetHandlingData(modelHash);

    ctx.Return(handling->GetDriveBiasFront());
}

static void DriveBiasFrontSetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldJSValue()) return;
    uint32_t modelHash = ctx.GetExtraInternalFieldJSValue<uint32_t>();
    auto handling = alt::ICore::Instance().GetHandlingData(modelHash);

    float value;
    if(!ctx.GetValue(value)) return;

    handling->SetDriveBiasFront(value);
}

static void AccelerationGetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldJSValue()) return;
    uint32_t modelHash = ctx.GetExtraInternalFieldJSValue<uint32_t>();
    auto handling = alt::ICore::Instance().GetHandlingData(modelHash);

    ctx.Return(handling->GetAcceleration());
}

static void AccelerationSetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldJSValue()) return;
    uint32_t modelHash = ctx.GetExtraInternalFieldJSValue<uint32_t>();
    auto handling = alt::ICore::Instance().GetHandlingData(modelHash);

    float value;
    if(!ctx.GetValue(value)) return;

    handling->SetAcceleration(value);
}

static void InitialDriveGearsGetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldJSValue()) return;
    uint32_t modelHash = ctx.GetExtraInternalFieldJSValue<uint32_t>();
    auto handling = alt::ICore::Instance().GetHandlingData(modelHash);

    ctx.Return(handling->GetInitialDriveGears());
}

static void InitialDriveGearsSetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldJSValue()) return;
    uint32_t modelHash = ctx.GetExtraInternalFieldJSValue<uint32_t>();
    auto handling = alt::ICore::Instance().GetHandlingData(modelHash);

    uint32_t value;
    if(!ctx.GetValue(value)) return;

    handling->SetInitialDriveGears(value);
}

static void DriveInertiaGetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldJSValue()) return;
    uint32_t modelHash = ctx.GetExtraInternalFieldJSValue<uint32_t>();
    auto handling = alt::ICore::Instance().GetHandlingData(modelHash);

    ctx.Return(handling->GetDriveInertia());
}

static void DriveInertiaSetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldJSValue()) return;
    uint32_t modelHash = ctx.GetExtraInternalFieldJSValue<uint32_t>();
    auto handling = alt::ICore::Instance().GetHandlingData(modelHash);

    float value;
    if(!ctx.GetValue(value)) return;

    handling->SetDriveInertia(value);
}

static void ClutchChangeRateScaleUpShiftGetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldJSValue()) return;
    uint32_t modelHash = ctx.GetExtraInternalFieldJSValue<uint32_t>();
    auto handling = alt::ICore::Instance().GetHandlingData(modelHash);

    ctx.Return(handling->GetClutchChangeRateScaleUpShift());
}

static void ClutchChangeRateScaleUpShiftSetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldJSValue()) return;
    uint32_t modelHash = ctx.GetExtraInternalFieldJSValue<uint32_t>();
    auto handling = alt::ICore::Instance().GetHandlingData(modelHash);

    float value;
    if(!ctx.GetValue(value)) return;

    handling->SetClutchChangeRateScaleUpShift(value);
}

static void ClutchChangeRateScaleDownShiftGetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldJSValue()) return;
    uint32_t modelHash = ctx.GetExtraInternalFieldJSValue<uint32_t>();
    auto handling = alt::ICore::Instance().GetHandlingData(modelHash);

    ctx.Return(handling->GetClutchChangeRateScaleDownShift());
}

static void ClutchChangeRateScaleDownShiftSetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldJSValue()) return;
    uint32_t modelHash = ctx.GetExtraInternalFieldJSValue<uint32_t>();
    auto handling = alt::ICore::Instance().GetHandlingData(modelHash);

    float value;
    if(!ctx.GetValue(value)) return;

    handling->SetClutchChangeRateScaleDownShift(value);
}

static void InitialDriveForceGetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldJSValue()) return;
    uint32_t modelHash = ctx.GetExtraInternalFieldJSValue<uint32_t>();
    auto handling = alt::ICore::Instance().GetHandlingData(modelHash);

    ctx.Return(handling->GetInitialDriveForce());
}

static void InitialDriveForceSetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldJSValue()) return;
    uint32_t modelHash = ctx.GetExtraInternalFieldJSValue<uint32_t>();
    auto handling = alt::ICore::Instance().GetHandlingData(modelHash);

    float value;
    if(!ctx.GetValue(value)) return;

    handling->SetInitialDriveForce(value);
}

static void DriveMaxFlatVelGetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldJSValue()) return;
    uint32_t modelHash = ctx.GetExtraInternalFieldJSValue<uint32_t>();
    auto handling = alt::ICore::Instance().GetHandlingData(modelHash);

    ctx.Return(handling->GetDriveMaxFlatVel());
}

static void DriveMaxFlatVelSetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldJSValue()) return;
    uint32_t modelHash = ctx.GetExtraInternalFieldJSValue<uint32_t>();
    auto handling = alt::ICore::Instance().GetHandlingData(modelHash);

    float value;
    if(!ctx.GetValue(value)) return;

    handling->SetDriveMaxFlatVel(value);
}

static void InitialDriveMaxFlatVelGetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldJSValue()) return;
    uint32_t modelHash = ctx.GetExtraInternalFieldJSValue<uint32_t>();
    auto handling = alt::ICore::Instance().GetHandlingData(modelHash);

    ctx.Return(handling->GetInitialDriveMaxFlatVel());
}

static void InitialDriveMaxFlatVelSetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldJSValue()) return;
    uint32_t modelHash = ctx.GetExtraInternalFieldJSValue<uint32_t>();
    auto handling = alt::ICore::Instance().GetHandlingData(modelHash);

    float value;
    if(!ctx.GetValue(value)) return;

    handling->SetInitialDriveMaxFlatVel(value);
}

static void BrakeForceGetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldJSValue()) return;
    uint32_t modelHash = ctx.GetExtraInternalFieldJSValue<uint32_t>();
    auto handling = alt::ICore::Instance().GetHandlingData(modelHash);

    ctx.Return(handling->GetBrakeForce());
}

static void BrakeForceSetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldJSValue()) return;
    uint32_t modelHash = ctx.GetExtraInternalFieldJSValue<uint32_t>();
    auto handling = alt::ICore::Instance().GetHandlingData(modelHash);

    float value;
    if(!ctx.GetValue(value)) return;

    handling->SetBrakeForce(value);
}

static void BrakeBiasFrontGetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldJSValue()) return;
    uint32_t modelHash = ctx.GetExtraInternalFieldJSValue<uint32_t>();
    auto handling = alt::ICore::Instance().GetHandlingData(modelHash);

    ctx.Return(handling->GetBrakeBiasFront());
}

static void BrakeBiasFrontSetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldJSValue()) return;
    uint32_t modelHash = ctx.GetExtraInternalFieldJSValue<uint32_t>();
    auto handling = alt::ICore::Instance().GetHandlingData(modelHash);

    float value;
    if(!ctx.GetValue(value)) return;

    handling->SetBrakeBiasFront(value);
}

static void BrakeBiasRearGetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldJSValue()) return;
    uint32_t modelHash = ctx.GetExtraInternalFieldJSValue<uint32_t>();
    auto handling = alt::ICore::Instance().GetHandlingData(modelHash);

    ctx.Return(handling->GetBrakeBiasRear());
}

static void BrakeBiasRearSetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldJSValue()) return;
    uint32_t modelHash = ctx.GetExtraInternalFieldJSValue<uint32_t>();
    auto handling = alt::ICore::Instance().GetHandlingData(modelHash);

    float value;
    if(!ctx.GetValue(value)) return;

    handling->SetBrakeBiasRear(value);
}

static void HandBrakeForceGetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldJSValue()) return;
    uint32_t modelHash = ctx.GetExtraInternalFieldJSValue<uint32_t>();
    auto handling = alt::ICore::Instance().GetHandlingData(modelHash);

    ctx.Return(handling->GetHandBrakeForce());
}

static void HandBrakeForceSetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldJSValue()) return;
    uint32_t modelHash = ctx.GetExtraInternalFieldJSValue<uint32_t>();
    auto handling = alt::ICore::Instance().GetHandlingData(modelHash);

    float value;
    if(!ctx.GetValue(value)) return;

    handling->SetHandBrakeForce(value);
}

static void SteeringLockGetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldJSValue()) return;
    uint32_t modelHash = ctx.GetExtraInternalFieldJSValue<uint32_t>();
    auto handling = alt::ICore::Instance().GetHandlingData(modelHash);

    ctx.Return(handling->GetSteeringLock());
}

static void SteeringLockSetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldJSValue()) return;
    uint32_t modelHash = ctx.GetExtraInternalFieldJSValue<uint32_t>();
    auto handling = alt::ICore::Instance().GetHandlingData(modelHash);

    float value;
    if(!ctx.GetValue(value)) return;

    handling->SetSteeringLock(value);
}

static void SteeringLockRatioGetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldJSValue()) return;
    uint32_t modelHash = ctx.GetExtraInternalFieldJSValue<uint32_t>();
    auto handling = alt::ICore::Instance().GetHandlingData(modelHash);

    ctx.Return(handling->GetSteeringLockRatio());
}

static void SteeringLockRatioSetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldJSValue()) return;
    uint32_t modelHash = ctx.GetExtraInternalFieldJSValue<uint32_t>();
    auto handling = alt::ICore::Instance().GetHandlingData(modelHash);

    float value;
    if(!ctx.GetValue(value)) return;

    handling->SetSteeringLockRatio(value);
}

static void TractionCurveMaxGetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldJSValue()) return;
    uint32_t modelHash = ctx.GetExtraInternalFieldJSValue<uint32_t>();
    auto handling = alt::ICore::Instance().GetHandlingData(modelHash);

    ctx.Return(handling->GetTractionCurveMax());
}

static void TractionCurveMaxSetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldJSValue()) return;
    uint32_t modelHash = ctx.GetExtraInternalFieldJSValue<uint32_t>();
    auto handling = alt::ICore::Instance().GetHandlingData(modelHash);

    float value;
    if(!ctx.GetValue(value)) return;

    handling->SetTractionCurveMax(value);
}

static void TractionCurveMaxRatioGetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldJSValue()) return;
    uint32_t modelHash = ctx.GetExtraInternalFieldJSValue<uint32_t>();
    auto handling = alt::ICore::Instance().GetHandlingData(modelHash);

    ctx.Return(handling->GetTractionCurveMaxRatio());
}

static void TractionCurveMaxRatioSetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldJSValue()) return;
    uint32_t modelHash = ctx.GetExtraInternalFieldJSValue<uint32_t>();
    auto handling = alt::ICore::Instance().GetHandlingData(modelHash);

    float value;
    if(!ctx.GetValue(value)) return;

    handling->SetTractionCurveMaxRatio(value);
}

static void TractionCurveMinGetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldJSValue()) return;
    uint32_t modelHash = ctx.GetExtraInternalFieldJSValue<uint32_t>();
    auto handling = alt::ICore::Instance().GetHandlingData(modelHash);

    ctx.Return(handling->GetTractionCurveMin());
}

static void TractionCurveMinSetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldJSValue()) return;
    uint32_t modelHash = ctx.GetExtraInternalFieldJSValue<uint32_t>();
    auto handling = alt::ICore::Instance().GetHandlingData(modelHash);

    float value;
    if(!ctx.GetValue(value)) return;

    handling->SetTractionCurveMin(value);
}

static void TractionCurveMinRatioGetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldJSValue()) return;
    uint32_t modelHash = ctx.GetExtraInternalFieldJSValue<uint32_t>();
    auto handling = alt::ICore::Instance().GetHandlingData(modelHash);

    ctx.Return(handling->GetTractionCurveMinRatio());
}

static void TractionCurveMinRatioSetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldJSValue()) return;
    uint32_t modelHash = ctx.GetExtraInternalFieldJSValue<uint32_t>();
    auto handling = alt::ICore::Instance().GetHandlingData(modelHash);

    float value;
    if(!ctx.GetValue(value)) return;

    handling->SetTractionCurveMinRatio(value);
}

static void TractionCurveLateralGetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldJSValue()) return;
    uint32_t modelHash = ctx.GetExtraInternalFieldJSValue<uint32_t>();
    auto handling = alt::ICore::Instance().GetHandlingData(modelHash);

    ctx.Return(handling->GetTractionCurveLateral());
}

static void TractionCurveLateralSetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldJSValue()) return;
    uint32_t modelHash = ctx.GetExtraInternalFieldJSValue<uint32_t>();
    auto handling = alt::ICore::Instance().GetHandlingData(modelHash);

    float value;
    if(!ctx.GetValue(value)) return;

    handling->SetTractionCurveLateral(value);
}

static void TractionCurveLateralRatioGetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldJSValue()) return;
    uint32_t modelHash = ctx.GetExtraInternalFieldJSValue<uint32_t>();
    auto handling = alt::ICore::Instance().GetHandlingData(modelHash);

    ctx.Return(handling->GetTractionCurveLateralRatio());
}

static void TractionCurveLateralRatioSetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldJSValue()) return;
    uint32_t modelHash = ctx.GetExtraInternalFieldJSValue<uint32_t>();
    auto handling = alt::ICore::Instance().GetHandlingData(modelHash);

    float value;
    if(!ctx.GetValue(value)) return;

    handling->SetTractionCurveLateralRatio(value);
}

static void TractionSpringDeltaMaxGetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldJSValue()) return;
    uint32_t modelHash = ctx.GetExtraInternalFieldJSValue<uint32_t>();
    auto handling = alt::ICore::Instance().GetHandlingData(modelHash);

    ctx.Return(handling->GetTractionSpringDeltaMax());
}

static void TractionSpringDeltaMaxSetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldJSValue()) return;
    uint32_t modelHash = ctx.GetExtraInternalFieldJSValue<uint32_t>();
    auto handling = alt::ICore::Instance().GetHandlingData(modelHash);

    float value;
    if(!ctx.GetValue(value)) return;

    handling->SetTractionSpringDeltaMax(value);
}

static void TractionSpringDeltaMaxRatioGetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldJSValue()) return;
    uint32_t modelHash = ctx.GetExtraInternalFieldJSValue<uint32_t>();
    auto handling = alt::ICore::Instance().GetHandlingData(modelHash);

    ctx.Return(handling->GetTractionSpringDeltaMaxRatio());
}

static void TractionSpringDeltaMaxRatioSetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldJSValue()) return;
    uint32_t modelHash = ctx.GetExtraInternalFieldJSValue<uint32_t>();
    auto handling = alt::ICore::Instance().GetHandlingData(modelHash);

    float value;
    if(!ctx.GetValue(value)) return;

    handling->SetTractionSpringDeltaMaxRatio(value);
}

static void LowSpeedTractionLossMultGetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldJSValue()) return;
    uint32_t modelHash = ctx.GetExtraInternalFieldJSValue<uint32_t>();
    auto handling = alt::ICore::Instance().GetHandlingData(modelHash);

    ctx.Return(handling->GetLowSpeedTractionLossMult());
}

static void LowSpeedTractionLossMultSetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldJSValue()) return;
    uint32_t modelHash = ctx.GetExtraInternalFieldJSValue<uint32_t>();
    auto handling = alt::ICore::Instance().GetHandlingData(modelHash);

    float value;
    if(!ctx.GetValue(value)) return;

    handling->SetLowSpeedTractionLossMult(value);
}

static void CamberStiffnessGetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldJSValue()) return;
    uint32_t modelHash = ctx.GetExtraInternalFieldJSValue<uint32_t>();
    auto handling = alt::ICore::Instance().GetHandlingData(modelHash);

    ctx.Return(handling->GetCamberStiffness());
}

static void CamberStiffnessSetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldJSValue()) return;
    uint32_t modelHash = ctx.GetExtraInternalFieldJSValue<uint32_t>();
    auto handling = alt::ICore::Instance().GetHandlingData(modelHash);

    float value;
    if(!ctx.GetValue(value)) return;

    handling->SetCamberStiffness(value);
}

static void TractionBiasFrontGetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldJSValue()) return;
    uint32_t modelHash = ctx.GetExtraInternalFieldJSValue<uint32_t>();
    auto handling = alt::ICore::Instance().GetHandlingData(modelHash);

    ctx.Return(handling->GetTractionBiasFront());
}

static void TractionBiasFrontSetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldJSValue()) return;
    uint32_t modelHash = ctx.GetExtraInternalFieldJSValue<uint32_t>();
    auto handling = alt::ICore::Instance().GetHandlingData(modelHash);

    float value;
    if(!ctx.GetValue(value)) return;

    handling->SetTractionBiasFront(value);
}

static void TractionBiasRearGetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldJSValue()) return;
    uint32_t modelHash = ctx.GetExtraInternalFieldJSValue<uint32_t>();
    auto handling = alt::ICore::Instance().GetHandlingData(modelHash);

    ctx.Return(handling->GetTractionBiasRear());
}

static void TractionBiasRearSetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldJSValue()) return;
    uint32_t modelHash = ctx.GetExtraInternalFieldJSValue<uint32_t>();
    auto handling = alt::ICore::Instance().GetHandlingData(modelHash);

    float value;
    if(!ctx.GetValue(value)) return;

    handling->SetTractionBiasRear(value);
}

static void TractionLossMultGetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldJSValue()) return;
    uint32_t modelHash = ctx.GetExtraInternalFieldJSValue<uint32_t>();
    auto handling = alt::ICore::Instance().GetHandlingData(modelHash);

    ctx.Return(handling->GetTractionLossMult());
}

static void TractionLossMultSetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldJSValue()) return;
    uint32_t modelHash = ctx.GetExtraInternalFieldJSValue<uint32_t>();
    auto handling = alt::ICore::Instance().GetHandlingData(modelHash);

    float value;
    if(!ctx.GetValue(value)) return;

    handling->SetTractionLossMult(value);
}

static void SuspensionForceGetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldJSValue()) return;
    uint32_t modelHash = ctx.GetExtraInternalFieldJSValue<uint32_t>();
    auto handling = alt::ICore::Instance().GetHandlingData(modelHash);

    ctx.Return(handling->GetSuspensionForce());
}

static void SuspensionForceSetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldJSValue()) return;
    uint32_t modelHash = ctx.GetExtraInternalFieldJSValue<uint32_t>();
    auto handling = alt::ICore::Instance().GetHandlingData(modelHash);

    float value;
    if(!ctx.GetValue(value)) return;

    handling->SetSuspensionForce(value);
}

static void SuspensionCompDampGetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldJSValue()) return;
    uint32_t modelHash = ctx.GetExtraInternalFieldJSValue<uint32_t>();
    auto handling = alt::ICore::Instance().GetHandlingData(modelHash);

    ctx.Return(handling->GetSuspensionCompDamp());
}

static void SuspensionCompDampSetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldJSValue()) return;
    uint32_t modelHash = ctx.GetExtraInternalFieldJSValue<uint32_t>();
    auto handling = alt::ICore::Instance().GetHandlingData(modelHash);

    float value;
    if(!ctx.GetValue(value)) return;

    handling->SetSuspensionCompDamp(value);
}

static void SuspensionReboundDampGetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldJSValue()) return;
    uint32_t modelHash = ctx.GetExtraInternalFieldJSValue<uint32_t>();
    auto handling = alt::ICore::Instance().GetHandlingData(modelHash);

    ctx.Return(handling->GetSuspensionReboundDamp());
}

static void SuspensionReboundDampSetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldJSValue()) return;
    uint32_t modelHash = ctx.GetExtraInternalFieldJSValue<uint32_t>();
    auto handling = alt::ICore::Instance().GetHandlingData(modelHash);

    float value;
    if(!ctx.GetValue(value)) return;

    handling->SetSuspensionReboundDamp(value);
}

static void SuspensionUpperLimitGetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldJSValue()) return;
    uint32_t modelHash = ctx.GetExtraInternalFieldJSValue<uint32_t>();
    auto handling = alt::ICore::Instance().GetHandlingData(modelHash);

    ctx.Return(handling->GetSuspensionUpperLimit());
}

static void SuspensionUpperLimitSetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldJSValue()) return;
    uint32_t modelHash = ctx.GetExtraInternalFieldJSValue<uint32_t>();
    auto handling = alt::ICore::Instance().GetHandlingData(modelHash);

    float value;
    if(!ctx.GetValue(value)) return;

    handling->SetSuspensionUpperLimit(value);
}

static void SuspensionLowerLimitGetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldJSValue()) return;
    uint32_t modelHash = ctx.GetExtraInternalFieldJSValue<uint32_t>();
    auto handling = alt::ICore::Instance().GetHandlingData(modelHash);

    ctx.Return(handling->GetSuspensionLowerLimit());
}

static void SuspensionLowerLimitSetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldJSValue()) return;
    uint32_t modelHash = ctx.GetExtraInternalFieldJSValue<uint32_t>();
    auto handling = alt::ICore::Instance().GetHandlingData(modelHash);

    float value;
    if(!ctx.GetValue(value)) return;

    handling->SetSuspensionLowerLimit(value);
}

static void SuspensionRaiseGetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldJSValue()) return;
    uint32_t modelHash = ctx.GetExtraInternalFieldJSValue<uint32_t>();
    auto handling = alt::ICore::Instance().GetHandlingData(modelHash);

    ctx.Return(handling->GetSuspensionRaise());
}

static void SuspensionRaiseSetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldJSValue()) return;
    uint32_t modelHash = ctx.GetExtraInternalFieldJSValue<uint32_t>();
    auto handling = alt::ICore::Instance().GetHandlingData(modelHash);

    float value;
    if(!ctx.GetValue(value)) return;

    handling->SetSuspensionRaise(value);
}

static void SuspensionBiasFrontGetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldJSValue()) return;
    uint32_t modelHash = ctx.GetExtraInternalFieldJSValue<uint32_t>();
    auto handling = alt::ICore::Instance().GetHandlingData(modelHash);

    ctx.Return(handling->GetSuspensionBiasFront());
}

static void SuspensionBiasFrontSetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldJSValue()) return;
    uint32_t modelHash = ctx.GetExtraInternalFieldJSValue<uint32_t>();
    auto handling = alt::ICore::Instance().GetHandlingData(modelHash);

    float value;
    if(!ctx.GetValue(value)) return;

    handling->SetSuspensionBiasFront(value);
}

static void SuspensionBiasRearGetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldJSValue()) return;
    uint32_t modelHash = ctx.GetExtraInternalFieldJSValue<uint32_t>();
    auto handling = alt::ICore::Instance().GetHandlingData(modelHash);

    ctx.Return(handling->GetSuspensionBiasRear());
}

static void SuspensionBiasRearSetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldJSValue()) return;
    uint32_t modelHash = ctx.GetExtraInternalFieldJSValue<uint32_t>();
    auto handling = alt::ICore::Instance().GetHandlingData(modelHash);

    float value;
    if(!ctx.GetValue(value)) return;

    handling->SetSuspensionBiasRear(value);
}

static void AntiRollBarForceGetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldJSValue()) return;
    uint32_t modelHash = ctx.GetExtraInternalFieldJSValue<uint32_t>();
    auto handling = alt::ICore::Instance().GetHandlingData(modelHash);

    ctx.Return(handling->GetAntiRollBarForce());
}

static void AntiRollBarForceSetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldJSValue()) return;
    uint32_t modelHash = ctx.GetExtraInternalFieldJSValue<uint32_t>();
    auto handling = alt::ICore::Instance().GetHandlingData(modelHash);

    float value;
    if(!ctx.GetValue(value)) return;

    handling->SetAntiRollBarForce(value);
}

static void AntiRollBarBiasFrontGetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldJSValue()) return;
    uint32_t modelHash = ctx.GetExtraInternalFieldJSValue<uint32_t>();
    auto handling = alt::ICore::Instance().GetHandlingData(modelHash);

    ctx.Return(handling->GetAntiRollBarBiasFront());
}

static void AntiRollBarBiasFrontSetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldJSValue()) return;
    uint32_t modelHash = ctx.GetExtraInternalFieldJSValue<uint32_t>();
    auto handling = alt::ICore::Instance().GetHandlingData(modelHash);

    float value;
    if(!ctx.GetValue(value)) return;

    handling->SetAntiRollBarBiasFront(value);
}

static void AntiRollBarBiasRearGetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldJSValue()) return;
    uint32_t modelHash = ctx.GetExtraInternalFieldJSValue<uint32_t>();
    auto handling = alt::ICore::Instance().GetHandlingData(modelHash);

    ctx.Return(handling->GetAntiRollBarBiasRear());
}

static void AntiRollBarBiasRearSetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldJSValue()) return;
    uint32_t modelHash = ctx.GetExtraInternalFieldJSValue<uint32_t>();
    auto handling = alt::ICore::Instance().GetHandlingData(modelHash);

    float value;
    if(!ctx.GetValue(value)) return;

    handling->SetAntiRollBarBiasRear(value);
}

static void RollCentreHeightFrontGetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldJSValue()) return;
    uint32_t modelHash = ctx.GetExtraInternalFieldJSValue<uint32_t>();
    auto handling = alt::ICore::Instance().GetHandlingData(modelHash);

    ctx.Return(handling->GetRollCentreHeightFront());
}

static void RollCentreHeightFrontSetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldJSValue()) return;
    uint32_t modelHash = ctx.GetExtraInternalFieldJSValue<uint32_t>();
    auto handling = alt::ICore::Instance().GetHandlingData(modelHash);

    float value;
    if(!ctx.GetValue(value)) return;

    handling->SetRollCentreHeightFront(value);
}

static void RollCentreHeightRearGetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldJSValue()) return;
    uint32_t modelHash = ctx.GetExtraInternalFieldJSValue<uint32_t>();
    auto handling = alt::ICore::Instance().GetHandlingData(modelHash);

    ctx.Return(handling->GetRollCentreHeightRear());
}

static void RollCentreHeightRearSetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldJSValue()) return;
    uint32_t modelHash = ctx.GetExtraInternalFieldJSValue<uint32_t>();
    auto handling = alt::ICore::Instance().GetHandlingData(modelHash);

    float value;
    if(!ctx.GetValue(value)) return;

    handling->SetRollCentreHeightRear(value);
}

static void CollisionDamageMultGetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldJSValue()) return;
    uint32_t modelHash = ctx.GetExtraInternalFieldJSValue<uint32_t>();
    auto handling = alt::ICore::Instance().GetHandlingData(modelHash);

    ctx.Return(handling->GetCollisionDamageMult());
}

static void CollisionDamageMultSetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldJSValue()) return;
    uint32_t modelHash = ctx.GetExtraInternalFieldJSValue<uint32_t>();
    auto handling = alt::ICore::Instance().GetHandlingData(modelHash);

    float value;
    if(!ctx.GetValue(value)) return;

    handling->SetCollisionDamageMult(value);
}

static void WeaponDamageMultGetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldJSValue()) return;
    uint32_t modelHash = ctx.GetExtraInternalFieldJSValue<uint32_t>();
    auto handling = alt::ICore::Instance().GetHandlingData(modelHash);

    ctx.Return(handling->GetWeaponDamageMult());
}

static void WeaponDamageMultSetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldJSValue()) return;
    uint32_t modelHash = ctx.GetExtraInternalFieldJSValue<uint32_t>();
    auto handling = alt::ICore::Instance().GetHandlingData(modelHash);

    float value;
    if(!ctx.GetValue(value)) return;

    handling->SetWeaponDamageMult(value);
}

static void DeformationDamageMultGetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldJSValue()) return;
    uint32_t modelHash = ctx.GetExtraInternalFieldJSValue<uint32_t>();
    auto handling = alt::ICore::Instance().GetHandlingData(modelHash);

    ctx.Return(handling->GetDeformationDamageMult());
}

static void DeformationDamageMultSetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldJSValue()) return;
    uint32_t modelHash = ctx.GetExtraInternalFieldJSValue<uint32_t>();
    auto handling = alt::ICore::Instance().GetHandlingData(modelHash);

    float value;
    if(!ctx.GetValue(value)) return;

    handling->SetDeformationDamageMult(value);
}

static void EngineDamageMultGetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldJSValue()) return;
    uint32_t modelHash = ctx.GetExtraInternalFieldJSValue<uint32_t>();
    auto handling = alt::ICore::Instance().GetHandlingData(modelHash);

    ctx.Return(handling->GetEngineDamageMult());
}

static void EngineDamageMultSetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldJSValue()) return;
    uint32_t modelHash = ctx.GetExtraInternalFieldJSValue<uint32_t>();
    auto handling = alt::ICore::Instance().GetHandlingData(modelHash);

    float value;
    if(!ctx.GetValue(value)) return;

    handling->SetEngineDamageMult(value);
}

static void PetrolTankVolumeGetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldJSValue()) return;
    uint32_t modelHash = ctx.GetExtraInternalFieldJSValue<uint32_t>();
    auto handling = alt::ICore::Instance().GetHandlingData(modelHash);

    ctx.Return(handling->GetPetrolTankVolume());
}

static void PetrolTankVolumeSetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldJSValue()) return;
    uint32_t modelHash = ctx.GetExtraInternalFieldJSValue<uint32_t>();
    auto handling = alt::ICore::Instance().GetHandlingData(modelHash);

    float value;
    if(!ctx.GetValue(value)) return;

    handling->SetPetrolTankVolume(value);
}

static void OilVolumeGetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldJSValue()) return;
    uint32_t modelHash = ctx.GetExtraInternalFieldJSValue<uint32_t>();
    auto handling = alt::ICore::Instance().GetHandlingData(modelHash);

    ctx.Return(handling->GetOilVolume());
}

static void OilVolumeSetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldJSValue()) return;
    uint32_t modelHash = ctx.GetExtraInternalFieldJSValue<uint32_t>();
    auto handling = alt::ICore::Instance().GetHandlingData(modelHash);

    float value;
    if(!ctx.GetValue(value)) return;

    handling->SetOilVolume(value);
}

static void SeatOffsetDistXGetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldJSValue()) return;
    uint32_t modelHash = ctx.GetExtraInternalFieldJSValue<uint32_t>();
    auto handling = alt::ICore::Instance().GetHandlingData(modelHash);

    ctx.Return(handling->GetSeatOffsetDistX());
}

static void SeatOffsetDistXSetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldJSValue()) return;
    uint32_t modelHash = ctx.GetExtraInternalFieldJSValue<uint32_t>();
    auto handling = alt::ICore::Instance().GetHandlingData(modelHash);

    float value;
    if(!ctx.GetValue(value)) return;

    handling->SetSeatOffsetDistX(value);
}

static void SeatOffsetDistYGetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldJSValue()) return;
    uint32_t modelHash = ctx.GetExtraInternalFieldJSValue<uint32_t>();
    auto handling = alt::ICore::Instance().GetHandlingData(modelHash);

    ctx.Return(handling->GetSeatOffsetDistY());
}

static void SeatOffsetDistYSetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldJSValue()) return;
    uint32_t modelHash = ctx.GetExtraInternalFieldJSValue<uint32_t>();
    auto handling = alt::ICore::Instance().GetHandlingData(modelHash);

    float value;
    if(!ctx.GetValue(value)) return;

    handling->SetSeatOffsetDistY(value);
}

static void SeatOffsetDistZGetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldJSValue()) return;
    uint32_t modelHash = ctx.GetExtraInternalFieldJSValue<uint32_t>();
    auto handling = alt::ICore::Instance().GetHandlingData(modelHash);

    ctx.Return(handling->GetSeatOffsetDistZ());
}

static void SeatOffsetDistZSetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldJSValue()) return;
    uint32_t modelHash = ctx.GetExtraInternalFieldJSValue<uint32_t>();
    auto handling = alt::ICore::Instance().GetHandlingData(modelHash);

    float value;
    if(!ctx.GetValue(value)) return;

    handling->SetSeatOffsetDistZ(value);
}

static void MonetaryValueGetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldJSValue()) return;
    uint32_t modelHash = ctx.GetExtraInternalFieldJSValue<uint32_t>();
    auto handling = alt::ICore::Instance().GetHandlingData(modelHash);

    ctx.Return(handling->GetMonetaryValue());
}

static void MonetaryValueSetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldJSValue()) return;
    uint32_t modelHash = ctx.GetExtraInternalFieldJSValue<uint32_t>();
    auto handling = alt::ICore::Instance().GetHandlingData(modelHash);

    uint32_t value;
    if(!ctx.GetValue(value)) return;

    handling->SetMonetaryValue(value);
}

static void ModelFlagsGetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldJSValue()) return;
    uint32_t modelHash = ctx.GetExtraInternalFieldJSValue<uint32_t>();
    auto handling = alt::ICore::Instance().GetHandlingData(modelHash);

    ctx.Return(handling->GetModelFlags());
}

static void ModelFlagsSetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldJSValue()) return;
    uint32_t modelHash = ctx.GetExtraInternalFieldJSValue<uint32_t>();
    auto handling = alt::ICore::Instance().GetHandlingData(modelHash);

    uint32_t value;
    if(!ctx.GetValue(value)) return;

    handling->SetModelFlags(value);
}

static void HandlingFlagsGetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldJSValue()) return;
    uint32_t modelHash = ctx.GetExtraInternalFieldJSValue<uint32_t>();
    auto handling = alt::ICore::Instance().GetHandlingData(modelHash);

    ctx.Return(handling->GetHandlingFlags());
}

static void HandlingFlagsSetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldJSValue()) return;
    uint32_t modelHash = ctx.GetExtraInternalFieldJSValue<uint32_t>();
    auto handling = alt::ICore::Instance().GetHandlingData(modelHash);

    uint32_t value;
    if(!ctx.GetValue(value)) return;

    handling->SetHandlingFlags(value);
}

static void DamageFlagsGetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldJSValue()) return;
    uint32_t modelHash = ctx.GetExtraInternalFieldJSValue<uint32_t>();
    auto handling = alt::ICore::Instance().GetHandlingData(modelHash);

    ctx.Return(handling->GetDamageFlags());
}

static void DamageFlagsSetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldJSValue()) return;
    uint32_t modelHash = ctx.GetExtraInternalFieldJSValue<uint32_t>();
    auto handling = alt::ICore::Instance().GetHandlingData(modelHash);

    uint32_t value;
    if(!ctx.GetValue(value)) return;

    handling->SetDamageFlags(value);
}

extern js::Class handlingDataClass;
static js::ClassInstanceCache cache(handlingDataClass);
static void Get(js::FunctionContext& ctx)
{
    if(!ctx.CheckArgCount(1)) return;

    uint32_t modelHash;
    if(!ctx.GetArgAsHash(0, modelHash)) return;

    auto data = alt::ICore::Instance().GetHandlingData(modelHash);
    if(!ctx.Check(data != nullptr, "No HandlingData exists with this hash")) return;

    ctx.Return(cache.GetOrCreate(ctx.GetResource(), modelHash));
}

// clang-format off
extern js::Class handlingDataClass("HandlingData", [](js::ClassTemplate& tpl)
{
    tpl.LazyProperty("handlingNameHash", HandlingNameHashGetter);
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

    tpl.StaticFunction("get", Get);
}, true);
