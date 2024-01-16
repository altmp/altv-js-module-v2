#include "Class.h"

static void StreamSyncedMetaGetter(js::DynamicPropertyGetterContext& ctx)
{
    if(!ctx.CheckParent()) return;

    alt::ICheckpoint* obj = ctx.GetParent<alt::ICheckpoint>();

    ctx.Return(obj->GetStreamSyncedMetaData(ctx.GetProperty()));
}

static void StreamSyncedMetaSetter(js::DynamicPropertySetterContext& ctx)
{
    if(!ctx.CheckParent()) return;

    alt::ICheckpoint* obj = ctx.GetParent<alt::ICheckpoint>();

    alt::MValue value;
    if(!ctx.GetValue(value)) return;

    obj->SetStreamSyncedMetaData(ctx.GetProperty(), value);
}

static void StreamSyncedMetaDeleter(js::DynamicPropertyDeleterContext& ctx)
{
    if(!ctx.CheckParent()) return;

    alt::ICheckpoint* obj = ctx.GetParent<alt::ICheckpoint>();

    if(!obj->HasStreamSyncedMetaData(ctx.GetProperty()))
    {
        ctx.Return(false);
        return;
    }

    obj->DeleteStreamSyncedMetaData(ctx.GetProperty());
    ctx.Return(true);
}

static void StreamSyncedMetaEnumerator(js::DynamicPropertyEnumeratorContext& ctx)
{
    if(!ctx.CheckParent()) return;

    alt::ICheckpoint* obj = ctx.GetParent<alt::ICheckpoint>();

    ctx.Return(obj->GetStreamSyncedMetaDataKeys());
}

static void SetMultipleStreamSyncedMetaData(js::FunctionContext& ctx)
{
    if (!ctx.CheckThis()) return;
    if (!ctx.CheckArgCount(1)) return;

    alt::ICheckpoint* checkpoint = ctx.GetThisObject<alt::ICheckpoint>();

    js::Object dict;
    if(!ctx.GetArg(0, dict)) return;

    std::unordered_map<std::string, alt::MValue> values;
    for (auto key : dict.GetKeys())
    {
        alt::MValue val;
        if(!dict.Get(key, val)) continue;
        values[key] = val;
    }

    checkpoint->SetMultipleStreamSyncedMetaData(values);
}

// clang-format off
extern js::Class sharedCheckpointClass;
extern js::Class checkpointClass("Checkpoint", &sharedCheckpointClass, nullptr, [](js::ClassTemplate& tpl)
{
    tpl.BindToType(alt::IBaseObject::Type::CHECKPOINT);

    tpl.DynamicProperty("streamSyncedMeta", StreamSyncedMetaGetter, StreamSyncedMetaSetter, StreamSyncedMetaDeleter, StreamSyncedMetaEnumerator);

    tpl.Method("setMultipleStreamSyncedMetaData", SetMultipleStreamSyncedMetaData);

    tpl.GetByID<alt::IBaseObject::Type::CHECKPOINT>();
});
