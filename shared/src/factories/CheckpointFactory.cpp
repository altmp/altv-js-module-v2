#include "FactoryHandler.h"
#include "interfaces/IResource.h"

// clang-format off
static js::FactoryHandler checkpointFactory(alt::IBaseObject::Type::CHECKPOINT, [](js::Object& args) -> alt::IBaseObject* {
    uint8_t type;
    alt::Vector3f pos;
    float radius, height;
    alt::RGBA color;
    uint32_t streamingDistance;

    if(!args.Get("type", type)) return nullptr;
    if(!args.Get("pos", pos)) return nullptr;
    if(!args.Get("radius", radius)) return nullptr;
    if(!args.Get("height", height)) return nullptr;
    if(!args.Get("color", color)) return nullptr;
    if(!args.Get("streamingDistance", streamingDistance)) return nullptr;

    // todo: remove when fixed in core
    #ifdef ALT_CLIENT_API
    alt::RGBA iconColor;
    alt::Vector3f nextPos;
    if(!args.Get("iconColor", iconColor)) return nullptr;
    if(!args.Get("nextPos", nextPos)) return nullptr;
    return alt::ICore::Instance().CreateCheckpoint(type, pos, nextPos, radius, height, color, iconColor, streamingDistance, args.GetResource()->GetResource());
    #else
    return alt::ICore::Instance().CreateCheckpoint(type, pos, radius, height, color, streamingDistance);
    #endif
});
