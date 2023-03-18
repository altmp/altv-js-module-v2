#include "Event.h"

// clang-format off
static js::Event vehicleDestroyEvent(alt::CEvent::Type::VEHICLE_DESTROY, [](const alt::CEvent* ev, js::Event::EventArgs& args)
{
    auto e = static_cast<const alt::CVehicleDestroyEvent*>(ev);

    args.Set("vehicle", e->GetTarget());
});

static js::Event vehicleAttachEvent(alt::CEvent::Type::VEHICLE_ATTACH, [](const alt::CEvent* ev, js::Event::EventArgs& args)
{
    auto e = static_cast<const alt::CVehicleAttachEvent*>(ev);

    args.Set("vehicle", e->GetTarget());
    args.Set("attachedVehicle", e->GetAttached());
});

static js::Event vehicleDetachEvent(alt::CEvent::Type::VEHICLE_DETACH, [](const alt::CEvent* ev, js::Event::EventArgs& args)
{
    auto e = static_cast<const alt::CVehicleDetachEvent*>(ev);

    args.Set("vehicle", e->GetTarget());
    args.Set("detachedVehicle", e->GetDetached());
});

//? Does it belong here ?
static js::Event netOwnerChangeEvent(alt::CEvent::Type::NETOWNER_CHANGE, [](const alt::CEvent* ev, js::Event::EventArgs& args)
{
    auto e = static_cast<const alt::CNetOwnerChangeEvent*>(ev);

    args.Set("entity", e->GetTarget());
    args.Set("oldNetOwner", e->GetOldOwner());
    args.Set("newNetOwner", e->GetNewOwner());
});

static js::Event vehicleDamageEvent(alt::CEvent::Type::VEHICLE_DAMAGE, [](const alt::CEvent* ev, js::Event::EventArgs& args)
{
    auto e = static_cast<const alt::CVehicleDamageEvent*>(ev);

    args.Set("vehicle", e->GetTarget());
    args.Set("attacker", e->GetDamager());
    args.Set("bodyHealthDamage", e->GetBodyHealthDamage());
    args.Set("additionalBodyHealthDamage", e->GetBodyAdditionalHealthDamage());
    args.Set("engineHealthDamage", e->GetEngineHealthDamage());
    args.Set("petrolTankDamage", e->GetPetrolTankHealthDamage());
    args.Set("weaponHash", e->GetDamagedWith());
});