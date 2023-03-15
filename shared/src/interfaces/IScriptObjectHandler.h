#pragma once

#include <unordered_map>

#include "cpp-sdk/SDK.h"

#include "ScriptObject.h"

namespace js
{
    class Class;

    class IScriptObjectHandler
    {
        std::unordered_multimap<alt::IBaseObject::Type, ScriptObject*> objectMap;
        std::unordered_map<alt::IBaseObject::Type, Persistent<v8::Function>> customFactoryMap;

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

    public:
        IScriptObjectHandler() = default;

        ScriptObject* GetOrCreateScriptObject(v8::Local<v8::Context> context, alt::IBaseObject* object);
        void DestroyScriptObject(alt::IBaseObject* object);

        ScriptObject* GetScriptObject(alt::IBaseObject* object)
        {
            auto range = objectMap.equal_range(object->GetType());
            for(auto it = range.first; it != range.second; ++it)
            {
                if(it->second->GetObject() == object)
                {
                    return it->second;
                }
            }
            return nullptr;
        }
        ScriptObject* GetScriptObject(v8::Local<v8::Value> value)
        {
            if(!value->IsObject()) return nullptr;
            v8::Local<v8::Object> object = value.As<v8::Object>();
            return ScriptObject::Get(object);
        }

        void SetCustomFactory(alt::IBaseObject::Type type, v8::Local<v8::Function> factory)
        {
            customFactoryMap.insert({ type, Persistent<v8::Function>(v8::Isolate::GetCurrent(), factory) });
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
