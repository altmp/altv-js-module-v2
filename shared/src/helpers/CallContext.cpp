#include "CallContext.h"
#include "interfaces/IResource.h"

void js::FunctionContext::SetThisObject(alt::IBaseObject* object)
{
    if(!object) return;
    IResource* resource = GetResource();
    resource->BindScriptObject(info.This(), object);
}
