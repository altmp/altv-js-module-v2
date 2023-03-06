#pragma once

#include "v8-persistent-handle.h"
#include "Convert.h"

namespace js
{
    template<typename T>
    using Persistent = v8::Persistent<T, v8::CopyablePersistentTraits<T>>;

    class Object
    {
        v8::Local<v8::Context> context;
        v8::Local<v8::Object> object;

    public:
        Object() : object(v8::Object::New(v8::Isolate::GetCurrent())), context(v8::Isolate::GetCurrent()->GetEnteredOrMicrotaskContext()) {}
        Object(v8::Local<v8::Object> _object) : object(_object), context(v8::Isolate::GetCurrent()->GetEnteredOrMicrotaskContext()) {}
        Object(const std::initializer_list<std::pair<std::string, v8::Local<v8::Value>>>& list) : context(v8::Isolate::GetCurrent()->GetEnteredOrMicrotaskContext())
        {
            object = v8::Object::New(v8::Isolate::GetCurrent());
            for(auto& val : list)
            {
                Set(val.first, val.second);
            }
        }

        v8::Local<v8::Object> Get() const
        {
            return object;
        }

        template<typename T>
        void Set(const std::string& key, T& val)
        {
            object->Set(context, js::JSValue(key), js::JSValue(val));
        }
    };
}  // namespace js
