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
                int attr = (int)v8::PropertyAttribute::None;
                if(!configurable) attr |= (int)v8::PropertyAttribute::DontDelete;
                if(!writable) attr |= (int)v8::PropertyAttribute::ReadOnly;
                if(!enumerable) attr |= (int)v8::PropertyAttribute::DontEnum;
                object->DefineOwnProperty(context, js::JSValue(key), (v8::PropertyAttribute)attr);
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

    class Function
    {
        v8::Local<v8::Context> context;
        v8::Local<v8::Function> function;

        v8::MaybeLocal<v8::Value> CallNative(v8::Local<v8::Value> thisObj, v8::Local<v8::Value>* argv, int argc)
        {
            // todo: try/catch
            return function->Call(context, thisObj, argc, argv);
        }

    public:
        Function() : context(v8::Isolate::GetCurrent()->GetEnteredOrMicrotaskContext()) {}
        Function(v8::Local<v8::Function> _function) : function(_function), context(v8::Isolate::GetCurrent()->GetEnteredOrMicrotaskContext()) {}

        v8::Local<v8::Function> Get() const
        {
            return function;
        }

        template<typename Ret>
        std::optional<Ret> Call(const std::vector<v8::Local<v8::Value>>& args)
        {
            v8::MaybeLocal<v8::Value> retValue = CallNative(v8::Undefined(context->GetIsolate()), (v8::Local<v8::Value>*)args.data(), args.size());
            if constexpr(std::is_same_v<Ret, void>) return std::nullopt;
            else
            {
                v8::Local<v8::Value> val;
                if(!retValue.ToLocal(&val)) return std::nullopt;
                return js::CppValue<Ret>(val);
            }
        }

        template<typename Ret>
        std::optional<Ret> Call(const Object& thisObj, const std::vector<v8::Local<v8::Value>>& args)
        {
            v8::MaybeLocal<v8::Value> retValue = CallNative(thisObj.Get(), (v8::Local<v8::Value>*)args.data(), args.size());
            if constexpr(std::is_same_v<Ret, void>) return std::nullopt;
            else
            {
                v8::Local<v8::Value> val;
                if(!retValue.ToLocal(&val)) return std::nullopt;
                return js::CppValue<Ret>(val);
            }
        }

        template<typename Ret, typename... Args>
        std::optional<Ret> Call(const Args&... args)
        {
            v8::Local<v8::Value> argv[] = { js::JSValue(args)... };
            v8::MaybeLocal<v8::Value> retValue = CallNative(v8::Undefined(context->GetIsolate()), argv, sizeof...(args));
            if constexpr(std::is_same_v<Ret, void>) return;
            else
            {
                v8::Local<v8::Value> val;
                if(!retValue.ToLocal(&val)) return std::nullopt;
                return js::CppValue<Ret>(val);
            }
        }

        template<typename Ret, typename... Args>
        std::optional<Ret> Call(const Object& thisObj, const Args&... args)
        {
            v8::Local<v8::Value> argv[] = { js::JSValue(args)... };
            v8::MaybeLocal<v8::Value> retValue = CallNative(thisObj.Get(), argv, sizeof...(args));
            if constexpr(std::is_same_v<Ret, void>) return;
            else
            {
                v8::Local<v8::Value> val;
                if(!retValue.ToLocal(&val)) return std::nullopt;
                return js::CppValue<Ret>(val);
            }
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
