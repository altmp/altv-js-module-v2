#include "IScriptObjectHandler.h"
#include "Class.h"
#include "Logger.h"

js::ScriptObject* js::IScriptObjectHandler::GetOrCreateScriptObject(v8::Local<v8::Context> context, alt::IBaseObject* object)
{
    js::ScriptObject* existingObject = GetScriptObject(object);
    if(existingObject) return existingObject;

    ScriptObject* scriptObject = nullptr;

    Class* class_ = GetClassForType(object->GetType());
    if(!class_)
    {
        Logger::Error("Class not found for type", (int)object->GetType());
        return nullptr;
    }

    if(HasCustomFactory(object->GetType()))
    {
        v8::Local<v8::Function> factory = GetCustomFactory(object->GetType());
        scriptObject = ScriptObject::Create(context, object, factory, class_);
    }
    else
        scriptObject = ScriptObject::Create(context, object, class_);

    if(!scriptObject)
    {
        Logger::Error("Failed to create script object for type", (int)object->GetType());
        return nullptr;
    }

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

void js::IScriptObjectHandler::BindClassToType(alt::IBaseObject::Type type, Class* class_)
{
    GetClassMap().insert({ type, class_ });
    class_->SetInternalFieldCount(1);
}
