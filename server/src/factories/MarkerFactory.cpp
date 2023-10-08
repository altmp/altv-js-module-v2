#include "FactoryHandler.h"
#include "interfaces/IResource.h"

// clang-format off
static js::FactoryHandler markerFactory(alt::IBaseObject::Type::MARKER, [](js::Object& args) -> alt::IBaseObject* {
    alt::IResource* resource = args.GetResource()->GetResource();

    alt::IPlayer* target = nullptr;
    alt::Vector3f pos = {0, 0, 0};

    // TODO (xLuxy): This needs testing once server-sided markers are implemented.
    if (args.Has("target"))
    {
        if (!args.Get("target", target)) return nullptr;
    }
    else if (args.Has("pos"))
    {
        if (!args.Get("pos", pos)) return nullptr;
    }

    alt::IMarker::MarkerType markerType;
    if (!args.Get("type", markerType)) return nullptr;

    auto color = args.Get<alt::RGBA>("color", {255, 255, 255, 255});

    return alt::ICore::Instance().CreateMarker(target, markerType, pos, color, resource);
});
