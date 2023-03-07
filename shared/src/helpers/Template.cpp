#include "Template.h"
#include "interfaces/IResource.h"
#include "Namespace.h"

alt::IBaseObject* js::Wrapper::GetThisObjectFromInfo(const v8::PropertyCallbackInfo<v8::Value>& info)
{
    return IResource::GetFromContext(info.GetIsolate()->GetCurrentContext())->GetScriptObject(info.This())->GetObject();
}
alt::IBaseObject* js::Wrapper::GetThisObjectFromInfo(const v8::FunctionCallbackInfo<v8::Value>& info)
{
    return IResource::GetFromContext(info.GetIsolate()->GetCurrentContext())->GetScriptObject(info.This())->GetObject();
}

void js::Wrapper::DynamicPropertyLazyHandler(v8::Local<v8::Name> property, const v8::PropertyCallbackInfo<v8::Value>& info)
{
    PropertyContext<v8::Value> ctx{ info, property };

    js::ClassTemplate::DynamicPropertyData* data = static_cast<ClassTemplate::DynamicPropertyData*>(info.Data().As<v8::External>()->Value());
    v8::NamedPropertyHandlerConfiguration config;
    config.getter = Wrapper::DynamicPropertyGetterHandler;
    if(data->setter) config.setter = Wrapper::DynamicPropertySetterHandler;
    if(data->deleter) config.deleter = Wrapper::DynamicPropertyDeleterHandler;
    if(data->enumerator) config.enumerator = Wrapper::DynamicPropertyEnumeratorHandler;
    config.flags = v8::PropertyHandlerFlags::kOnlyInterceptStrings;
    config.data = v8::External::New(ctx.GetIsolate(), data);

    v8::Local<v8::Context> context = ctx.GetIsolate()->GetCurrentContext();
    v8::Local<v8::ObjectTemplate> tpl = v8::ObjectTemplate::New(ctx.GetIsolate());
    tpl->SetHandler(config);
    Object obj{ tpl->NewInstance(context).ToLocalChecked() };
    obj.AddProperty("__internalParent", info.This(), false, false, false);
    ctx.Return(obj.Get());
}

void js::Wrapper::DynamicPropertyGetterHandler(v8::Local<v8::Name> property, const v8::PropertyCallbackInfo<v8::Value>& info)
{
    Object thisObj{ info.This() };
    PropertyContext<v8::Value> ctx{ info, property };
    ctx.SetParent(thisObj.Get<alt::IBaseObject*>("__internalParent"));

    auto data = static_cast<ClassTemplate::DynamicPropertyData*>(info.Data().As<v8::External>()->Value());
    data->getter(ctx);
}

void js::Wrapper::DynamicPropertySetterHandler(v8::Local<v8::Name> property, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<v8::Value>& info)
{
    Object thisObj{ info.This() };
    PropertyContext<v8::Value> ctx{ info, property, value };
    ctx.SetParent(thisObj.Get<alt::IBaseObject*>("__internalParent"));

    auto data = static_cast<ClassTemplate::DynamicPropertyData*>(info.Data().As<v8::External>()->Value());
    data->setter(ctx);
    info.GetReturnValue().Set(value);
}

void js::Wrapper::DynamicPropertyDeleterHandler(v8::Local<v8::Name> property, const v8::PropertyCallbackInfo<v8::Boolean>& info)
{
    Object thisObj{ info.This() };
    PropertyContext<v8::Boolean> ctx{ info, property };
    ctx.SetParent(thisObj.Get<alt::IBaseObject*>("__internalParent"));

    auto data = static_cast<ClassTemplate::DynamicPropertyData*>(info.Data().As<v8::External>()->Value());
    data->deleter(ctx);
}

void js::Wrapper::DynamicPropertyEnumeratorHandler(const v8::PropertyCallbackInfo<v8::Array>& info)
{
    Object thisObj{ info.This() };
    PropertyContext<v8::Array> ctx{ info };
    ctx.SetParent(thisObj.Get<alt::IBaseObject*>("__internalParent"));

    auto data = static_cast<ClassTemplate::DynamicPropertyData*>(info.Data().As<v8::External>()->Value());
    data->enumerator(ctx);
}

void js::ModuleTemplate::Namespace(const std::string& name, js::Namespace& namespace_)
{
    Get()->Set(JSValue(name), namespace_.Initialize(GetIsolate()));
}
