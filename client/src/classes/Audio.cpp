#include "Class.h"

// clang-format off
extern js::Class audioClass("Audio", [](js::ClassTemplate& tpl)
{
    tpl.BindToType(alt::IBaseObject::Type::AUDIO);

    tpl.Property<&alt::IAudio::GetSource, &alt::IAudio::SetSource>("source");
    tpl.Property<&alt::IAudio::IsLoop, &alt::IAudio::SetLoop>("loop");
    tpl.Property<&alt::IAudio::GetVolume, &alt::IAudio::SetVolume>("volume");
    tpl.Property<&alt::IAudio::GetOutputs>("outputs");
    tpl.Property<&alt::IAudio::GetCurrentTime>("currentTime");
    tpl.Property<&alt::IAudio::GetMaxTime>("maxTime");
    tpl.Property<&alt::IAudio::IsPlaying>("playing");

    tpl.Method<&alt::IAudio::AddOutput>("addOutput");
    tpl.Method<&alt::IAudio::RemoveOutput>("removeOutput");
    tpl.Method<&alt::IAudio::Play>("play");
    tpl.Method<&alt::IAudio::Pause>("pause");
    tpl.Method<&alt::IAudio::Reset>("reset");
    tpl.Method<&alt::IAudio::Seek>("seek");

    tpl.GetByID<alt::IBaseObject::Type::AUDIO>();
});
