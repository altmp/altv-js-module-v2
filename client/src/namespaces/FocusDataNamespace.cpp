#include "Namespace.h"

static void FocusOverridenGetter(js::PropertyContext& ctx)
{
    ctx.Return(alt::ICore::Instance().IsFocusOverriden());
}

static void FocusOverridePosGetter(js::PropertyContext& ctx)
{
    ctx.Return(alt::ICore::Instance().GetFocusOverridePos());
}

static void FocusOverridePosSetter(js::PropertyContext& ctx)
{
    alt::Position pos;
    if(!ctx.GetValue(pos)) return;

    alt::ICore::Instance().OverrideFocusPosition(pos);
}

static void FocusOverrideEntityGetter(js::PropertyContext& ctx)
{
    ctx.Return(alt::ICore::Instance().GetFocusOverrideEntity());
}

static void FocusOverrideEntitySetter(js::PropertyContext& ctx)
{
    alt::IEntity* entity;
    if(!ctx.GetValue(entity)) return;

    alt::ICore::Instance().OverrideFocusEntity(entity);
}

static void ClearFocusOverride(js::FunctionContext& ctx)
{
    alt::ICore::Instance().ClearFocusOverride();
}

// clang-format off
extern js::Namespace focusDataNamespace("FocusData", [](js::NamespaceTemplate& tpl) {
    tpl.StaticProperty("isFocusOverriden", FocusOverridenGetter);
    tpl.StaticProperty("focusOverridePos", FocusOverridePosGetter, FocusOverridePosSetter);
    tpl.StaticProperty("focusOverrideEntity", FocusOverrideEntityGetter, FocusOverrideEntitySetter);

    tpl.StaticFunction("clearFocusOverride", ClearFocusOverride);
});
