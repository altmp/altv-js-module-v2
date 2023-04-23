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

static void MetaGetter(js::DynamicPropertyContext<v8::Value>& ctx)
{
    if(!ctx.CheckParent()) return;
    alt::IBaseObject* obj = ctx.GetParent<alt::IBaseObject>();
    ctx.Return(obj->GetMetaData(ctx.GetProperty()));
}

static void MetaSetter(js::DynamicPropertyContext<v8::Value>& ctx)
{
    if(!ctx.CheckParent()) return;
    alt::IBaseObject* obj = ctx.GetParent<alt::IBaseObject>();
    alt::MValue value;
    if(!ctx.GetValue(value)) return;
    obj->SetMetaData(ctx.GetProperty(), value);
}

static void MetaDeleter(js::DynamicPropertyContext<v8::Boolean>& ctx)
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

static void MetaEnumerator(js::DynamicPropertyContext<v8::Array>& ctx)
{
    if(!ctx.CheckParent()) return;
    alt::IBaseObject* obj = ctx.GetParent<alt::IBaseObject>();
    std::vector<std::string> keys = obj->GetMetaDataKeys();
    ctx.Return(keys);
}

// clang-format off
extern js::Class baseObjectClass("BaseObject", nullptr, [](js::ClassTemplate& tpl)
{
    tpl.Property<&alt::IBaseObject::GetType>("type");
    tpl.Property("valid", ValidGetter);

    tpl.Method("destroy", Destroy);

    tpl.Method<&alt::IBaseObject::SetMetaData>("setMetaData");
    tpl.Method<&alt::IBaseObject::GetMetaData>("getMetaData");

    tpl.DynamicProperty("meta", MetaGetter, MetaSetter, MetaDeleter, MetaEnumerator);
});
