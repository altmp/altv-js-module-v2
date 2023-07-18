#include "Namespace.h"
#include "interfaces/IResource.h"

static void VisibleGetter(js::PropertyContext& ctx)
{
    ctx.Return(ctx.GetResource()->GetResource()->CursorVisible());
}

static void VisibleSetter(js::PropertyContext& ctx)
{
    bool val;
    if(!ctx.GetValue(val)) return;

    ctx.Return(ctx.GetResource()->GetResource()->ToggleCursor(val));
}

template<bool Normalized>
static void PosGetter(js::PropertyContext& ctx)
{
    ctx.Return(alt::ICore::Instance().GetCursorPosition(Normalized));
}

template<bool Normalized>
static void PosSetter(js::PropertyContext& ctx)
{
    alt::Vector2f pos;
    if(!ctx.GetValue(pos)) return;

    alt::ICore::Instance().SetCursorPosition(pos, Normalized);
}

// clang-format off
extern js::Namespace cursorNamespace("Cursor", [](js::NamespaceTemplate& tpl) {
    tpl.StaticProperty("visible", VisibleGetter, VisibleSetter);
    tpl.StaticProperty("pos", PosGetter<false>, PosSetter<false>);
    tpl.StaticProperty("posNormalized", PosGetter<true>, PosSetter<true>);
});
