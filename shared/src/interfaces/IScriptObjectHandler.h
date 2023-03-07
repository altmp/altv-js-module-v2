#pragma once

#include <unordered_map>

#include "cpp-sdk/SDK.h"

#include "ScriptObject.h"

namespace js
{
    class Class;

    class IScriptObjectHandler
    {
        std::unordered_multimap<alt::IBaseObject::Type, ScriptObject*>& GetObjectMap()
        {
            static std::unordered_multimap<alt::IBaseObject::Type, ScriptObject*> objectMap;
            return objectMap;
        }

        static std::unordered_map<alt::IBaseObject::Type, Class*>& GetClassMap()
        {
            static std::unordered_map<alt::IBaseObject::Type, Class*> classMap;
            return classMap;
        }

        static Class* GetClassForType(alt::IBaseObject::Type type)
        {
            return GetClassMap().at(type);
        }

    public:
        IScriptObjectHandler() = default;

        ScriptObject* CreateScriptObject(v8::Local<v8::Context> context, alt::IBaseObject* object);
        void DestroyScriptObject(alt::IBaseObject* object);
        void BindScriptObject(v8::Local<v8::Object> thisObject, alt::IBaseObject* object);

        ScriptObject* GetScriptObject(alt::IBaseObject* object)
        {
            auto range = GetObjectMap().equal_range(object->GetType());
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

        static void BindClassToType(alt::IBaseObject::Type type, Class* class_);
    };
}  // namespace js
