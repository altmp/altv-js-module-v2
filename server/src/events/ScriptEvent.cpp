#include "Event.h"

// clang-format off
static js::Event colshapeEvent(alt::CEvent::Type::COLSHAPE_EVENT, [](const alt::CEvent* ev, js::Event::EventArgs& args)
{
    auto e = static_cast<const alt::CColShapeEvent*>(ev);

    args.Set("entity", e->GetEntity());
    args.Set("colShape", e->GetTarget());
    args.Set("state", e->GetState());
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

    args.SetMethod("setDamageValue", SetDamageValue);
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

static js::Event fireEvent(alt::CEvent::Type::FIRE_EVENT, [](const alt::CEvent* ev, js::Event::EventArgs& args)
{
    auto e = static_cast<const alt::CFireEvent*>(ev);

    args.Set("player", e->GetSource());
    const std::vector<alt::CFireEvent::FireInfo>& fires = e->GetFires();
    js::Array firesArr(fires.size());
    for (auto& fire : fires)
    {
        js::Object fireObj;
        fireObj.Set("pos", fire.position);
        fireObj.Set("weaponHash", fire.weaponHash);
        firesArr.Push(fireObj);
    }
    args.Set("fires", firesArr);
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
