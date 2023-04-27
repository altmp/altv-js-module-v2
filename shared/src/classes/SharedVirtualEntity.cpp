#include "Class.h"
#include "cpp-sdk/ICore.h"

static void StreamSyncedMetaGetter(js::DynamicPropertyContext<v8::Value>& ctx)
{
    if(!ctx.CheckParent()) return;
    alt::IVirtualEntity* obj = ctx.GetParent<alt::IVirtualEntity>();
    ctx.Return(obj->GetStreamSyncedMetaData(ctx.GetProperty()));
}

static void StreamSyncedMetaEnumerator(js::DynamicPropertyContext<v8::Array>& ctx)
{
    if(!ctx.CheckParent()) return;
    alt::IVirtualEntity* obj = ctx.GetParent<alt::IVirtualEntity>();
    ctx.Return(obj->GetStreamSyncedMetaDataKeys());
}

// clang-format off
extern js::Class worldObjectClass;
extern js::Class sharedVirtualEntityClass("SharedVirtualEntity", &worldObjectClass, nullptr, [](js::ClassTemplate& tpl)
{
    tpl.LazyProperty<&alt::IVirtualEntity::GetID>("id");
    tpl.LazyProperty<&alt::IVirtualEntity::GetGroup>("group");
    tpl.LazyProperty<&alt::IVirtualEntity::GetStreamingDistance>("streamingDistance");

    tpl.DynamicProperty("streamSyncedMeta", StreamSyncedMetaGetter, nullptr, nullptr, StreamSyncedMetaEnumerator);
});
