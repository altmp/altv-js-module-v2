#include "Class.h"

static void LocalGetter(js::LazyPropertyContext& ctx)
{
    ctx.Return(alt::ICore::Instance().GetLocalPlayer());
}

// clang-format off
extern js::Class sharedPlayerClass;
extern js::Class playerClass("Player", &sharedPlayerClass, nullptr, [](js::ClassTemplate& tpl)
{
    tpl.BindToType(alt::IBaseObject::Type::PLAYER);

    tpl.StaticLazyProperty("local", LocalGetter);
});
