#include "IScriptObjectHandler.h"
#include "Class.h"
#include "Logger.h"

js::ScriptObject* js::IScriptObjectHandler::GetOrCreateScriptObject(v8::Local<v8::Context> context, alt::IBaseObject* object)
{
    js::ScriptObject* existingObject = GetScriptObject(object);
    if(existingObject) return existingObject;

    Class* class_ = GetClassForType(object->GetType());
    if(!class_)
    {
        Logger::Error("Class not found for type", (int)object->GetType());
        return nullptr;
    }
    ScriptObject* scriptObject = ScriptObject::Create(context, object, class_);
    objectMap.insert({ object->GetType(), scriptObject });
    return scriptObject;
}

void js::IScriptObjectHandler::DestroyScriptObject(alt::IBaseObject* object)
{
    auto range = objectMap.equal_range(object->GetType());
    for(auto it = range.first; it != range.second; ++it)
    {
        if(it->second->GetObject() == object)
        {
            objectMap.erase(it);
            ScriptObject::Destroy(it->second);
            break;
        }
    }
}

void js::IScriptObjectHandler::BindScriptObject(v8::Local<v8::Object> thisObject, alt::IBaseObject* object)
{
    Class* objectClass = GetClassForType(object->GetType());
    if(!objectClass) return;
    ScriptObject* scriptObject = ScriptObject::Create(thisObject, object, objectClass);
    objectMap.insert({ object->GetType(), scriptObject });
}

void js::IScriptObjectHandler::BindClassToType(alt::IBaseObject::Type type, Class* class_)
{
    GetClassMap().insert({ type, class_ });
    class_->SetInternalFieldCount(1);
}
