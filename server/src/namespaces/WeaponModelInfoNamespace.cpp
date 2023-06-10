#include "Namespace.h"

static void Get(js::FunctionContext& ctx)
{
    if(!ctx.CheckArgCount(1)) return;

    uint32_t model;
    if(!ctx.GetArgAsHash(0, model)) return;

    const alt::WeaponModelInfo& info = alt::ICore::Instance().GetWeaponModelByHash(model);
    if(!ctx.Check(info.hash != 0, "Invalid weapon model")) return;

    js::Object modelObj;
    modelObj.Set("hash", info.hash);
    modelObj.Set("name", info.name);
    modelObj.Set("modelHash", info.modelHash);
    modelObj.Set("ammoTypeHash", info.ammoTypeHash);
    modelObj.Set("ammoType", info.ammoType);
    modelObj.Set("ammoModelHash", info.ammoModelHash);
    modelObj.Set("defaultMaxAmmoMp", info.defaultMaxAmmoMp);
    modelObj.Set("skillAbove50MaxAmmoMp", info.skillAbove50MaxAmmoMp);
    modelObj.Set("maxSkillMaxAmmoMp", info.maxSkillMaxAmmoMp);
    modelObj.Set("bonusMaxAmmoMp", info.bonusMaxAmmoMp);

    ctx.Return(modelObj);
}

// clang-format off
extern js::Namespace weaponModelInfoNamespace("WeaponModelInfo", [](js::NamespaceTemplate& tpl) {
    tpl.StaticFunction("get", Get);
});
