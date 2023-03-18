#include "JS.h"
#include "interfaces/IResource.h"

js::IResource* js::Value::GetResource()
{
    if(!resource) resource = IResource::GetFromContext(GetContext());
    return resource;
}

js::Type js::Object::GetType(const std::string& key)
{
    if(typeCache.contains(key)) return typeCache.at(key);
    v8::MaybeLocal<v8::Value> maybeVal = object->Get(context, js::JSValue(key));
    v8::Local<v8::Value> val;
    if(!maybeVal.ToLocal(&val)) return js::Type::INVALID;
    js::Type type = js::GetType(val, GetResource());
    typeCache.insert({ key, type });
    return type;
}
