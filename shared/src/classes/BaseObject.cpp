#include "Class.h"
#include "cpp-sdk/ICore.h"

static void SetMeta(js::FunctionContext& ctx)
{
    if(!ctx.CheckArgCount(2)) return;
    alt::IBaseObject* baseObject = ctx.GetThisObject<alt::IBaseObject>();

    std::string key;
    if(!ctx.GetArg(0, key, js::Type::String)) return;

    v8::Local<v8::Value> val;
    if(!ctx.GetArgRaw(1, val)) return;
    baseObject->SetMetaData(key, js::JSToMValue(val));
}

// clang-format off
extern js::Class baseObjectClass("BaseObject", nullptr, [](js::ClassTemplate& tpl)
{
    tpl.Method<alt::IBaseObject, alt::MValueConst, const std::string&, &alt::IBaseObject::GetMetaData>("getMeta");
    tpl.Method("setMeta", SetMeta);
    tpl.Property<alt::IBaseObject, &alt::IBaseObject::GetType>("type");
});
