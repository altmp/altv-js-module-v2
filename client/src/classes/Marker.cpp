#include "Class.h"

// clang-format off
extern js::Class sharedMarkerClass;
extern js::Class markerClass("Marker", &sharedMarkerClass, nullptr, [](js::ClassTemplate& tpl)
{
    tpl.BindToType(alt::IBaseObject::Type::MARKER);

    tpl.Property<&alt::IMarker::IsStreamedIn>("isStreamedIn");

    tpl.GetByRemoteID<alt::IBaseObject::Type::MARKER>();
});
