#include "FactoryHandler.h"

// clang-format off
static js::FactoryHandler markerFactory(alt::IBaseObject::Type::MARKER, [](js::Object& args) -> alt::IBaseObject* {
    alt::IResource* resource = args.GetResource()->GetResource();

    alt::IPlayer* target;
    if (!args.Get("target", target)) return nullptr;

    alt::IMarker::MarkerType markerType;
    if (!args.Get("type", markerType)) return nullptr;

    alt::Vector3f pos;
    if (!args.Get("pos", pos)) return nullptr;

    auto color = args.Get<alt::RGBA>("color", {255, 255, 255, 255});

    return alt::ICore::Instance().CreateMarker(target, markerType, pos, color, resource);
});
