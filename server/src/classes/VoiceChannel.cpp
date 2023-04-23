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

    tpl.Property<alt::IVoiceChannel, &alt::IVoiceChannel::GetPlayers>("players");
    tpl.Property<alt::IVoiceChannel, &alt::IVoiceChannel::GetPlayerCount>("playerCount");

    tpl.MethodEx<&alt::IVoiceChannel::HasPlayer>("hasPlayer");
    tpl.MethodEx<&alt::IVoiceChannel::AddPlayer>("addPlayer");
    tpl.MethodEx<&alt::IVoiceChannel::RemovePlayer>("removePlayer");
    tpl.MethodEx<&alt::IVoiceChannel::IsPlayerMuted>("isPlayerMuted");
    tpl.MethodEx<&alt::IVoiceChannel::MutePlayer>("mutePlayer");
    tpl.MethodEx<&alt::IVoiceChannel::UnmutePlayer>("unmutePlayer");
});
