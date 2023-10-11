#pragma once

#include <unordered_map>

#include "cpp-sdk/SDK.h"

#include "ScriptObject.h"

namespace js
{
    class Class;

    class IScriptObjectHandler
    {
        using ObjectIdentifier = uint64_t;

        std::unordered_map<ObjectIdentifier, ScriptObject*> objectMap;
        std::unordered_map<alt::IBaseObject::Type, Persistent<v8::Function>> customFactoryMap;

        ObjectIdentifier GetObjectIdentifier(alt::IBaseObject* object);

        static std::unordered_map<alt::IBaseObject::Type, Class*>& GetClassMap()
        {
            static std::unordered_map<alt::IBaseObject::Type, Class*> classMap;
            return classMap;
        }

        static Class* GetClassForType(alt::IBaseObject::Type type)
        {
            if(!GetClassMap().contains(type)) return nullptr;
            return GetClassMap().at(type);
        }

    protected:
        void Reset()
        {
            for(auto& [_, scriptObject] : objectMap) ScriptObject::Destroy(scriptObject);
            objectMap.clear();
            customFactoryMap.clear();
        }

    public:
        IScriptObjectHandler() = default;

        ScriptObject* GetOrCreateScriptObject(v8::Local<v8::Context> context, alt::IBaseObject* object);
        void DestroyScriptObject(alt::IBaseObject* object);

        ScriptObject* GetScriptObject(alt::IBaseObject* object);
        ScriptObject* GetScriptObject(v8::Local<v8::Value> value)
        {
            if(!value->IsObject()) return nullptr;
            v8::Local<v8::Object> object = value.As<v8::Object>();
            return ScriptObject::Get(object);
        }

        void SetCustomFactory(alt::IBaseObject::Type type, v8::Local<v8::Function> factory)
        {
            customFactoryMap[type] = Persistent<v8::Function>(factory->GetIsolate(), factory);
        }
        v8::Local<v8::Function> GetCustomFactory(alt::IBaseObject::Type type)
        {
            return customFactoryMap.at(type).Get(v8::Isolate::GetCurrent());
        }
        bool HasCustomFactory(alt::IBaseObject::Type type)
        {
            return customFactoryMap.contains(type);
        }

        static void BindClassToType(alt::IBaseObject::Type type, Class* class_);
    };
}  // namespace js
