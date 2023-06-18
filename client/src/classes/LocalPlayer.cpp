#include "Class.h"

static void WeaponsGetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckThis()) return;
    alt::ILocalPlayer* player = ctx.GetThisObject<alt::ILocalPlayer>();

    std::vector<alt::Weapon> weapons = player->GetWeapons();
    js::Array arr(weapons.size());
    for(auto weapon : weapons)
    {
        js::Object obj;
        obj.Set("hash", weapon.hash);
        obj.Set("tintIndex", weapon.tintIndex);
        js::Array components(weapon.components.size());
        for(auto component : weapon.components) components.Push(component);
        obj.Set("components", components);
        arr.Push(obj);
    }

    ctx.Return(arr);
}

static void GetWeaponAmmo(js::FunctionContext& ctx)
{
    if(!ctx.CheckThis()) return;
    if(!ctx.CheckArgCount(1)) return;
    alt::ILocalPlayer* player = ctx.GetThisObject<alt::ILocalPlayer>();

    uint32_t weaponHash;
    if(!ctx.GetArgAsHash(0, weaponHash)) return;

    ctx.Return(player->GetWeaponAmmo(weaponHash));
}

static void HasWeapon(js::FunctionContext& ctx)
{
    if(!ctx.CheckThis()) return;
    if(!ctx.CheckArgCount(1)) return;
    alt::ILocalPlayer* player = ctx.GetThisObject<alt::ILocalPlayer>();

    uint32_t weaponHash;
    if(!ctx.GetArgAsHash(0, weaponHash)) return;

    ctx.Return(player->HasWeapon(weaponHash));
}

static void GetWeaponComponents(js::FunctionContext& ctx)
{
    if(!ctx.CheckThis()) return;
    if(!ctx.CheckArgCount(1)) return;
    alt::ILocalPlayer* player = ctx.GetThisObject<alt::ILocalPlayer>();

    uint32_t weaponHash;
    if(!ctx.GetArgAsHash(0, weaponHash)) return;

    ctx.Return(player->GetWeaponComponents(weaponHash));
}

// clang-format off
extern js::Class playerClass;
extern js::Class localPlayerClass("LocalPlayer", &playerClass, nullptr, [](js::ClassTemplate& tpl)
{
    tpl.BindToType(alt::IBaseObject::Type::LOCAL_PLAYER);

    tpl.Property<&alt::ILocalPlayer::GetCurrentAmmo>("currentAmmo");
    tpl.Property<&alt::ILocalPlayer::GetStamina, &alt::ILocalPlayer::SetStamina>("stamina");
    tpl.Property<&alt::ILocalPlayer::GetMaxStamina, &alt::ILocalPlayer::SetMaxStamina>("maxStamina");
    //tpl.Property("currentWeaponData", GetCurrentWeaponData);
    tpl.Property("weapons", WeaponsGetter);

    tpl.Method("getWeaponAmmo", GetWeaponAmmo);
    tpl.Method("hasWeapon", HasWeapon);
    tpl.Method("getWeaponComponents", GetWeaponComponents);
});
