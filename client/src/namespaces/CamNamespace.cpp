#include "Namespace.h"

static void PosGetter(js::PropertyContext& ctx)
{
    ctx.Return(alt::ICore::Instance().GetCamPos());
}

static void FrozenGetter(js::PropertyContext& ctx)
{
    ctx.Return(alt::ICore::Instance().IsCamFrozen());
}

static void FrozenSetter(js::PropertyContext& ctx)
{
    bool val;
    if(!ctx.GetValue(val)) return;

    alt::ICore::Instance().SetCamFrozen(val);
}

// clang-format off
extern js::Namespace camNamespace("Cam", [](js::NamespaceTemplate& tpl) {
    tpl.StaticProperty("pos", PosGetter);
    tpl.StaticProperty("frozen", FrozenGetter, FrozenSetter);
});
