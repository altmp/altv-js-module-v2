#include "Class.h"
#include "cpp-sdk/ICore.h"

static void HasWeaponComponent(js::FunctionContext& ctx)
{
    if(!ctx.CheckThis()) return;
    if(!ctx.CheckArgCount(2)) return;
    alt::IPlayer* player = ctx.GetThisObject<alt::IPlayer>();

    uint32_t weapon;
    if(!ctx.GetArgAsHash(0, weapon)) return;

    uint32_t component;
    if(!ctx.GetArgAsHash(1, component)) return;

    ctx.Return(player->HasWeaponComponent(weapon, component));
}

static void GetWeaponTintIndex(js::FunctionContext& ctx)
{
    if(!ctx.CheckThis()) return;
    if(!ctx.CheckArgCount(1)) return;
    alt::IPlayer* player = ctx.GetThisObject<alt::IPlayer>();

    uint32_t weapon;
    if(!ctx.GetArgAsHash(0, weapon)) return;

    ctx.Return(player->GetWeaponTintIndex(weapon));
}

// clang-format off
extern js::Class entityClass;
extern js::Class sharedPlayerClass("SharedPlayer", &entityClass, nullptr, [](js::ClassTemplate& tpl)
{
    tpl.LazyProperty<&alt::IPlayer::GetName>("name");

    tpl.Property<&alt::IPlayer::GetHealth>("health");
    tpl.Property<&alt::IPlayer::GetMaxHealth>("maxHealth");
    tpl.Property<&alt::IPlayer::GetCurrentWeaponComponents>("currentWeaponComponents");
    tpl.Property<&alt::IPlayer::GetCurrentWeaponTintIndex>("currentWeaponTintIndex");
    tpl.Property<&alt::IPlayer::GetCurrentWeapon>("currentWeapon");
    tpl.Property<&alt::IPlayer::IsDead>("dead");
    tpl.Property<&alt::IPlayer::IsJumping>("jumping");
    tpl.Property<&alt::IPlayer::IsInRagdoll>("inRagdoll");
    tpl.Property<&alt::IPlayer::IsAiming>("aiming");
    tpl.Property<&alt::IPlayer::IsShooting>("shooting");
    tpl.Property<&alt::IPlayer::IsReloading>("reloading");
    tpl.Property<&alt::IPlayer::IsEnteringVehicle>("enteringVehicle");
    tpl.Property<&alt::IPlayer::IsLeavingVehicle>("leavingVehicle");
    tpl.Property<&alt::IPlayer::IsOnLadder>("onLadder");
    tpl.Property<&alt::IPlayer::IsInMelee>("inMelee");
    tpl.Property<&alt::IPlayer::IsInCover>("inCover");
    tpl.Property<&alt::IPlayer::IsParachuting>("parachuting");
    tpl.Property<&alt::IPlayer::GetArmour>("armour");
    tpl.Property<&alt::IPlayer::GetMaxArmour>("maxArmour");
    tpl.Property<&alt::IPlayer::GetMoveSpeed>("moveSpeed");
    tpl.Property<&alt::IPlayer::GetAimPos>("aimPos");
    tpl.Property<&alt::IPlayer::GetHeadRotation>("headRotation");
    tpl.Property<&alt::IPlayer::IsInVehicle>("inVehicle");
    tpl.Property<&alt::IPlayer::GetVehicle>("vehicle");
    tpl.Property<&alt::IPlayer::GetSeat>("seat");
    tpl.Property<&alt::IPlayer::GetEntityAimingAt>("entityAimingAt");
    tpl.Property<&alt::IPlayer::GetEntityAimOffset>("entityAimOffset");
    tpl.Property<&alt::IPlayer::IsFlashlightActive>("flashlightActive");
    tpl.Property<&alt::IPlayer::IsSuperJumpEnabled>("superJumpEnabled");
    tpl.Property<&alt::IPlayer::IsCrouching>("crouching");
    tpl.Property<&alt::IPlayer::IsStealthy>("stealthy");
    tpl.Property<&alt::IPlayer::GetCurrentAnimationDict>("currentAnimationDict");
    tpl.Property<&alt::IPlayer::GetCurrentAnimationName>("currentAnimationName");
    tpl.Property<&alt::IPlayer::IsSpawned>("spawned");
    tpl.Property<&alt::IPlayer::GetForwardSpeed>("forwardSpeed");
    tpl.Property<&alt::IPlayer::GetStrafeSpeed>("strafeSpeed");

    tpl.Method("getWeaponTintIndex", GetWeaponTintIndex);
    tpl.Method("hasWeaponComponent", HasWeaponComponent);
});
