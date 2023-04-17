#include "Class.h"
#include "cpp-sdk/ICore.h"

static void SyncedMetaGetter(js::DynamicPropertyContext<v8::Value>& ctx)
{
    if(!ctx.CheckParent()) return;
    alt::IEntity* obj = ctx.GetParent<alt::IEntity>();
    ctx.Return(obj->GetSyncedMetaData(ctx.GetProperty()));
}

static void SyncedMetaEnumerator(js::DynamicPropertyContext<v8::Array>& ctx)
{
    if(!ctx.CheckParent()) return;
    alt::IEntity* obj = ctx.GetParent<alt::IEntity>();
    std::vector<std::string> keys = obj->GetSyncedMetaDataKeys();
    ctx.Return(keys);
}

static void StreamSyncedMetaGetter(js::DynamicPropertyContext<v8::Value>& ctx)
{
    if(!ctx.CheckParent()) return;
    alt::IEntity* obj = ctx.GetParent<alt::IEntity>();
    ctx.Return(obj->GetStreamSyncedMetaData(ctx.GetProperty()));
}

static void StreamSyncedMetaEnumerator(js::DynamicPropertyContext<v8::Array>& ctx)
{
    if(!ctx.CheckParent()) return;
    alt::IEntity* obj = ctx.GetParent<alt::IEntity>();
    ctx.Return(obj->GetStreamSyncedMetaDataKeys());
}

// clang-format off
extern js::Class worldObjectClass;
extern js::Class sharedEntityClass("SharedEntity", &worldObjectClass, nullptr, [](js::ClassTemplate& tpl)
{
    tpl.LazyProperty<alt::IEntity, &alt::IEntity::GetID>("id");

    tpl.Property<alt::IEntity, &alt::IEntity::GetModel>("model");
    tpl.Property<alt::IEntity, &alt::IEntity::GetNetworkOwner>("netOwner");
    tpl.Property<alt::IEntity, alt::Rotation, &alt::IEntity::GetRotation, &alt::IEntity::SetRotation>("rot");
    tpl.Property<alt::IEntity, &alt::IEntity::GetVisible>("visible");

    tpl.DynamicProperty("syncedMeta", SyncedMetaGetter, nullptr, nullptr, SyncedMetaEnumerator);
    tpl.DynamicProperty("streamSyncedMeta", StreamSyncedMetaGetter, nullptr, nullptr, StreamSyncedMetaEnumerator);
});
