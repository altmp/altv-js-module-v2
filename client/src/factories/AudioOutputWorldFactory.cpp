#include "FactoryHandler.h"
#include "interfaces/IResource.h"

// clang-format off
static js::FactoryHandler audioOutputWorldFactory(alt::IBaseObject::Type::AUDIO_OUTPUT_WORLD, [](js::Object& args) -> alt::IBaseObject* {
    alt::Vector3f pos;
    if(!args.Get("pos", pos)) return nullptr;

    uint32_t categoryHash = args.Get<uint32_t>("categoryHash", alt::ICore::Instance().Hash("radio"));

    return alt::ICore::Instance().CreateWorldOutput(categoryHash, pos, args.GetResource()->GetResource());
});
