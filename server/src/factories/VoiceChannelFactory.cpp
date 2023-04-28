#include "FactoryHandler.h"
#include "Logger.h"

// clang-format off
static js::FactoryHandler voiceChannelFactory(alt::IBaseObject::Type::VOICE_CHANNEL, [](js::Object& args) -> alt::IBaseObject* {
    bool spatial;
    if(!args.Get("spatial", spatial)) return nullptr;
    float maxDistance = args.Get<float>("maxDistance");
    return alt::ICore::Instance().CreateVoiceChannel(spatial, maxDistance);
});
