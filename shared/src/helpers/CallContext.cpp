#include "CallContext.h"
#include "interfaces/IResource.h"

void js::FunctionContext::SetThisObject(alt::IBaseObject* object)
{
    if(!object) return;
    IResource* resource = GetResource();
    resource->BindScriptObject(info.This(), object);

    js::Function func = resource->GetBindingExport<js::Function>("entity:addEntityToAll");
    if(!func.IsValid()) return;
    func.Call(info.This());
}
