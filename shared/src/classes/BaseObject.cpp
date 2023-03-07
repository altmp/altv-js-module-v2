#include "Class.h"
#include "cpp-sdk/ICore.h"

static void MetaGetter(js::PropertyContext<v8::Value>& ctx)
{
    alt::IBaseObject* obj = ctx.GetParent<alt::IBaseObject>();
    ctx.Check(obj != nullptr, "Invalid base object");
    ctx.Return(obj->GetMetaData(ctx.GetProperty()));
}
static void MetaSetter(js::PropertyContext<v8::Value>& ctx)
{
    alt::IBaseObject* obj = ctx.GetParent<alt::IBaseObject>();
    ctx.Check(obj != nullptr, "Invalid base object");
    alt::MValue value;
    if(!ctx.GetValue(0, value)) return;
    obj->SetMetaData(ctx.GetProperty(), value);
}
static void MetaDeleter(js::PropertyContext<v8::Boolean>& ctx)
{
    alt::IBaseObject* obj = ctx.GetParent<alt::IBaseObject>();
    ctx.Check(obj != nullptr, "Invalid base object");
    if(!obj->HasMetaData(ctx.GetProperty()))
    {
        ctx.Return(false);
        return;
    }
    obj->DeleteMetaData(ctx.GetProperty());
    ctx.Return(true);
}
static void MetaEnumerator(js::PropertyContext<v8::Array>& ctx)
{
    alt::IBaseObject* obj = ctx.GetParent<alt::IBaseObject>();
    ctx.Check(obj != nullptr, "Invalid base object");
    std::vector<std::string> keys = obj->GetMetaDataKeys();
    ctx.Return(keys);
}

// clang-format off
extern js::Class baseObjectClass("BaseObject", nullptr, [](js::ClassTemplate& tpl)
{
    tpl.Method<alt::IBaseObject, alt::MValueConst, const std::string&, &alt::IBaseObject::GetMetaData>("getMeta");
    tpl.Method<alt::IBaseObject, void, const std::string&, alt::MValue, &alt::IBaseObject::SetMetaData>("setMeta");
    tpl.Property<alt::IBaseObject, &alt::IBaseObject::GetType>("type");
    tpl.DynamicProperty("meta", MetaGetter, MetaSetter, MetaDeleter, MetaEnumerator);
});
