#include "Namespace.h"

static void Get(js::FunctionContext& ctx)
{
    if(!ctx.CheckArgCount(1)) return;

    uint32_t model;
    if(!ctx.GetArgAsHash(0, model)) return;

    const alt::PedModelInfo& info = alt::ICore::Instance().GetPedModelByHash(model);
    if(!ctx.Check(info.hash != 0, "Invalid ped model")) return;

    js::Object modelObj;
    modelObj.Set("hash", info.hash);
    modelObj.Set("name", info.name);
    modelObj.Set("type", info.type);
    modelObj.Set("dlcName", info.dlcName);
    modelObj.Set("defaultUnarmedWeapon", info.defaultUnarmedWeapon);
    modelObj.Set("movementClipSet", info.movementClipSet);
    js::Array bones;
    for(const alt::BoneInfo& bone : info.bones)
    {
        js::Object boneObj;
        boneObj.Set("id", bone.id);
        boneObj.Set("index", bone.index);
        boneObj.Set("name", bone.name);
        bones.Push(boneObj);
    }
    modelObj.Set("bones", bones);

    ctx.Return(modelObj);
}

// clang-format off
extern js::Namespace pedModelInfoNamespace("PedModelInfo", [](js::NamespaceTemplate& tpl) {
    tpl.StaticFunction("get", Get);
});
