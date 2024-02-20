#include "Class.h"
#include "cpp-sdk/ICore.h"

// clang-format off
extern js::Class worldObjectClass;
extern js::Class sharedMarkerClass("SharedMarker", &worldObjectClass, nullptr, [](js::ClassTemplate& tpl)
{
    tpl.Property<&alt::IMarker::IsGlobal>("global");
    tpl.Property<&alt::IMarker::GetTarget>("target");

    tpl.Property<&alt::IMarker::GetColor, &alt::IMarker::SetColor>("color");
    tpl.Property<&alt::IMarker::IsVisible, &alt::IMarker::SetVisible>("visible");
    tpl.Property<&alt::IMarker::GetMarkerType, &alt::IMarker::SetMarkerType>("markerType");
    tpl.Property<&alt::IMarker::GetScale, &alt::IMarker::SetScale>("scale");
    tpl.Property<&alt::IMarker::GetRotation, &alt::IMarker::SetRotation>("rot");
    tpl.Property<&alt::IMarker::GetDirection, &alt::IMarker::SetDirection>("direction");
    tpl.Property<&alt::IMarker::IsFaceCamera, &alt::IMarker::SetFaceCamera>("faceCamera");
    tpl.Property<&alt::IMarker::IsRotating, &alt::IMarker::SetRotating>("rotating");
    tpl.Property<&alt::IMarker::IsBobUpDown, &alt::IMarker::SetBobUpDown>("bobUpDown");

    tpl.Property<&alt::IMarker::GetStreamingDistance>("streamingDistance");
});
