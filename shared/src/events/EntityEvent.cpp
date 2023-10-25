#include "Event.h"

// clang-format off
static js::Event baseObjectCreateEvent(alt::CEvent::Type::CREATE_BASE_OBJECT_EVENT, [](const alt::CEvent* ev, js::Event::EventArgs& args)
{
    auto e = static_cast<const alt::CCreateBaseObjectEvent*>(ev);
    args.Set("object", e->GetObject());
});

static js::Event baseObjectRemoveEvent(alt::CEvent::Type::REMOVE_BASE_OBJECT_EVENT, [](const alt::CEvent* ev, js::Event::EventArgs& args)
{
    auto e = static_cast<const alt::CRemoveBaseObjectEvent*>(ev);
    args.Set("object", e->GetObject());
});

static js::Event netOwnerChangeEvent(alt::CEvent::Type::NETOWNER_CHANGE, [](const alt::CEvent* ev, js::Event::EventArgs& args)
{
    auto e = static_cast<const alt::CNetOwnerChangeEvent*>(ev);

    args.Set("entity", e->GetTarget());
    args.Set("oldOwner", e->GetOldOwner());
    args.Set("newOwner", e->GetNewOwner());
});

static void SetDamageValue(js::FunctionContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldValue()) return;
    alt::CWeaponDamageEvent* ev = ctx.GetExtraInternalFieldValue<alt::CWeaponDamageEvent>();

    uint32_t value;
    if(!ctx.GetArg(0, value)) return;

    ev->SetDamageValue(value);
}
static js::Event weaponDamageEvent(alt::CEvent::Type::WEAPON_DAMAGE_EVENT, [](const alt::CEvent* ev, js::Event::EventArgs& args)
{
    auto e = static_cast<const alt::CWeaponDamageEvent*>(ev);

    args.Set("source", e->GetSource());
    args.Set("target", e->GetTarget());
    args.Set("weaponHash", e->GetWeaponHash());
    args.Set("damage", e->GetDamageValue());
    args.Set("offset", e->GetShotOffset());
    args.Set("bodyPart", e->GetBodyPart());

    args.SetBoundMethod("setDamageValue", SetDamageValue);
});
