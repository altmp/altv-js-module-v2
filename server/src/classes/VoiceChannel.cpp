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

    tpl.Method<alt::IVoiceChannel, bool, alt::IPlayer*, &alt::IVoiceChannel::HasPlayer>("hasPlayer");
    tpl.Method<alt::IVoiceChannel, void, alt::IPlayer*, &alt::IVoiceChannel::AddPlayer>("addPlayer");
    tpl.Method<alt::IVoiceChannel, void, alt::IPlayer*, &alt::IVoiceChannel::RemovePlayer>("removePlayer");
    tpl.Method<alt::IVoiceChannel, bool, alt::IPlayer*, &alt::IVoiceChannel::IsPlayerMuted>("isPlayerMuted");
    tpl.Method<alt::IVoiceChannel, void, alt::IPlayer*, &alt::IVoiceChannel::MutePlayer>("mutePlayer");
    tpl.Method<alt::IVoiceChannel, void, alt::IPlayer*, &alt::IVoiceChannel::UnmutePlayer>("unmutePlayer");
});
