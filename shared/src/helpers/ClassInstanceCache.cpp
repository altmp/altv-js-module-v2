#include "ClassInstanceCache.h"
#include "interfaces/IResource.h"

v8::Local<v8::Object> js::ClassInstanceCache::GetOrCreate(IResource* resource, Identifier identifier, v8::Local<v8::Value> internalFieldValue)
{
    if(instanceMap[resource].contains(identifier)) return Get(resource, identifier);

    if(internalFieldValue.IsEmpty()) internalFieldValue = js::JSValue(identifier);
    v8::Local<v8::Object> instance = class_->Create(resource->GetContext(), internalFieldValue);
    Add(resource, identifier, instance);
    return instance;
}
