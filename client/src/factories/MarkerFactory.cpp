#include "FactoryHandler.h"
#include "interfaces/IResource.h"

// clang-format off
static js::FactoryHandler markerFactory(alt::IBaseObject::Type::MARKER, [](js::Object& args) -> alt::IBaseObject* {
    alt::IResource* resource = args.GetResource()->GetResource();

    alt::IMarker::MarkerType markerType;
    if (!args.Get("type", markerType)) return nullptr;

    alt::Vector3f pos;
    if (!args.Get("pos", pos)) return nullptr;

    auto color = args.Get<alt::RGBA>("color", {255, 255, 255, 255});
    bool useStreaming = args.Get<bool>("useStreaming", false);
    uint32_t streamingDistance = args.Get<uint32_t>("streamingDistance", 0);

    return alt::ICore::Instance().CreateMarker(markerType, pos, color, useStreaming, streamingDistance, resource);
});
