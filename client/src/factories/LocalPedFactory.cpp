#include "FactoryHandler.h"
#include "interfaces/IResource.h"

// clang-format off
static js::FactoryHandler localPedFactory(alt::IBaseObject::Type::LOCAL_PED, [](js::Object& args) -> alt::IBaseObject* {
    uint32_t model;
    if(!args.GetAsHash("model", model)) return nullptr;

    int32_t dimension;
    if(!args.Get("dimension", dimension)) return nullptr;

    alt::Vector3f pos;
    if(!args.Get("pos", pos)) return nullptr;

    float heading = args.Get<float>("heading", 0.f);
    bool useStreaming = args.Get<bool>("useStreaming", false);
    uint32_t streamingDistance = args.Get<uint32_t>("streamingDistance", 0);

    return alt::ICore::Instance().CreateLocalPed(model, dimension, pos, { 0, 0, heading }, useStreaming, streamingDistance, args.GetResource()->GetResource());
});
