#include "Class.h"
#include "cpp-sdk/ICore.h"

// clang-format off
extern js::Class baseObjectClass;
extern js::Class voiceChannelClass("VoiceChannel", &baseObjectClass, nullptr, [](js::ClassTemplate& tpl)
{
    tpl.BindToType(alt::IBaseObject::Type::VOICE_CHANNEL);

    tpl.LazyProperty<alt::IVoiceChannel, &alt::IVoiceChannel::GetID>("id");
    tpl.LazyProperty<alt::IVoiceChannel, &alt::IVoiceChannel::IsSpatial>("isSpatial");
    tpl.LazyProperty<alt::IVoiceChannel, &alt::IVoiceChannel::GetMaxDistance>("maxDistance");

    tpl.Property<&alt::IVoiceChannel::GetPlayers>("players");
    tpl.Property<&alt::IVoiceChannel::GetPlayerCount>("playerCount");

    tpl.Mehtod<&alt::IVoiceChannel::HasPlayer>("hasPlayer");
    tpl.Mehtod<&alt::IVoiceChannel::AddPlayer>("addPlayer");
    tpl.Mehtod<&alt::IVoiceChannel::RemovePlayer>("removePlayer");
    tpl.Mehtod<&alt::IVoiceChannel::IsPlayerMuted>("isPlayerMuted");
    tpl.Mehtod<&alt::IVoiceChannel::MutePlayer>("mutePlayer");
    tpl.Mehtod<&alt::IVoiceChannel::UnmutePlayer>("unmutePlayer");
});
