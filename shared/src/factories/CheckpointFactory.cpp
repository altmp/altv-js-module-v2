#include "FactoryHandler.h"
#include "interfaces/IResource.h"

// clang-format off
static js::FactoryHandler checkpointFactory(alt::IBaseObject::Type::CHECKPOINT, [](js::Object& args) -> alt::IBaseObject* {
    uint8_t type;
    if(!args.Get("type", type)) return nullptr;

    alt::Vector3f pos;
    if(!args.Get("pos", pos)) return nullptr;

    float radius;
    if(!args.Get("radius", radius)) return nullptr;

    float height;
    if(!args.Get("height", height)) return nullptr;

    alt::RGBA color;
    if(!args.Get("color", color)) return nullptr;

    uint32_t streamingDistance;
    if(!args.Get("streamingDistance", streamingDistance)) return nullptr;

    // todo: remove when fixed in core
    #ifdef ALT_CLIENT_API
    alt::RGBA iconColor;

    if(!args.Get("iconColor", iconColor)) return nullptr;
    alt::Vector3f nextPos;
    if(!args.Get("nextPos", nextPos)) return nullptr;

    return alt::ICore::Instance().CreateCheckpoint(type, pos, nextPos, radius, height, color, iconColor, streamingDistance, args.GetResource()->GetResource());
    #else
    return alt::ICore::Instance().CreateCheckpoint(type, pos, radius, height, color, streamingDistance);
    #endif
});
