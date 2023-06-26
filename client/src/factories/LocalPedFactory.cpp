#include "FactoryHandler.h"
#include "interfaces/IResource.h"

// clang-format off
static js::FactoryHandler localPedFactory(alt::IBaseObject::Type::LOCAL_PED, [](js::Object& args) -> alt::IBaseObject* {
    uint32_t model;
    if(args.GetType("model") == js::Type::NUMBER)      model = args.Get<uint32_t>("model");
    else if(args.GetType("model") == js::Type::STRING) model = alt::ICore::Instance().Hash(args.Get<std::string>("model"));
    else return nullptr;

    uint32_t dimension;
    if(!args.Get("dimension", dimension)) return nullptr;

    alt::Vector3f pos;
    if(!args.Get<alt::Vector3f>("pos", pos)) return nullptr;

    alt::Vector3f rot;
    if(!args.Get<alt::Vector3f>("rot", rot)) return nullptr;

    bool useStreaming = args.Get<bool>("useStreaming", true);

    uint32_t streamingDistance = args.Get<uint32_t>("streamingDistance", 100);

    return alt::ICore::Instance().CreateLocalPed(model, dimension, pos, rot, useStreaming, streamingDistance);
});
