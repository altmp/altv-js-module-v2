#include "FactoryHandler.h"
#include "interfaces/IResource.h"

// clang-format off
static js::FactoryHandler audioFactory(alt::IBaseObject::Type::AUDIO, [](js::Object& args) -> alt::IBaseObject* {
    std::string source;
    if(!args.Get("source", source)) return nullptr;

    float volume;
    if(!args.Get("volume", volume)) return nullptr;

    uint32_t category;
    if(!args.GetAsHash("category", category)) return nullptr;

    bool frontend = args.Get<bool>("frontend", false);

    return alt::ICore::Instance().CreateAudio(source, volume, category, frontend, args.GetResource()->GetResource());
});
