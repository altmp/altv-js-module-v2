#include "FactoryHandler.h"
#include "interfaces/IResource.h"

// clang-format off
static js::FactoryHandler audioFilterFactory(alt::IBaseObject::Type::AUDIO_FILTER, [](js::Object& args) -> alt::IBaseObject* {
    uint32_t hash;
    if(!args.GetAsHash("hash", hash)) return nullptr;

    return alt::ICore::Instance().CreateAudioFilter(hash, args.GetResource()->GetResource());
});
