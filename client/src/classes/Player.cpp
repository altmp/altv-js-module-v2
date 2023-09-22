#include "Class.h"

static void FilterGetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckThis()) return;
    alt::IPlayer* player = ctx.GetThisObject<alt::IPlayer>();

    ctx.Return(player->GetFilter());
}

static void FilterSetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckThis()) return;
    if(!ctx.CheckValueType({ js::Type::BASE_OBJECT, js::Type::NULL_TYPE })) return;
    alt::IPlayer* player = ctx.GetThisObject<alt::IPlayer>();

    if(ctx.GetValueType() == js::Type::BASE_OBJECT)
    {
        alt::IAudioFilter* filter;
        if(!ctx.GetValue(filter)) return;
        player->AddFilter(filter);
    }
    else
        player->RemoveFilter();
}

static void LocalGetter(js::LazyPropertyContext& ctx)
{
    ctx.Return(alt::ICore::Instance().GetLocalPlayer());
}

// clang-format off
extern js::Class sharedPlayerClass;
extern js::Class playerClass("Player", &sharedPlayerClass, nullptr, [](js::ClassTemplate& tpl)
{
    tpl.BindToType(alt::IBaseObject::Type::PLAYER);

    tpl.Property<&alt::IPlayer::IsTalking>("isTalking");
    tpl.Property<&alt::IPlayer::GetMicLevel>("micLevel");
    tpl.Property<&alt::IPlayer::GetSpatialVolume, &alt::IPlayer::SetSpatialVolume>("spatialVolume");
    tpl.Property<&alt::IPlayer::GetNonSpatialVolume, &alt::IPlayer::SetNonSpatialVolume>("nonSpatialVolume");
    tpl.Property("filter", FilterGetter, FilterSetter);

    tpl.StaticLazyProperty("local", LocalGetter);

    tpl.GetByID<alt::IBaseObject::Type::PLAYER>();
    tpl.GetByRemoteID<alt::IBaseObject::Type::PLAYER>();
});
