#include "FactoryHandler.h"
#include "interfaces/IResource.h"

// clang-format off
static js::FactoryHandler objectFactory(alt::IBaseObject::Type::OBJECT, [](js::Object& args) -> alt::IBaseObject* {
    uint32_t modelHash;
    if(!args.GetAsHash("model", modelHash)) return nullptr;

    alt::Vector3f pos;
    if(!args.Get("pos", pos)) return nullptr;

    alt::Vector3f rot;
    if(!args.Get("rot", rot)) return nullptr;

    bool noOffset = args.Get<bool>("noOffset", false);

    bool dynamic = args.Get<bool>("dynamic", false);

    bool useStreaming = args.Get<bool>("useStreaming", false);

    uint32_t streamingDistance = args.Get<uint32_t>("streamingDistance", 0);

    return alt::ICore::Instance().CreateObject(modelHash, pos, rot, noOffset, dynamic, useStreaming, streamingDistance, args.GetResource()->GetResource());
});
