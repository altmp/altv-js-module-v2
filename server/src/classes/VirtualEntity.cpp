#include "Class.h"
#include "cpp-sdk/ICore.h"

static void StreamSyncedMetaSetter(js::DynamicPropertyContext<v8::Value>& ctx)
{
    if(!ctx.CheckParent()) return;
    alt::IVirtualEntity* obj = ctx.GetParent<alt::IVirtualEntity>();

    alt::MValue value;
    if(!ctx.GetValue(value)) return;

    obj->SetStreamSyncedMetaData(ctx.GetProperty(), value);
}

static void StreamSyncedMetaDeleter(js::DynamicPropertyContext<v8::Boolean>& ctx)
{
    if(!ctx.CheckParent()) return;
    alt::IVirtualEntity* obj = ctx.GetParent<alt::IVirtualEntity>();

    if(!obj->HasStreamSyncedMetaData(ctx.GetProperty()))
    {
        ctx.Return(false);
        return;
    }

    obj->DeleteStreamSyncedMetaData(ctx.GetProperty());
    ctx.Return(true);
}

// clang-format off
extern js::Class sharedVirtualEntityClass;
extern js::Class virtualEntityClass("VirtualEntity", &sharedVirtualEntityClass, nullptr, [](js::ClassTemplate& tpl)
{
    tpl.BindToType(alt::IBaseObject::Type::VIRTUAL_ENTITY);

    tpl.DynamicProperty("streamSyncedMeta", nullptr, StreamSyncedMetaSetter, StreamSyncedMetaDeleter, nullptr);
});
