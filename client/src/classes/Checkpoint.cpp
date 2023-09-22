#include "Class.h"

// clang-format off
extern js::Class sharedCheckpointClass;
extern js::Class checkpointClass("Checkpoint", &sharedCheckpointClass, nullptr, [](js::ClassTemplate& tpl)
{
    tpl.BindToType(alt::IBaseObject::Type::CHECKPOINT);

    tpl.Property<&alt::ICheckpoint::GetGameID>("scriptID");
    tpl.Property<&alt::ICheckpoint::IsStreamedIn>("isStreamedIn");

    tpl.GetByID<alt::IBaseObject::Type::CHECKPOINT>();
    tpl.GetByRemoteID<alt::IBaseObject::Type::CHECKPOINT>();
});
