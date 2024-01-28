#include "Class.h"
#include "cpp-sdk/ICore.h"

static void StreamSyncedMetaSetter(js::DynamicPropertySetterContext& ctx)
{
    if(!ctx.CheckParent()) return;
    alt::IVirtualEntity* obj = ctx.GetParent<alt::IVirtualEntity>();

    alt::MValue value;
    if(!ctx.GetValue(value)) return;

    obj->SetStreamSyncedMetaData(ctx.GetProperty(), value);
}

static void StreamSyncedMetaDeleter(js::DynamicPropertyDeleterContext& ctx)
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

static void SetMultipleStreamSyncedMetaData(js::FunctionContext& ctx)
{
    if (!ctx.CheckThis()) return;
    if (!ctx.CheckArgCount(1)) return;

    alt::IVirtualEntity* entity = ctx.GetThisObject<alt::IVirtualEntity>();

    js::Object dict;
    if(!ctx.GetArg(0, dict)) return;

    std::unordered_map<std::string, alt::MValue> values;
    for (auto key : dict.GetKeys())
    {
        alt::MValue val;
        if(!dict.Get(key, val)) continue;
        values[key] = val;
    }

    entity->SetMultipleStreamSyncedMetaData(values);
}

// clang-format off
extern js::Class sharedVirtualEntityClass;
extern js::Class virtualEntityClass("VirtualEntity", &sharedVirtualEntityClass, nullptr, [](js::ClassTemplate& tpl)
{
    tpl.BindToType(alt::IBaseObject::Type::VIRTUAL_ENTITY);

    tpl.DynamicProperty("streamSyncedMeta", nullptr, StreamSyncedMetaSetter, StreamSyncedMetaDeleter, nullptr);

    tpl.Method("setMultipleStreamSyncedMetaData", SetMultipleStreamSyncedMetaData);

    tpl.GetByID<alt::IBaseObject::Type::VIRTUAL_ENTITY>();
});
