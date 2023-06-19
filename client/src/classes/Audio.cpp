#include "Class.h"

static void CategoryGetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckThis()) return;
    alt::IAudio* audio = ctx.GetThisObject<alt::IAudio>();

    ctx.Return(audio->GetCategory());
}

static void CategorySetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckThis()) return;
    alt::IAudio* audio = ctx.GetThisObject<alt::IAudio>();

    uint32_t category;
    if(!ctx.GetValueAsHash(category)) return;

    audio->SetCategory(category);
}

static void AddOutput(js::FunctionContext& ctx)
{
    if(!ctx.CheckThis()) return;
    if(!ctx.CheckArgCount(1)) return;
    alt::IAudio* audio = ctx.GetThisObject<alt::IAudio>();

    if(!ctx.CheckArgType(0, { js::Type::BASE_OBJECT, js::Type::NUMBER })) return;

    if(ctx.GetArgType(0) == js::Type::BASE_OBJECT)
    {
        alt::IEntity* entity;
        if(!ctx.GetArg(0, entity)) return;

        audio->AddOutput(entity);
    }
    else
    {
        uint32_t scriptID;
        if(!ctx.GetArg(0, scriptID)) return;

        audio->AddOutput(scriptID);
    }
}

static void RemoveOutput(js::FunctionContext& ctx)
{
    if(!ctx.CheckThis()) return;
    if(!ctx.CheckArgCount(1, 2)) return;
    alt::IAudio* audio = ctx.GetThisObject<alt::IAudio>();

    if(!ctx.CheckArgType(0, { js::Type::BASE_OBJECT, js::Type::NUMBER })) return;

    if(ctx.GetArgType(0) == js::Type::BASE_OBJECT)
    {
        alt::IEntity* entity;
        if(!ctx.GetArg(0, entity)) return;
        bool removeRef = ctx.GetArg<bool>(1, true);

        audio->RemoveOutput(entity, removeRef);
    }
    else
    {
        uint32_t scriptID;
        if(!ctx.GetArg(0, scriptID)) return;
        bool removeRef = ctx.GetArg<bool>(1, true);

        audio->RemoveOutput(scriptID);
    }
}

// clang-format off
extern js::Class audioClass("Audio", [](js::ClassTemplate& tpl)
{
    tpl.BindToType(alt::IBaseObject::Type::AUDIO);

    tpl.Property<&alt::IAudio::GetSource, &alt::IAudio::SetSource>("source");
    tpl.Property<&alt::IAudio::IsLoop, &alt::IAudio::SetLoop>("loop");
    tpl.Property<&alt::IAudio::GetVolume, &alt::IAudio::SetVolume>("volume");
    tpl.Property("category", CategoryGetter, CategorySetter);
    tpl.Property<&alt::IAudio::IsFrontendPlay>("isFrontendPlay");
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
});
