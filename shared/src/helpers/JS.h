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
        void Set(const std::string& key, const T& val)
        {
            object->Set(context, js::JSValue(key), js::JSValue(val));
        }

        template<typename T>
        T Get(const std::string& key) const
        {
            v8::MaybeLocal<v8::Value> maybeVal = object->Get(context, js::JSValue(key));
            v8::Local<v8::Value> val;
            if(!maybeVal.ToLocal(&val)) return T();
            std::optional<T> result = js::CppValue<T>(val);
            return result.has_value() ? result.value() : T();
        }

        void SetAccessor(const std::string& key, v8::AccessorNameGetterCallback getter, v8::AccessorNameSetterCallback setter = nullptr, void* data = nullptr)
        {
            object->SetAccessor(context,
                                js::JSValue(key),
                                getter,
                                setter,
                                data ? v8::External::New(context->GetIsolate(), data) : v8::MaybeLocal<v8::Value>(),
                                v8::DEFAULT,
                                setter != nullptr ? v8::PropertyAttribute::None : v8::PropertyAttribute::ReadOnly);
        }

        template<typename T>
        void SetProperty(const std::string& key, const T& val, bool configurable = true, bool writable = true, bool enumerable = true)
        {
            if(configurable && writable && enumerable) object->CreateDataProperty(context, js::JSValue(key), js::JSValue(val));
            else
            {
                v8::PropertyAttribute attr = v8::None;
                if(!configurable) attr |= v8::PropertyAttribute::DontDelete;
                if(!writable) attr |= v8::PropertyAttribute::ReadOnly;
                if(!enumerable) attr |= v8::PropertyAttribute::DontEnum;
                object->DefineOwnProperty(context, js::JSValue(key), attr);
            }
        }
    };

    class Array
    {
        v8::Local<v8::Context> context;
        v8::Local<v8::Array> array;
        int currentIdx = 0;

    public:
        Array() : array(v8::Array::New(v8::Isolate::GetCurrent())), context(v8::Isolate::GetCurrent()->GetEnteredOrMicrotaskContext()) {}
        Array(int size) : array(v8::Array::New(v8::Isolate::GetCurrent(), size)), context(v8::Isolate::GetCurrent()->GetEnteredOrMicrotaskContext()) {}
        Array(v8::Local<v8::Array> _array) : array(_array), context(v8::Isolate::GetCurrent()->GetEnteredOrMicrotaskContext()) {}
        Array(const std::initializer_list<v8::Local<v8::Value>>& list) : context(v8::Isolate::GetCurrent()->GetEnteredOrMicrotaskContext())
        {
            array = v8::Array::New(v8::Isolate::GetCurrent(), list.size());
            int i = 0;
            for(auto& val : list) Push(val);
        }

        v8::Local<v8::Array> Get() const
        {
            return array;
        }

        template<typename T>
        void Push(const T& val)
        {
            array->Set(context, currentIdx++, js::JSValue(val));
        }

        template<typename T>
        void Set(int index, const T& val)
        {
            array->Set(context, index, js::JSValue(val));
        }
    };

    struct TemporaryGlobalExtension
    {
        std::string name;
        v8::Local<v8::Context> ctx;

        TemporaryGlobalExtension(v8::Local<v8::Context> _ctx, const std::string& _name, v8::Local<v8::Value> value) : ctx(_ctx), name(_name)
        {
            ctx->Global()->Set(ctx, js::JSValue(_name), value);
        }
        ~TemporaryGlobalExtension()
        {
            ctx->Global()->Delete(ctx, js::JSValue(name));
        }
    };
}  // namespace js
