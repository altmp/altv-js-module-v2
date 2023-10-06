#include "Class.h"

static void GetByScriptID(js::FunctionContext& ctx)
{
    if(!ctx.CheckArgCount(1)) return;

    uint32_t scriptId;
    if(!ctx.GetArg(0, scriptId)) return;

    ctx.Return(alt::ICore::Instance().GetBlipByGameID(scriptId));
}

// clang-format off
extern js::Class sharedBlipClass;
extern js::Class blipClass("Blip", &sharedBlipClass, nullptr, [](js::ClassTemplate& tpl)
{
    tpl.BindToType(alt::IBaseObject::Type::BLIP);

    tpl.Property<&alt::IBlip::GetGameID>("scriptID");
    tpl.Property<&alt::IBlip::IsStreamedIn>("isStreamedIn");

    tpl.GetByID<alt::IBaseObject::Type::BLIP>();
    tpl.GetByRemoteID<alt::IBaseObject::Type::BLIP>();

    tpl.StaticFunction("getByScriptID", &GetByScriptID);
});
