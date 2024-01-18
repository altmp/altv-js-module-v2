#include "FactoryHandler.h"
#include "Logger.h"

// clang-format off
static js::FactoryHandler voiceChannelFactory(alt::IBaseObject::Type::VOICE_CHANNEL, [](js::Object& args) -> alt::IBaseObject* {
    bool spatial;
    if(!args.Get("spatial", spatial)) return nullptr;

    float maxDistance = args.Get<float>("maxDistance");

    // Check if voice chat is enabled
    const auto config = alt::ICore::Instance().GetServerConfig()->Get("voice");
    if (config->IsNone())
    {
        js::Throw("Failed to create voice channel, make sure external voice chat is enabled.");
        return nullptr;
    }

    return alt::ICore::Instance().CreateVoiceChannel(spatial, maxDistance);
});
