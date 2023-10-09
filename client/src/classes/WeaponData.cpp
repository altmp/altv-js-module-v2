#include "Class.h"
#include "cpp-sdk/ICore.h"
#include "helpers/ClassInstanceCache.h"

static void ModelHashGetter(js::LazyPropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldJSValue()) return;
    uint32_t weaponHash = ctx.GetExtraInternalFieldJSValue<uint32_t>();
    auto weaponData = alt::ICore::Instance().GetWeaponData(weaponHash);

    ctx.Return(weaponData->GetModelHash());
}

static void NameHashGetter(js::LazyPropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldJSValue()) return;
    uint32_t weaponHash = ctx.GetExtraInternalFieldJSValue<uint32_t>();
    auto weaponData = alt::ICore::Instance().GetWeaponData(weaponHash);

    ctx.Return(weaponData->GetNameHash());
}

static void RecoilShakeAmplitudeGetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldJSValue()) return;
    uint32_t weaponHash = ctx.GetExtraInternalFieldJSValue<uint32_t>();
    auto weaponData = alt::ICore::Instance().GetWeaponData(weaponHash);

    ctx.Return(weaponData->GetRecoilShakeAmplitude());
}

static void RecoilShakeAmplitudeSetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldJSValue()) return;
    uint32_t weaponHash = ctx.GetExtraInternalFieldJSValue<uint32_t>();
    auto weaponData = alt::ICore::Instance().GetWeaponData(weaponHash);

    float value;
    if(!ctx.GetValue(value)) return;

    weaponData->SetRecoilShakeAmplitude(value);
}

static void RecoilAccuracyMaxGetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldJSValue()) return;
    uint32_t weaponHash = ctx.GetExtraInternalFieldJSValue<uint32_t>();
    auto weaponData = alt::ICore::Instance().GetWeaponData(weaponHash);

    ctx.Return(weaponData->GetRecoilAccuracyMax());
}

static void RecoilAccuracyMaxSetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldJSValue()) return;
    uint32_t weaponHash = ctx.GetExtraInternalFieldJSValue<uint32_t>();
    auto weaponData = alt::ICore::Instance().GetWeaponData(weaponHash);

    float value;
    if(!ctx.GetValue(value)) return;

    weaponData->SetRecoilAccuracyMax(value);
}

static void RecoilAccuracyToAllowHeadshotPlayerGetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldJSValue()) return;
    uint32_t weaponHash = ctx.GetExtraInternalFieldJSValue<uint32_t>();
    auto weaponData = alt::ICore::Instance().GetWeaponData(weaponHash);

    ctx.Return(weaponData->GetRecoilAccuracyToAllowHeadshotPlayer());
}

static void RecoilAccuracyToAllowHeadshotPlayerSetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldJSValue()) return;
    uint32_t weaponHash = ctx.GetExtraInternalFieldJSValue<uint32_t>();
    auto weaponData = alt::ICore::Instance().GetWeaponData(weaponHash);

    float value;
    if(!ctx.GetValue(value)) return;

    weaponData->SetRecoilAccuracyToAllowHeadshotPlayer(value);
}

static void RecoilRecoveryRateGetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldJSValue()) return;
    uint32_t weaponHash = ctx.GetExtraInternalFieldJSValue<uint32_t>();
    auto weaponData = alt::ICore::Instance().GetWeaponData(weaponHash);

    ctx.Return(weaponData->GetRecoilRecoveryRate());
}

static void RecoilRecoveryRateSetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldJSValue()) return;
    uint32_t weaponHash = ctx.GetExtraInternalFieldJSValue<uint32_t>();
    auto weaponData = alt::ICore::Instance().GetWeaponData(weaponHash);

    float value;
    if(!ctx.GetValue(value)) return;

    weaponData->SetRecoilRecoveryRate(value);
}

static void AnimReloadRateGetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldJSValue()) return;
    uint32_t weaponHash = ctx.GetExtraInternalFieldJSValue<uint32_t>();
    auto weaponData = alt::ICore::Instance().GetWeaponData(weaponHash);

    ctx.Return(weaponData->GetAnimReloadRate());
}

static void AnimReloadRateSetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldJSValue()) return;
    uint32_t weaponHash = ctx.GetExtraInternalFieldJSValue<uint32_t>();
    auto weaponData = alt::ICore::Instance().GetWeaponData(weaponHash);

    float value;
    if(!ctx.GetValue(value)) return;

    weaponData->SetAnimReloadRate(value);
}

static void VehicleReloadRateGetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldJSValue()) return;
    uint32_t weaponHash = ctx.GetExtraInternalFieldJSValue<uint32_t>();
    auto weaponData = alt::ICore::Instance().GetWeaponData(weaponHash);

    ctx.Return(weaponData->GetVehicleReloadTime());
}

static void VehicleReloadTimeSetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldJSValue()) return;
    uint32_t weaponHash = ctx.GetExtraInternalFieldJSValue<uint32_t>();
    auto weaponData = alt::ICore::Instance().GetWeaponData(weaponHash);

    float value;
    if(!ctx.GetValue(value)) return;

    weaponData->SetVehicleReloadTime(value);
}

static void LockOnRangeGetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldJSValue()) return;
    uint32_t weaponHash = ctx.GetExtraInternalFieldJSValue<uint32_t>();
    auto weaponData = alt::ICore::Instance().GetWeaponData(weaponHash);

    ctx.Return(weaponData->GetLockOnRange());
}

static void LockOnRangeSetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldJSValue()) return;
    uint32_t weaponHash = ctx.GetExtraInternalFieldJSValue<uint32_t>();
    auto weaponData = alt::ICore::Instance().GetWeaponData(weaponHash);

    float value;
    if(!ctx.GetValue(value)) return;

    weaponData->SetLockOnRange(value);
}

static void AccuracySpreadGetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldJSValue()) return;
    uint32_t weaponHash = ctx.GetExtraInternalFieldJSValue<uint32_t>();
    auto weaponData = alt::ICore::Instance().GetWeaponData(weaponHash);

    ctx.Return(weaponData->GetAccuracySpread());
}

static void AccuracySpreadSetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldJSValue()) return;
    uint32_t weaponHash = ctx.GetExtraInternalFieldJSValue<uint32_t>();
    auto weaponData = alt::ICore::Instance().GetWeaponData(weaponHash);

    float value;
    if(!ctx.GetValue(value)) return;

    weaponData->SetAccuracySpread(value);
}

static void RangeGetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldJSValue()) return;
    uint32_t weaponHash = ctx.GetExtraInternalFieldJSValue<uint32_t>();
    auto weaponData = alt::ICore::Instance().GetWeaponData(weaponHash);

    ctx.Return(weaponData->GetRange());
}

static void RangeSetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldJSValue()) return;
    uint32_t weaponHash = ctx.GetExtraInternalFieldJSValue<uint32_t>();
    auto weaponData = alt::ICore::Instance().GetWeaponData(weaponHash);

    float value;
    if(!ctx.GetValue(value)) return;

    weaponData->SetRange(value);
}

static void DamageGetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldJSValue()) return;
    uint32_t weaponHash = ctx.GetExtraInternalFieldJSValue<uint32_t>();
    auto weaponData = alt::ICore::Instance().GetWeaponData(weaponHash);

    ctx.Return(weaponData->GetDamage());
}

static void DamageSetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldJSValue()) return;
    uint32_t weaponHash = ctx.GetExtraInternalFieldJSValue<uint32_t>();
    auto weaponData = alt::ICore::Instance().GetWeaponData(weaponHash);

    float value;
    if(!ctx.GetValue(value)) return;

    weaponData->SetDamage(value);
}

static void ClipSizeGetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldJSValue()) return;
    uint32_t weaponHash = ctx.GetExtraInternalFieldJSValue<uint32_t>();
    auto weaponData = alt::ICore::Instance().GetWeaponData(weaponHash);

    ctx.Return(weaponData->GetClipSize());
}

static void TimeBetweenShotsGetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldJSValue()) return;
    uint32_t weaponHash = ctx.GetExtraInternalFieldJSValue<uint32_t>();
    auto weaponData = alt::ICore::Instance().GetWeaponData(weaponHash);

    ctx.Return(weaponData->GetTimeBetweenShots());
}

static void HeadshotDamageModifierGetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldJSValue()) return;
    uint32_t weaponHash = ctx.GetExtraInternalFieldJSValue<uint32_t>();
    auto weaponData = alt::ICore::Instance().GetWeaponData(weaponHash);

    ctx.Return(weaponData->GetHeadshotDamageModifier());
}

static void HeadshotDamageModifierSetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldJSValue()) return;
    uint32_t weaponHash = ctx.GetExtraInternalFieldJSValue<uint32_t>();
    auto weaponData = alt::ICore::Instance().GetWeaponData(weaponHash);

    float value;
    if(!ctx.GetValue(value)) return;

    weaponData->SetHeadshotDamageModifier(value);
}

static void PlayerDamageModifierGetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldJSValue()) return;
    uint32_t weaponHash = ctx.GetExtraInternalFieldJSValue<uint32_t>();
    auto weaponData = alt::ICore::Instance().GetWeaponData(weaponHash);

    ctx.Return(weaponData->GetPlayerDamageModifier());
}

static void PlayerDamageModifierSetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldJSValue()) return;
    uint32_t weaponHash = ctx.GetExtraInternalFieldJSValue<uint32_t>();
    auto weaponData = alt::ICore::Instance().GetWeaponData(weaponHash);

    float value;
    if(!ctx.GetValue(value)) return;

    weaponData->SetPlayerDamageModifier(value);
}

extern js::Class weaponDataClass;
extern js::ClassInstanceCache weaponDataCache(weaponDataClass);
static void AllGetter(js::PropertyContext& ctx)
{
    auto weaponDatas = alt::ICore::Instance().GetAllWeaponData();

    js::Array arr(weaponDatas.size());
    for (const auto& weaponData: weaponDatas)
        arr.Push(weaponDataCache.GetOrCreate(ctx.GetResource(), weaponData->GetNameHash()));

    ctx.Return(arr);
}

static void Get(js::FunctionContext& ctx)
{
    if(!ctx.CheckArgCount(1)) return;

    uint32_t weaponHash;
    if(!ctx.GetArgAsHash(0, weaponHash)) return;

    auto data = alt::ICore::Instance().GetWeaponData(weaponHash);
    if(!ctx.Check(data != nullptr, "No WeaponData exists with this hash")) return;

    ctx.Return(weaponDataCache.GetOrCreate(ctx.GetResource(), weaponHash));
}

// clang-format off
extern js::Class weaponDataClass("WeaponData", [](js::ClassTemplate tpl)
{
    tpl.LazyProperty("modelHash", ModelHashGetter);
    tpl.LazyProperty("nameHash", NameHashGetter);
    tpl.Property("recoilShakeAmplitude", RecoilShakeAmplitudeGetter, RecoilShakeAmplitudeSetter);
    tpl.Property("recoilAccuracyMax", RecoilAccuracyMaxGetter, RecoilAccuracyMaxSetter);
    tpl.Property("recoilAccuracyToAllowHeadshotPlayer", RecoilAccuracyToAllowHeadshotPlayerGetter, RecoilAccuracyToAllowHeadshotPlayerSetter);
    tpl.Property("recoilRecoveryRate", RecoilRecoveryRateGetter, RecoilRecoveryRateSetter);
    tpl.Property("animReloadRate", AnimReloadRateGetter, AnimReloadRateSetter);
    tpl.Property("vehicleReloadTime", VehicleReloadRateGetter, VehicleReloadTimeSetter);
    tpl.Property("lockOnRange", LockOnRangeGetter, LockOnRangeSetter);
    tpl.Property("accuracySpread", AccuracySpreadGetter, AccuracySpreadSetter);
    tpl.Property("range", RangeGetter, RangeSetter);
    tpl.Property("damage", DamageGetter, DamageSetter);
    tpl.Property("clipSize", ClipSizeGetter);
    tpl.Property("timeBetweenShots", TimeBetweenShotsGetter);
    tpl.Property("headshotDamageModifier", HeadshotDamageModifierGetter, HeadshotDamageModifierSetter);
    tpl.Property("playerDamageModifier", PlayerDamageModifierGetter, PlayerDamageModifierSetter);

    tpl.StaticProperty("all", AllGetter);

    tpl.StaticFunction("get", Get);
}, true);
