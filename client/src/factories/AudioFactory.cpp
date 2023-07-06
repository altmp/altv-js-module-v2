#include "FactoryHandler.h"
#include "interfaces/IResource.h"

// clang-format off
static js::FactoryHandler audioFactory(alt::IBaseObject::Type::AUDIO, [](js::Object& args) -> alt::IBaseObject* {
    std::string source;
    if(!args.Get("source", source)) return nullptr;

    float volume;
    if(!args.Get("volume", volume)) return nullptr;

    return alt::ICore::Instance().CreateAudio(source, volume, args.GetResource()->GetResource());
});
