#include "Class.h"
#include "cpp-sdk/ICore.h"

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

static std::string testVal;
static void Get(js::PropertyContext& ctx)
{
    std::cout << "Get " << testVal << std::endl;
    ctx.Return(testVal);
}

static void Set(js::PropertyContext& ctx)
{
    std::cout << "Set " << testVal << std::endl;
    std::string val;
    if(!ctx.GetValue(val)) return;
    testVal = val;
}

// clang-format off
extern js::Class baseObjectClass("BaseObject", nullptr, [](js::ClassTemplate& tpl)
{
    tpl.Method<alt::IBaseObject, alt::MValueConst, const std::string&, &alt::IBaseObject::GetMetaData>("getMeta");
    tpl.Method<alt::IBaseObject, void, const std::string&, alt::MValue, &alt::IBaseObject::SetMetaData>("setMeta");
    tpl.Property<alt::IBaseObject, &alt::IBaseObject::GetType>("type");
    tpl.DynamicProperty("meta", MetaGetter, MetaSetter, MetaDeleter, MetaEnumerator);

    tpl.Property("testProp", Get, Set);
});
