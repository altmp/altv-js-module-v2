#include "Type.h"
#include "interfaces/IResource.h"

bool js::IsVector3(v8::Local<v8::Value> value, IResource* resource)
{
    return resource->IsVector3(value);
}

bool js::IsVector2(v8::Local<v8::Value> value, IResource* resource)
{
    return resource->IsVector2(value);
}

bool js::IsRGBA(v8::Local<v8::Value> value, IResource* resource)
{
    return resource->IsRGBA(value);
}

bool js::IsQuaternion(v8::Local<v8::Value> value, IResource* resource)
{
    return resource->IsQuaternion(value);
}

bool js::IsBaseObject(v8::Local<v8::Value> value, IResource* resource)
{
    return resource->IsBaseObject(value);
}
