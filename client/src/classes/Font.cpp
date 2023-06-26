#include "Class.h"
#include "cpp-sdk/ICore.h"
#include "interfaces/IResource.h"

static void Register(js::FunctionContext& ctx)
{
    if(!ctx.CheckArgCount(1)) return;

    std::string path;
    if(!ctx.GetArg(0, path)) return;

    js::IResource* resource = ctx.GetResource();
    js::SourceLocation origin = js::SourceLocation::GetCurrent(resource);

    alt::IBaseObject* font = alt::ICore::Instance().RegisterFont(resource->GetResource(), path, origin.file);

    if(!font) return;

    ctx.Return(font);
}

// clang-format off
extern js::Class baseObjectClass;
extern js::Class fontClass("Font", &baseObjectClass, nullptr, [](js::ClassTemplate& tpl)
{
    tpl.BindToType(alt::IBaseObject::Type::FONT);

    tpl.StaticFunction("register", Register);
});
