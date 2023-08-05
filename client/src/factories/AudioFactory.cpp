#include "FactoryHandler.h"
#include "interfaces/IResource.h"

// clang-format off
static js::FactoryHandler audioFactory(alt::IBaseObject::Type::AUDIO, [](js::Object& args) -> alt::IBaseObject* {
    std::string source;
    if(!args.Get("source", source)) return nullptr;

    float volume;
    if(!args.Get("volume", volume)) return nullptr;

    bool isRadio = args.Get<bool>("isRadio", false);

    js::IResource* resource = args.GetResource();
    return alt::ICore::Instance().CreateAudio(source, volume, isRadio, js::SourceLocation::GetCurrent(resource).file, resource->GetResource());
});
