#include "Class.h"
#include "cpp-sdk/ICore.h"

static void StreamSyncedMetaGetter(js::DynamicPropertyGetterContext& ctx)
{
    if(!ctx.CheckParent()) return;
    alt::IEntity* obj = ctx.GetParent<alt::IEntity>();
    ctx.Return(obj->GetStreamSyncedMetaData(ctx.GetProperty()));
}

static void StreamSyncedMetaEnumerator(js::DynamicPropertyEnumeratorContext& ctx)
{
    if(!ctx.CheckParent()) return;
    alt::IEntity* obj = ctx.GetParent<alt::IEntity>();
    ctx.Return(obj->GetStreamSyncedMetaDataKeys());
}

// clang-format off
extern js::Class worldObjectClass;
extern js::Class sharedEntityClass("SharedEntity", &worldObjectClass, nullptr, [](js::ClassTemplate& tpl)
{
    tpl.Property<&alt::IEntity::GetModel>("model");
    tpl.Property<&alt::IEntity::GetNetworkOwner>("netOwner");
    tpl.Property<&alt::IEntity::GetRotation, &alt::IEntity::SetRotation>("rot");
    tpl.Property<&alt::IEntity::GetVisible>("visible");
    tpl.Property<&alt::IEntity::IsFrozen, &alt::IEntity::SetFrozen>("frozen");

    tpl.DynamicProperty("streamSyncedMeta", StreamSyncedMetaGetter, nullptr, nullptr, StreamSyncedMetaEnumerator);
});
