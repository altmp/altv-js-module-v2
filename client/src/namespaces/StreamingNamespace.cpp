#include "Namespace.h"

static void DoesTextureExistInArchetype(js::FunctionContext& ctx)
{
    if(!ctx.CheckArgCount(2)) return;

    uint32_t modelHash;
    if(!ctx.GetArgAsHash(0, modelHash)) return;

    std::string textureName;
    if(!ctx.GetArg(1, textureName)) return;

    ctx.Return(alt::ICore::Instance().GetTextureFromDrawable(modelHash, textureName) != nullptr);
}

static void RequestIPL(js::FunctionContext& ctx)
{
    if(!ctx.CheckArgCount(1)) return;

    std::string ipl;
    if(!ctx.GetArg(0, ipl)) return;

    alt::ICore::Instance().RequestIPL(ipl);
}

static void RemoveIPL(js::FunctionContext& ctx)
{
    if(!ctx.CheckArgCount(1)) return;

    std::string ipl;
    if(!ctx.GetArg(0, ipl)) return;

    alt::ICore::Instance().RemoveIPL(ipl);
}

static void LoadModel(js::FunctionContext& ctx)
{
    if(!ctx.CheckArgCount(1, 2)) return;

    uint32_t model;
    if(!ctx.GetArgAsHash(0, model)) return;

    bool async = ctx.GetArg<bool>(1, false);

    if(!async) alt::ICore::Instance().LoadModel(model);
    else
        alt::ICore::Instance().LoadModelAsync(model);
}

static void LoadYtyp(js::FunctionContext& ctx)
{
    if(!ctx.CheckArgCount(1)) return;

    std::string ytyp;
    if(!ctx.GetArg(0, ytyp)) return;

    alt::ICore::Instance().LoadYtyp(ytyp);
}

static void UnloadYtyp(js::FunctionContext& ctx)
{
    if(!ctx.CheckArgCount(1)) return;

    std::string ytyp;
    if(!ctx.GetArg(0, ytyp)) return;

    alt::ICore::Instance().UnloadYtyp(ytyp);
}

static void LoadDefaultIpls(js::FunctionContext& ctx)
{
    alt::ICore::Instance().LoadDefaultIpls();
}

// clang-format off
extern js::Namespace streamingNamespace("Streaming", [](js::NamespaceTemplate& tpl) {
    tpl.StaticFunction("doesTextureExistInArchetype", DoesTextureExistInArchetype);
    tpl.StaticFunction("requestIpl", RequestIPL);
    tpl.StaticFunction("removeIpl", RemoveIPL);
    tpl.StaticFunction("loadDefaultIpls", LoadDefaultIpls);
    tpl.StaticFunction("loadModel", LoadModel);
    tpl.StaticFunction("loadYtyp", LoadYtyp);
    tpl.StaticFunction("unloadYtyp", UnloadYtyp);
});
