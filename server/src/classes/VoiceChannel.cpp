#include "Class.h"
#include "cpp-sdk/ICore.h"

// clang-format off
extern js::Class baseObjectClass;
extern js::Class voiceChannelClass("VoiceChannel", &baseObjectClass, nullptr, [](js::ClassTemplate& tpl)
{
    tpl.BindToType(alt::IBaseObject::Type::VOICE_CHANNEL);

    tpl.LazyProperty<&alt::IVoiceChannel::IsSpatial>("isSpatial");
    tpl.LazyProperty<&alt::IVoiceChannel::GetMaxDistance>("maxDistance");

    tpl.Property<&alt::IVoiceChannel::GetPriority, &alt::IVoiceChannel::SetPriority>("priority");
    tpl.Property<&alt::IVoiceChannel::GetFilter, &alt::IVoiceChannel::SetFilter>("filter");

    tpl.Property<&alt::IVoiceChannel::GetPlayers>("players");
    tpl.Property<&alt::IVoiceChannel::GetPlayerCount>("playerCount");

    tpl.Method<&alt::IVoiceChannel::HasPlayer>("hasPlayer");
    tpl.Method<&alt::IVoiceChannel::AddPlayer>("addPlayer");
    tpl.Method<&alt::IVoiceChannel::RemovePlayer>("removePlayer");
    tpl.Method<&alt::IVoiceChannel::IsPlayerMuted>("isPlayerMuted");
    tpl.Method<&alt::IVoiceChannel::MutePlayer>("mutePlayer");
    tpl.Method<&alt::IVoiceChannel::UnmutePlayer>("unmutePlayer");

    tpl.GetByID<alt::IBaseObject::Type::VOICE_CHANNEL>();
});
