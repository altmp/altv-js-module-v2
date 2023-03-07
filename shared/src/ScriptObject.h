#pragma once

#include <unordered_map>

#include "v8.h"
#include "cpp-sdk/ICore.h"

#include "helpers/JS.h"

namespace js
{
    class Class;
    class IScriptObjectHandler;

    class ScriptObject
    {
        friend class IScriptObjectHandler;

        v8::Isolate* isolate;
        Persistent<v8::Object> jsObject;
        alt::IBaseObject* object = nullptr;

        ScriptObject(v8::Isolate* _isolate, v8::Local<v8::Object> _jsObject, alt::IBaseObject* _object) : isolate(_isolate), jsObject(_isolate, _jsObject), object(_object) {}
        static ScriptObject* Create(v8::Local<v8::Context> context, alt::IBaseObject* object, Class* class_);
        static ScriptObject* Create(v8::Local<v8::Object> jsObject, alt::IBaseObject* object);
        static void Destroy(ScriptObject* scriptObject);

    public:
        v8::Local<v8::Object> Get() const
        {
            return jsObject.Get(isolate);
        }
        alt::IBaseObject* GetObject() const
        {
            return object;
        }

        v8::Isolate* GetIsolate() const
        {
            return isolate;
        }
    };
}  // namespace js
