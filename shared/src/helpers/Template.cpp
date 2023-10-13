#include "Template.h"
#include "interfaces/IResource.h"
#include "Namespace.h"

#include <fstream>
#include <filesystem>

void js::Wrapper::DynamicPropertyLazyHandler(v8::Local<v8::Name> property, const v8::PropertyCallbackInfo<v8::Value>& info)
{
    DynamicPropertyGetterContext ctx{ info, property };

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
    tpl->SetInternalFieldCount(2);
    tpl->SetHandler(config);
    v8::Local<v8::Object> obj = tpl->NewInstance(context).ToLocalChecked();
    obj->SetInternalField(0, info.This());
    ctx.Return(obj);
}

void js::Wrapper::DynamicPropertyGetterHandler(v8::Local<v8::Name> property, const v8::PropertyCallbackInfo<v8::Value>& info)
{
    DynamicPropertyGetterContext ctx{ info, property };
    v8::Local<v8::Object> parent = info.This()->GetInternalField(0).As<v8::Object>();
    ctx.SetParent(parent);

    auto data = static_cast<ClassTemplate::DynamicPropertyData*>(info.Data().As<v8::External>()->Value());
    data->getter(ctx);
}

void js::Wrapper::DynamicPropertySetterHandler(v8::Local<v8::Name> property, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<v8::Value>& info)
{
    DynamicPropertySetterContext ctx{ info, property, value };
    v8::Local<v8::Object> parent = info.This()->GetInternalField(0).As<v8::Object>();
    ctx.SetParent(parent);

    auto data = static_cast<ClassTemplate::DynamicPropertyData*>(info.Data().As<v8::External>()->Value());
    data->setter(ctx);
    info.GetReturnValue().Set(value);
}

void js::Wrapper::DynamicPropertyDeleterHandler(v8::Local<v8::Name> property, const v8::PropertyCallbackInfo<v8::Boolean>& info)
{
    DynamicPropertyDeleterContext ctx{ info, property };
    v8::Local<v8::Object> parent = info.This()->GetInternalField(0).As<v8::Object>();
    ctx.SetParent(parent);

    auto data = static_cast<ClassTemplate::DynamicPropertyData*>(info.Data().As<v8::External>()->Value());
    data->deleter(ctx);
}

void js::Wrapper::DynamicPropertyEnumeratorHandler(const v8::PropertyCallbackInfo<v8::Array>& info)
{
    DynamicPropertyEnumeratorContext ctx{ info };
    v8::Local<v8::Object> parent = info.This()->GetInternalField(0).As<v8::Object>();
    ctx.SetParent(parent);

    auto data = static_cast<ClassTemplate::DynamicPropertyData*>(info.Data().As<v8::External>()->Value());
    data->enumerator(ctx);
}

void js::ModuleTemplate::Namespace(const std::string& name, js::Namespace& namespace_)
{
    Get()->Set(JSValue(name), namespace_.Get(GetIsolate()));
}

void js::ModuleTemplate::Namespace(js::Namespace& namespace_)
{
    Get()->Set(JSValue(namespace_.GetName()), namespace_.Get(GetIsolate()));
}

static void StaticBindingExportGetter(v8::Local<v8::Name>, const v8::PropertyCallbackInfo<v8::Value>& info)
{
    js::LazyPropertyContext ctx{ info };
    std::string exportName = js::CppValue(info.Data().As<v8::String>());
    ctx.Return(ctx.GetResource()->GetBindingExport(exportName));
}

void js::ModuleTemplate::StaticBindingExport(const std::string& name, const std::string& exportName)
{
    Get()->SetLazyDataProperty(JSValue(name), StaticBindingExportGetter, JSValue(exportName));
}

js::ClassTemplate::DynamicPropertyData* js::ClassTemplate::GetDynamicPropertyData(v8::Isolate* isolate, Class* class_, const std::string& name)
{
    auto& dynamicPropertyDataMap = GetDynamicPropertyDataMap();
    auto& clsMap = dynamicPropertyDataMap[isolate];
    Class* currentClass = class_;
    DynamicPropertyData* data = nullptr;
    while(!data && currentClass)
    {
        if(!clsMap.contains(currentClass) || !clsMap.at(currentClass).contains(name))
        {
            currentClass = currentClass->GetParentClass();
            continue;
        }
        data = clsMap.at(currentClass).at(name);
    }
    return data;
}

v8::Local<v8::FunctionTemplate> js::ClassTemplate::GetPropertyGetter(v8::Isolate* isolate, Class* cls, const std::string& name)
{
    auto& propertyGetterMap = GetPropertyGetterMap();
    auto& clsMap = propertyGetterMap[isolate];
    v8::Local<v8::FunctionTemplate> tpl;
    Class* currentClass = cls;
    while(tpl.IsEmpty() && currentClass)
    {
        if(!clsMap.contains(currentClass) || !clsMap.at(currentClass).contains(name))
        {
            currentClass = currentClass->GetParentClass();
            continue;
        }
        tpl = clsMap.at(currentClass).at(name).Get(isolate);
    }
    return tpl;
}

void js::ClassTemplate::BindToType(alt::IBaseObject::Type type)
{
    IScriptObjectHandler::BindClassToType(type, class_);
}

void js::ClassTemplate::Inherit(ClassTemplate& parent)
{
    Get()->Inherit(parent.Get());

    // Inherit static methods
    for(auto& [name, method] : parent.staticMethods) StaticFunction(name, method);
}
