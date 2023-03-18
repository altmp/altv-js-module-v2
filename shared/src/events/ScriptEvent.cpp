#include "Event.h"

// clang-format off
static js::Event clientScriptEvent(alt::CEvent::Type::CLIENT_SCRIPT_EVENT, [](const alt::CEvent* ev, js::Event::EventArgs& args)
{
    auto e = static_cast<const alt::CClientScriptEvent*>(ev);
    args.Set("eventName", e->GetName());

    const alt::MValueArgs& eventArgs = e->GetArgs();
    js::Array argsArray(eventArgs.GetSize());
    js::MValueArgsToJS(eventArgs, argsArray);
    args.Set("args", argsArray.Get());
});

static js::Event serverScriptEvent(alt::CEvent::Type::SERVER_SCRIPT_EVENT, [](const alt::CEvent* ev, js::Event::EventArgs& args)
{
    auto e = static_cast<const alt::CServerScriptEvent*>(ev);
    args.Set("eventName", e->GetName());

    const alt::MValueArgs& eventArgs = e->GetArgs();
    js::Array argsArray(eventArgs.GetSize());
    js::MValueArgsToJS(eventArgs, argsArray);
    args.Set("args", argsArray.Get());
});

// TODO
//? ColShape, CollisionShape ?
static js::Event colshapeEvent(alt::CEvent::Type::COLSHAPE_EVENT, [](const alt::CEvent* ev, js::Event::EventArgs& args)
{
    // 
});

static js::Event weaponDamageEvent(alt::CEvent::Type::WEAPON_DAMAGE_EVENT, [](const alt::CEvent* ev, js::Event::EventArgs& args)
{
    auto e = static_cast<const alt::CWeaponDamageEvent*>(ev);

    args.Set("source", e->GetSource());
    args.Set("target", e->GetTarget());
    args.Set("weaponHash", e->GetWeaponHash());
    args.Set("damage", e->GetDamageValue());
    args.Set("offset", e->GetShotOffset());
    args.Set("bodyPart", e->GetBodyPart());
});

static js::Event explosionEvent(alt::CEvent::Type::EXPLOSION_EVENT, [](const alt::CEvent* ev, js::Event::EventArgs& args)
{
    auto e = static_cast<const alt::CExplosionEvent*>(ev);

    args.Set("source", e->GetSource());
    args.Set("type", e->GetExplosionType());
    args.Set("pos", e->GetPosition());
    args.Set("fx", e->GetExplosionFX());
    args.Set("target", e->GetTarget());
});

// TODO
static js::Event fireEvent(alt::CEvent::Type::FIRE_EVENT, [](const alt::CEvent* ev, js::Event::EventArgs& args)
{
    // 
});

static js::Event startProjectileEvent(alt::CEvent::Type::START_PROJECTILE_EVENT, [](const alt::CEvent* ev, js::Event::EventArgs& args)
{
    auto e = static_cast<const alt::CStartProjectileEvent*>(ev);

    args.Set("player", e->GetSource());
    args.Set("pos", e->GetStartPosition());
    args.Set("dir", e->GetDirection());
    args.Set("ammoHash", e->GetAmmoHash());
    args.Set("weaponHash", e->GetWeaponHash());
});

static js::Event syncedMetaChangeEvent(alt::CEvent::Type::SYNCED_META_CHANGE, [](const alt::CEvent* ev, js::Event::EventArgs& args)
{
    auto e = static_cast<const alt::CSyncedMetaDataChangeEvent*>(ev);

    args.Set("entity", e->GetTarget());
    args.Set("key", e->GetKey());
    args.Set("oldValue", e->GetOldVal());
    args.Set("newValue", e->GetVal());
});

static js::Event streamSyncedMetaChangeEvent(alt::CEvent::Type::STREAM_SYNCED_META_CHANGE, [](const alt::CEvent* ev, js::Event::EventArgs& args)
{
    auto e = static_cast<const alt::CStreamSyncedMetaDataChangeEvent*>(ev);

    args.Set("entity", e->GetTarget());
    args.Set("key", e->GetKey());
    args.Set("oldValue", e->GetOldVal());
    args.Set("newValue", e->GetVal());
});

static js::Event globalMetaChangeEvent(alt::CEvent::Type::GLOBAL_META_CHANGE, [](const alt::CEvent* ev, js::Event::EventArgs& args)
{
    auto e = static_cast<const alt::CGlobalMetaDataChangeEvent*>(ev);

    args.Set("key", e->GetKey());
    args.Set("oldValue", e->GetOldVal());
    args.Set("newValue", e->GetVal());
});

static js::Event globalSyncedMetaChangeEvent(alt::CEvent::Type::GLOBAL_SYNCED_META_CHANGE, [](const alt::CEvent* ev, js::Event::EventArgs& args)
{
    auto e = static_cast<const alt::CGlobalMetaDataChangeEvent*>(ev);

    args.Set("key", e->GetKey());
    args.Set("oldValue", e->GetOldVal());
    args.Set("newValue", e->GetVal());
});