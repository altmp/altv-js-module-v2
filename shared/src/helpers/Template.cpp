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

void js::ModuleTemplate::Namespace(const std::string& name, js::Namespace& namespace_)
{
    Get()->Set(JSValue(name), namespace_.Initialize(GetIsolate()));
}
