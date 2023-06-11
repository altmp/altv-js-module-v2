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

static js::Event entityHitEntityEvent(alt::CEvent::Type::ENTITY_HIT_ENTITY, [](const alt::CEvent* ev, js::Event::EventArgs& args)
{
    auto e = static_cast<const alt::CEntityHitEntityEvent*>(ev);

    args.Set("entity", e->GetTarget());
    args.Set("damager", e->GetDamager());
    args.Set("weapon", e->GetWeapon());
});
