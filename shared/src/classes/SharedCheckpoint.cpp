#include "Class.h"

// clang-format off
extern js::Class colShapeClass;
extern js::Class sharedCheckpointClass("Checkpoint", &colShapeClass, nullptr, [](js::ClassTemplate& tpl)
{
    tpl.Property<&alt::ICheckpoint::GetCheckpointType, &alt::ICheckpoint::SetCheckpointType>("checkpointType");
    tpl.Property<&alt::ICheckpoint::GetRadius, &alt::ICheckpoint::SetRadius>("radius");
    tpl.Property<&alt::ICheckpoint::GetHeight, &alt::ICheckpoint::SetHeight>("height");
    tpl.Property<&alt::ICheckpoint::GetColor, &alt::ICheckpoint::SetColor>("color");
    tpl.Property<&alt::ICheckpoint::GetIconColor, &alt::ICheckpoint::SetIconColor>("iconColor");
    tpl.Property<&alt::ICheckpoint::GetNextPosition, &alt::ICheckpoint::SetNextPosition>("nextPos");
    tpl.Property<&alt::ICheckpoint::GetStreamingDistance>("streamingDistance");
    tpl.Property<&alt::ICheckpoint::IsVisible, &alt::ICheckpoint::SetVisible>("visible");

    tpl.Method<&alt::ICheckpoint::IsEntityIn>("entityIn");
    tpl.Method<&alt::ICheckpoint::IsEntityIdIn>("entityIdIn");
    tpl.Method<&alt::ICheckpoint::IsPointIn>("pointIn");
});
