#include "FunctionContext.h"
#include "interfaces/IResource.h"

alt::IBaseObject* js::FunctionContext::GetThisObjectUntyped()
{
    if(errored) return nullptr;
    return GetResource()->GetScriptObject(info.This())->GetObject();
}

js::IResource* js::FunctionContext::GetResource()
{
    if(!resource) resource = IResource::GetFromContext(info.GetIsolate()->GetCurrentContext());
    return resource;
}

void js::FunctionContext::SetThisObject(alt::IBaseObject* object)
{
    if(!object) return;
    IResource* resource = GetResource();
    resource->BindScriptObject(info.This(), object);
}
