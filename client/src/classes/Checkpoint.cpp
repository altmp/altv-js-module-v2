#include "Class.h"

// clang-format off
extern js::Class worldObjectClass;
extern js::Class checkpointClass("Checkpoint", &worldObjectClass, nullptr, [](js::ClassTemplate& tpl)
{
    tpl.BindToType(alt::IBaseObject::Type::CHECKPOINT);

    tpl.Property<&alt::ICheckpoint::GetGameID>("scriptID");
    tpl.Property<&alt::ICheckpoint::GetCheckpointType, &alt::ICheckpoint::SetCheckpointType>("checkpointType");
    tpl.Property<&alt::ICheckpoint::GetRadius, &alt::ICheckpoint::SetRadius>("radius");
    tpl.Property<&alt::ICheckpoint::GetHeight, &alt::ICheckpoint::SetHeight>("height");
    tpl.Property<&alt::ICheckpoint::GetColor, &alt::ICheckpoint::SetColor>("color");
    tpl.Property<&alt::ICheckpoint::GetNextPosition, &alt::ICheckpoint::SetNextPosition>("nextPos");
    tpl.Property<&alt::ICheckpoint::GetStreamingDistance>("streamingDistance");
    tpl.Property<&alt::ICheckpoint::IsStreamedIn>("isStreamedIn");
    tpl.Property<&alt::ICheckpoint::IsVisible, &alt::ICheckpoint::SetVisible>("visible");

    tpl.Method<&alt::ICheckpoint::IsEntityIn>("isEntityIn");
    tpl.Method<&alt::ICheckpoint::IsEntityIdIn>("isEntityIdIn");
    tpl.Method<&alt::ICheckpoint::IsPointIn>("isPointIn");

    tpl.GetByID<alt::IBaseObject::Type::CHECKPOINT>();
});
