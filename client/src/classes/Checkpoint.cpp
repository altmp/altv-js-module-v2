#include "Class.h"

static void GetByScriptID(js::FunctionContext& ctx)
{
    if(!ctx.CheckArgCount(1)) return;

    uint32_t scriptId;
    if(!ctx.GetArg(0, scriptId)) return;

    ctx.Return(alt::ICore::Instance().GetCheckpointByGameID(scriptId));
}

// clang-format off
extern js::Class sharedCheckpointClass;
extern js::Class checkpointClass("Checkpoint", &sharedCheckpointClass, nullptr, [](js::ClassTemplate& tpl)
{
    tpl.BindToType(alt::IBaseObject::Type::CHECKPOINT);

    tpl.Property<&alt::ICheckpoint::GetGameID>("scriptID");
    tpl.Property<&alt::ICheckpoint::IsStreamedIn>("isStreamedIn");

    tpl.GetByID<alt::IBaseObject::Type::CHECKPOINT>();
    tpl.GetByRemoteID<alt::IBaseObject::Type::CHECKPOINT>();

    tpl.StaticFunction("getByScriptID", &GetByScriptID);
});
