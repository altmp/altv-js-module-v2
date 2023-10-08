#include "Class.h"
#include "interfaces/IResource.h"
#include "cpp-sdk/ICore.h"

// clang-format off
extern js::Class sharedMarkerClass;
extern js::Class markerClass("Marker", &sharedMarkerClass, nullptr, [](js::ClassTemplate& tpl)
{
});
