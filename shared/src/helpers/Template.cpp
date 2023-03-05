#include "Template.h"
#include "interfaces/IResource.h"

alt::IBaseObject* js::Wrapper::GetThisObjectFromInfo(const v8::PropertyCallbackInfo<v8::Value>& info)
{
    return IResource::GetFromContext(info.GetIsolate()->GetCurrentContext())->GetScriptObject(info.This())->GetObject();
}
