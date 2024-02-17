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

    js::Object scriptObjectObj = scriptObject->Get();
    if(scriptObjectObj.GetType("onCreate") == js::Type::FUNCTION)
    {
        js::Function onCreateFunc = scriptObjectObj.Get<v8::Local<v8::Value>>("onCreate").As<v8::Function>();
        onCreateFunc.Call(scriptObjectObj);
    }

    objectMap.insert({ object, scriptObject });
    return scriptObject;
}

void js::IScriptObjectHandler::DestroyScriptObject(alt::IBaseObject* object)
{
    auto it = objectMap.find(object);
    if(it == objectMap.end()) return;
    ScriptObject::Destroy(it->second);
    objectMap.erase(it);
}

js::ScriptObject* js::IScriptObjectHandler::GetScriptObject(alt::IBaseObject* object)
{
    auto it = objectMap.find(object);
    if(it == objectMap.end()) return nullptr;
    return it->second;
}

void js::IScriptObjectHandler::BindClassToType(alt::IBaseObject::Type type, Class* class_)
{
    GetClassMap().insert({ type, class_ });
    class_->SetInternalFieldCount(1);
}
