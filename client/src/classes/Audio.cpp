#include "Class.h"

static void AddOutput(js::FunctionContext& ctx)
{
    if(!ctx.CheckThis()) return;
    if(!ctx.CheckArgCount(1)) return;
    alt::IAudio* audio = ctx.GetThisObject<alt::IAudio>();

    alt::IAudioOutput* entity;
    if(!ctx.GetArg(0, entity)) return;

    audio->AddOutput(entity);
}

static void RemoveOutput(js::FunctionContext& ctx)
{
    if(!ctx.CheckThis()) return;
    if(!ctx.CheckArgCount(1)) return;
    alt::IAudio* audio = ctx.GetThisObject<alt::IAudio>();

    alt::IAudioOutput* entity;
    if(!ctx.GetArg(0, entity)) return;

    audio->RemoveOutput(entity);
}

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
    tpl.Property<&alt::IAudio::IsPlaying>("isPlaying");

    tpl.Method("addOutput", AddOutput);
    tpl.Method("removeOutput", RemoveOutput);
    tpl.Method<&alt::IAudio::Play>("play");
    tpl.Method<&alt::IAudio::Pause>("pause");
    tpl.Method<&alt::IAudio::Reset>("reset");
    tpl.Method<&alt::IAudio::Seek>("seek");

    tpl.GetByID<alt::IBaseObject::Type::AUDIO>();
});
