#include "FactoryHandler.h"
#include "interfaces/IResource.h"

// clang-format off
static js::FactoryHandler audioFilterFactory(alt::IBaseObject::Type::AUDIO_FILTER, [](js::Object& args) -> alt::IBaseObject* {
    uint32_t hash = 0;
    if(args.GetType("hash") == js::Type::NUMBER)      hash = args.Get<uint32_t>("hash");
    else if(args.GetType("hash") == js::Type::STRING) hash = alt::ICore::Instance().Hash(args.Get<std::string>("hash"));

    return alt::ICore::Instance().CreateAudioFilter(hash, args.GetResource()->GetResource());
});
