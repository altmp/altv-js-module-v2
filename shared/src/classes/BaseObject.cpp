#include "Class.h"
#include "cpp-sdk/ICore.h"

static void ValidGetter(js::PropertyContext& ctx)
{
    ctx.Return(ctx.GetThisObject<alt::IBaseObject>() != nullptr);
}

static void Destroy(js::FunctionContext& ctx)
{
    if(!ctx.CheckThis()) return;

    alt::IBaseObject* obj = ctx.GetThisObject<alt::IBaseObject>();
    alt::ICore::Instance().DestroyBaseObject(obj);
}

static void MetaGetter(js::DynamicPropertyGetterContext& ctx)
{
    if(!ctx.CheckParent()) return;
    alt::IBaseObject* obj = ctx.GetParent<alt::IBaseObject>();
    ctx.Return(obj->GetMetaData(ctx.GetProperty()));
}

static void MetaSetter(js::DynamicPropertySetterContext& ctx)
{
    if(!ctx.CheckParent()) return;
    alt::IBaseObject* obj = ctx.GetParent<alt::IBaseObject>();
    alt::MValue value;
    if(!ctx.GetValue(value)) return;
    obj->SetMetaData(ctx.GetProperty(), value);
}

static void MetaDeleter(js::DynamicPropertyDeleterContext& ctx)
{
    if(!ctx.CheckParent()) return;
    alt::IBaseObject* obj = ctx.GetParent<alt::IBaseObject>();
    if(!obj->HasMetaData(ctx.GetProperty()))
    {
        ctx.Return(false);
        return;
    }
    obj->DeleteMetaData(ctx.GetProperty());
    ctx.Return(true);
}

static void MetaEnumerator(js::DynamicPropertyEnumeratorContext& ctx)
{
    if(!ctx.CheckParent()) return;
    alt::IBaseObject* obj = ctx.GetParent<alt::IBaseObject>();
    std::vector<std::string> keys = obj->GetMetaDataKeys();
    ctx.Return(keys);
}

static void SyncedMetaGetter(js::DynamicPropertyGetterContext& ctx)
{
    if(!ctx.CheckParent()) return;
    alt::IBaseObject* obj = ctx.GetParent<alt::IBaseObject>();
    ctx.Return(obj->GetSyncedMetaData(ctx.GetProperty()));
}

static void SyncedMetaEnumerator(js::DynamicPropertyEnumeratorContext& ctx)
{
    if(!ctx.CheckParent()) return;
    alt::IBaseObject* obj = ctx.GetParent<alt::IBaseObject>();
    std::vector<std::string> keys = obj->GetSyncedMetaDataKeys();
    ctx.Return(keys);
}

static void SetMultipleMetaData(js::FunctionContext& ctx)
{
    if (!ctx.CheckThis()) return;
    if (!ctx.CheckArgCount(1)) return;

    alt::IBaseObject* obj = ctx.GetThisObject<alt::IBaseObject>();

    js::Object dict;
    if(!ctx.GetArg(0, dict)) return;

    std::unordered_map<std::string, alt::MValue> values;
    for (auto key : dict.GetKeys())
    {
        alt::MValue val;
        if(!dict.Get(key, val)) continue;
        values[key] = val;
    }

    obj->SetMultipleMetaData(values);
}

static void SetMultipleSyncedMetaData(js::FunctionContext& ctx)
{
    if (!ctx.CheckThis()) return;
    if (!ctx.CheckArgCount(1)) return;

    alt::IBaseObject* obj = ctx.GetThisObject<alt::IBaseObject>();
    if(!obj) return;

    js::Object dict;
    if(!ctx.GetArg(0, dict)) return;

    std::unordered_map<std::string, alt::MValue> values;
    for (auto key : dict.GetKeys())
    {
        alt::MValue val;
        if(!dict.Get(key, val)) continue;
        values[key] = val;
    }

    obj->SetMultipleSyncedMetaData(values);
}

static void GetByID(js::FunctionContext& ctx)
{
    if(!ctx.CheckArgCount(2)) return;

    alt::IBaseObject::Type type;
    if(!ctx.GetArg(0, type)) return;

    uint32_t id;
    if(!ctx.GetArg(1, id)) return;

    alt::IBaseObject* obj = alt::ICore::Instance().GetBaseObjectByID(type, id);
    ctx.Return(obj);
}

// clang-format off
extern js::Class baseObjectClass("BaseObject", [](js::ClassTemplate& tpl)
{
    tpl.LazyProperty<&alt::IBaseObject::GetID>("id");
    tpl.LazyProperty<&alt::IBaseObject::GetType>("type");

    tpl.Property("valid", ValidGetter);
    tpl.Property<&alt::IBaseObject::IsRemoved>("removed");

    tpl.Method("destroy", Destroy);

    tpl.DynamicProperty("meta", MetaGetter, MetaSetter, MetaDeleter, MetaEnumerator);
    tpl.DynamicProperty("syncedMeta", SyncedMetaGetter, nullptr, nullptr, SyncedMetaEnumerator);

    tpl.Method("setMultipleMetaData", SetMultipleMetaData);
    tpl.Method("setMultipleSyncedMetaData", SetMultipleSyncedMetaData);

    tpl.StaticFunction("getByID", GetByID);
});
