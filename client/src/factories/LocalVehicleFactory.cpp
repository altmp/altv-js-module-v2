#include "FactoryHandler.h"
#include "interfaces/IResource.h"

// clang-format off
static js::FactoryHandler localVehicleFactory(alt::IBaseObject::Type::LOCAL_VEHICLE, [](js::Object& args) -> alt::IBaseObject* {
    uint32_t model;
    if(!args.GetAsHash("model", model)) return nullptr;

    uint32_t dimension;
    if(!args.Get("dimension", dimension)) return nullptr;

    alt::Vector3f pos;
    if(!args.Get("pos", pos)) return nullptr;

    alt::Vector3f rot;
    if(!args.Get("rot", rot)) return nullptr;

    bool useStreaming = args.Get<bool>("useStreaming", true);

    uint32_t streamingDistance = args.Get<uint32_t>("streamingDistance", 300);

    return alt::ICore::Instance().CreateLocalVehicle(model, dimension, pos, rot, useStreaming, streamingDistance, args.GetResource()->GetResource());
});
