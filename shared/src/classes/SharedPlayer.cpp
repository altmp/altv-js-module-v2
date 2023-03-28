#include "Class.h"
#include "cpp-sdk/ICore.h"

static void HasWeaponComponent(js::FunctionContext& ctx)
{
    if(!ctx.CheckThis()) return;
    if(!ctx.CheckArgCount(1)) return;
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
extern js::Class sharedPlayerClass("Player", nullptr, [](js::ClassTemplate& tpl)
{
    tpl.LazyProperty<alt::IPlayer, &alt::IPlayer::GetName>("name");

    tpl.Property<alt::IPlayer, &alt::IPlayer::GetHealth>("health");
    tpl.Property<alt::IPlayer, &alt::IPlayer::GetMaxHealth>("maxHealth");
    tpl.Property<alt::IPlayer, &alt::IPlayer::GetCurrentWeaponComponents>("currentWeaponComponents");
    tpl.Property<alt::IPlayer, &alt::IPlayer::GetCurrentWeaponTintIndex>("currentWeaponTintIndex");
    tpl.Property<alt::IPlayer, &alt::IPlayer::GetCurrentWeapon>("currentWeapon");
    tpl.Property<alt::IPlayer, &alt::IPlayer::IsDead>("isDead");
    tpl.Property<alt::IPlayer, &alt::IPlayer::IsJumping>("isJumping");
    tpl.Property<alt::IPlayer, &alt::IPlayer::IsAiming>("isAiming");
    tpl.Property<alt::IPlayer, &alt::IPlayer::IsShooting>("isShooting");
    tpl.Property<alt::IPlayer, &alt::IPlayer::IsReloading>("isReloading");
    tpl.Property<alt::IPlayer, &alt::IPlayer::GetArmour>("armour");
    tpl.Property<alt::IPlayer, &alt::IPlayer::GetMaxArmour>("maxArmour");
    tpl.Property<alt::IPlayer, &alt::IPlayer::GetMoveSpeed>("moveSpeed");
    tpl.Property<alt::IPlayer, &alt::IPlayer::GetAimPos>("aimPos");
    tpl.Property<alt::IPlayer, &alt::IPlayer::GetHeadRotation>("headRotation");
    tpl.Property<alt::IPlayer, &alt::IPlayer::IsInVehicle>("isInVehicle");
    tpl.Property<alt::IPlayer, &alt::IPlayer::GetVehicle>("vehicle");
    tpl.Property<alt::IPlayer, &alt::IPlayer::GetSeat>("seat");
    tpl.Property<alt::IPlayer, &alt::IPlayer::GetEntityAimingAt>("entityAimingAt");
    tpl.Property<alt::IPlayer, &alt::IPlayer::GetEntityAimOffset>("entityAimOffset");
    tpl.Property<alt::IPlayer, &alt::IPlayer::IsFlashlightActive>("isFlashlightActive");
    tpl.Property<alt::IPlayer, &alt::IPlayer::IsSuperJumpEnabled>("isSuperJumpEnabled");
    tpl.Property<alt::IPlayer, &alt::IPlayer::IsCrouching>("isCrouching");
    tpl.Property<alt::IPlayer, &alt::IPlayer::IsStealthy>("isStealthy");
    tpl.Property<alt::IPlayer, &alt::IPlayer::GetCurrentAnimationDict>("currentAnimationDict");
    tpl.Property<alt::IPlayer, &alt::IPlayer::GetCurrentAnimationName>("currentAnimationName");
    tpl.Property<alt::IPlayer, &alt::IPlayer::IsSpawned>("isSpawned");
    tpl.Property<alt::IPlayer, &alt::IPlayer::GetForwardSpeed>("forwardSpeed");
    tpl.Property<alt::IPlayer, &alt::IPlayer::GetStrafeSpeed>("strafeSpeed");

    tpl.Method("getWeaponTintIndex", GetWeaponTintIndex);
    tpl.Method("hasWeaponComponent", HasWeaponComponent);

});
