#pragma once

#include "v8-persistent-handle.h"
#include "Convert.h"
#include "Type.h"

namespace js
{
    template<typename T>
    using Persistent = v8::Persistent<T, v8::CopyablePersistentTraits<T>>;

    class IResource;

    static void Throw(const std::string& message)
    {
        v8::Isolate::GetCurrent()->ThrowException(v8::Exception::Error(js::JSValue(message)));
    }

    class TryCatch
    {
        v8::TryCatch tryCatch;

        void PrintError();

    public:
        TryCatch() : tryCatch(v8::Isolate::GetCurrent()) {}
        TryCatch(v8::Isolate* isolate) : tryCatch(isolate) {}

        bool Check(bool printError = true)
        {
            if(tryCatch.HasCaught())
            {
                if(printError) PrintError();
                tryCatch.Reset();
                return true;
            }
            return false;
        }
        void ReThrow()
        {
            tryCatch.ReThrow();
        }
    };

    class Value
    {
        bool valid = true;

    protected:
        v8::Local<v8::Context> context;
        IResource* resource = nullptr;

        Value(bool _valid, v8::Local<v8::Context> _context = v8::Isolate::GetCurrent()->GetEnteredOrMicrotaskContext()) : valid(_valid), context(_context) {}

    public:
        bool IsValid() const
        {
            return valid;
        }

        v8::Local<v8::Context> GetContext() const
        {
            return context;
        }

        IResource* GetResource();
    };

    class Object : public Value
    {
    public:
        using V8Type = v8::Object;

    private:
        v8::Local<v8::Object> object;
        std::unordered_map<std::string, js::Type> typeCache;

    public:
        Object() : Value(true), object(v8::Object::New(v8::Isolate::GetCurrent())) {}
        Object(v8::Local<v8::Object> _object) : Value(!_object.IsEmpty()), object(_object) {}
        Object(const std::initializer_list<std::pair<std::string, v8::Local<v8::Value>>>& list) : Value(true)
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
            using Type = std::conditional_t<std::is_enum_v<T>, int, T>;
            static_assert(IsJSValueConvertible<Type>, "Type is not convertible to JS value");
            object->Set(context, js::JSValue(key), js::JSValue((Type)val));
        }

        // Falls back to default value if the value is not found or the type doesn't match
        template<typename T>
        T Get(const std::string& key, const T& defaultValue = T()) const
        {
            using Type = std::conditional_t<std::is_enum_v<T>, int, T>;
            v8::MaybeLocal<v8::Value> maybeVal = object->Get(context, js::JSValue(key));
            v8::Local<v8::Value> val;
            if(!maybeVal.ToLocal(&val)) return defaultValue;
            std::optional<Type> result = js::CppValue<Type>(val);
            return result.has_value() ? (T)result.value() : defaultValue;
        }

        // Throws an error and returns false if the value is not found or the type doesn't match
        template<typename T>
        bool Get(const std::string& key, T& out)
        {
            using Type = std::conditional_t<std::is_enum_v<T>, int, T>;
            v8::MaybeLocal<v8::Value> maybeVal = object->Get(context, js::JSValue(key));
            v8::Local<v8::Value> val;
            if(!maybeVal.ToLocal(&val))
            {
                Throw("Failed to get property '" + key + "'");
                return false;
            }
            std::optional<Type> result = js::CppValue<Type>(val);
            if(!result.has_value())
            {
                Throw("Failed to get property '" + key + "'");
                return false;
            }
            out = (T)result.value();
            return true;
        }

        bool Has(const std::string& key) const
        {
            return object->HasOwnProperty(context, js::JSValue(key)).FromMaybe(false);
        }

        std::vector<std::string> GetKeys() const
        {
            std::vector<std::string> keys;
            v8::MaybeLocal<v8::Array> maybePropNames = object->GetPropertyNames(GetContext());
            v8::Local<v8::Array> propNames;
            if(!maybePropNames.ToLocal(&propNames)) return keys;
            for(uint32_t i = 0; i < propNames->Length(); i++)
            {
                v8::MaybeLocal<v8::Value> maybeKey = propNames->Get(GetContext(), i);
                v8::Local<v8::Value> key;
                if(!maybeKey.ToLocal(&key)) continue;
                keys.push_back(js::CppValue(key.As<v8::String>()));
            }
            return keys;
        }

        js::Type GetType(const std::string& key);

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
            static_assert(IsJSValueConvertible<T>, "Type is not convertible to JS value");
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

    class Array : public Value
    {
    public:
        using V8Type = v8::Array;

    private:
        v8::Local<v8::Array> array;
        int currentIdx = 0;

    public:
        Array() : Value(true), array(v8::Array::New(v8::Isolate::GetCurrent())) {}
        Array(int size) : Value(true), array(v8::Array::New(v8::Isolate::GetCurrent(), size)) {}
        Array(v8::Local<v8::Array> _array) : Value(!_array.IsEmpty()), array(_array) {}
        Array(const std::initializer_list<v8::Local<v8::Value>>& list) : Value(true)
        {
            array = v8::Array::New(v8::Isolate::GetCurrent(), list.size());
            int i = 0;
            for(auto& val : list) Push(val);
        }

        v8::Local<v8::Array> Get() const
        {
            return array;
        }

        uint32_t Length() const
        {
            return array->Length();
        }

        template<typename T>
        T Get(uint32_t index)
        {
            v8::MaybeLocal<v8::Value> maybeVal = array->Get(context, index);
            v8::Local<v8::Value> val;
            if(!maybeVal.ToLocal(&val)) return T();
            std::optional<T> result = js::CppValue<T>(val);
            return result.has_value() ? result.value() : T();
        }

        template<typename T>
        void Push(const T& val)
        {
            static_assert(IsJSValueConvertible<T>, "Type is not convertible to JS value");
            array->Set(context, currentIdx++, js::JSValue(val));
        }

        template<typename T>
        void Set(uint32_t index, const T& val)
        {
            static_assert(IsJSValueConvertible<T>, "Type is not convertible to JS value");
            array->Set(context, index, js::JSValue(val));
        }
    };

    class Function : public Value
    {
    public:
        using V8Type = v8::Function;

    private:
        v8::Local<v8::Function> function;
        TryCatch tryCatch;

        v8::MaybeLocal<v8::Value> CallNative(v8::Local<v8::Value> thisObj, v8::Local<v8::Value>* argv, int argc)
        {
            v8::MaybeLocal<v8::Value> retVal = function->Call(context, thisObj, argc, argv);
            tryCatch.Check();
            return retVal;
        }

    public:
        Function(v8::Local<v8::Function> _function) : Value(!_function.IsEmpty()), function(_function) {}

        v8::Local<v8::Function> Get() const
        {
            return function;
        }

        template<typename Ret = void>
        std::conditional_t<std::is_same_v<Ret, void>, void, std::optional<Ret>> Call(const std::vector<v8::Local<v8::Value>>& args)
        {
            v8::MaybeLocal<v8::Value> retValue = CallNative(v8::Undefined(context->GetIsolate()), (v8::Local<v8::Value>*)args.data(), args.size());
            if constexpr(std::is_same_v<Ret, void>) return;
            else
            {
                v8::Local<v8::Value> val;
                if(!retValue.ToLocal(&val)) return std::nullopt;
                return js::CppValue<Ret>(val);
            }
        }

        template<typename Ret = void>
        std::conditional_t<std::is_same_v<Ret, void>, void, std::optional<Ret>> Call(const Object& thisObj, const std::vector<v8::Local<v8::Value>>& args)
        {
            v8::MaybeLocal<v8::Value> retValue = CallNative(thisObj.Get(), (v8::Local<v8::Value>*)args.data(), args.size());
            if constexpr(std::is_same_v<Ret, void>) return;
            else
            {
                v8::Local<v8::Value> val;
                if(!retValue.ToLocal(&val)) return std::nullopt;
                return js::CppValue<Ret>(val);
            }
        }

        template<typename Ret = void, typename... Args>
        std::conditional_t<std::is_same_v<Ret, void>, void, std::optional<Ret>> Call(const Args&... args)
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

        template<typename Ret = void, typename... Args>
        std::conditional_t<std::is_same_v<Ret, void>, void, std::optional<Ret>> Call(const Object& thisObj, const Args&... args)
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

    class Promise : public Value
    {
    public:
        using V8Type = v8::Promise::Resolver;

    private:
        Persistent<v8::Promise::Resolver> resolver;

        Promise() : Value(true), resolver(v8::Isolate::GetCurrent(), v8::Promise::Resolver::New(context).ToLocalChecked()) {}

    public:
        v8::Local<v8::Promise::Resolver> Get() const
        {
            return resolver.Get(v8::Isolate::GetCurrent());
        }

        template<typename T>
        void Resolve(const T& value)
        {
            static_assert(IsJSValueConvertible<T>, "Type is not convertible to JS value");
            Get()->Resolve(context, JSValue(value));
        }

        template<typename T>
        void Reject(const T& value)
        {
            static_assert(IsJSValueConvertible<T>, "Type is not convertible to JS value");
            Get()->Reject(context, JSValue(value));
        }

        static std::shared_ptr<Promise> Create()
        {
            // Needed to allow make_shared to access the private ctor
            struct Wrap : public Promise
            {
            };
            return std::make_shared<Wrap>();
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
