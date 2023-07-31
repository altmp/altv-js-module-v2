#pragma once

#include <thread>

#include "v8-persistent-handle.h"

#include "Convert.h"
#include "Type.h"
#include "Callbacks.h"

namespace js
{
    template<typename T>
    using Persistent = v8::Persistent<T, v8::CopyablePersistentTraits<T>>;

    class IResource;

    static void Throw(const std::string& message)
    {
        v8::Isolate::GetCurrent()->ThrowException(v8::Exception::Error(js::JSValue(message)));
    }

    struct SourceLocation
    {
        bool valid = false;
        std::string file;
        int line = 0;

        SourceLocation() = default;
        SourceLocation(const std::string& _file, int _line) : valid(true), file(_file), line(_line) {}

        static SourceLocation GetCurrent(IResource* resource, int framesToSkip = 0);
    };

    class StackTrace
    {
        struct Frame
        {
            std::string file;
            std::string function;
            int line;
        };
        std::vector<Frame> frames;
        Persistent<v8::Context> context;

        StackTrace(const std::vector<Frame>&& frames, v8::Local<v8::Context> ctx);

    public:
        bool IsEmpty()
        {
            return frames.empty();
        }

        std::string ToString(uint32_t offset = 0) const;

        static StackTrace GetCurrent(v8::Isolate* isolate, IResource* resource = nullptr, int framesToSkip = 0);
        static void Print(v8::Isolate* isolate);
    };

    void RunEventLoop();

    class TryCatch
    {
        v8::TryCatch tryCatch;

        void PrintError(bool skipLocation);

    public:
        TryCatch() : tryCatch(v8::Isolate::GetCurrent()) {}
        TryCatch(v8::Isolate* isolate) : tryCatch(isolate) {}

        bool Check(bool printError = true, bool skipLocation = false)
        {
            if(HasCaught())
            {
                if(printError) PrintError(skipLocation);
                tryCatch.Reset();
                return true;
            }
            return false;
        }

        void ReThrow()
        {
            tryCatch.ReThrow();
        }

        bool HasCaught() const
        {
            return tryCatch.HasCaught();
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

    class PersistentValue
    {
        bool valid = true;

    protected:
        v8::Isolate* isolate;
        Persistent<v8::Context> context;

        IResource* resource = nullptr;

        PersistentValue(bool _valid, v8::Local<v8::Context> _context = v8::Isolate::GetCurrent()->GetEnteredOrMicrotaskContext())
            : valid(_valid), isolate(_context->GetIsolate()), context(_context->GetIsolate(), _context)
        {
        }

    public:
        bool IsValid() const
        {
            return valid;
        }

        v8::Isolate* GetIsolate() const
        {
            return isolate;
        }

        v8::Local<v8::Context> GetContext() const
        {
            return context.Get(isolate);
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

        void SetMethod(const std::string& key, FunctionCallback func);

        // Falls back to default value if the value is not found or the type doesn't match
        template<typename T>
        T Get(const std::string& key, const T& defaultValue = T()) const
        {
            v8::MaybeLocal<v8::Value> maybeVal = object->Get(context, js::JSValue(key));
            v8::Local<v8::Value> val;
            if(!maybeVal.ToLocal(&val)) return defaultValue;
            std::optional<T> result = js::CppValue<T>(val);
            return result.has_value() ? (T)result.value() : defaultValue;
        }

        // Throws an error and returns false if the value is not found or the type doesn't match
        template<typename T>
        bool Get(const std::string& key, T& out, bool throwOnError = true)
        {
            using Type = std::conditional_t<std::is_enum_v<T>, int, T>;
            v8::MaybeLocal<v8::Value> maybeVal = object->Get(context, js::JSValue(key));
            v8::Local<v8::Value> val;
            if(!maybeVal.ToLocal(&val))
            {
                if(throwOnError) Throw("Failed to get property '" + key + "', value not found");
                return false;
            }
            std::optional<Type> result = js::CppValue<Type>(val);
            if(!result.has_value())
            {
                if(throwOnError) Throw("Failed to get property '" + key + "', invalid type");
                return false;
            }
            out = (T)result.value();
            return true;
        }

        bool GetAsHash(const std::string& key, uint32_t& outValue)
        {
            Type argType = GetType(key);
            if(argType == Type::STRING)
            {
                std::string val = Get<std::string>(key);
                outValue = alt::ICore::Instance().Hash(val);
                return true;
            }
            else if(argType == Type::NUMBER)
            {
                uint32_t val = Get<uint32_t>(key);
                outValue = val;
                return true;
            }
            Throw("Invalid property type at key " + key + ", expected string or number but got " + TypeToString(argType));
            return false;
        }

        bool Has(const std::string& key) const
        {
            return object->HasOwnProperty(context, js::JSValue(key)).FromMaybe(false);
        }

        std::vector<std::string> GetKeys() const
        {
            std::vector<std::string> keys;
            v8::MaybeLocal<v8::Array> maybePropNames = object->GetPropertyNames(GetContext(),
                                                                                v8::KeyCollectionMode::kOwnOnly,
                                                                                (v8::PropertyFilter)(v8::PropertyFilter::ONLY_ENUMERABLE | v8::PropertyFilter::SKIP_SYMBOLS),
                                                                                v8::IndexFilter::kSkipIndices,
                                                                                v8::KeyConversionMode::kConvertToString);
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

        template<typename T>
        std::unordered_map<std::string, T> ToMap()
        {
            std::unordered_map<std::string, T> map;
            for(const std::string& key : GetKeys())
            {
                T val;
                if(Get(key, val, false)) map.insert({ key, val });
            }
            return map;
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
            static_assert(IsJSValueConvertible<T>, "Type is not convertible to JS value");
            if(configurable && writable && enumerable) object->CreateDataProperty(context, js::JSValue(key), js::JSValue(val));
            else
            {
                int attr = (int)v8::PropertyAttribute::None;
                if(!configurable) attr |= (int)v8::PropertyAttribute::DontDelete;
                if(!writable) attr |= (int)v8::PropertyAttribute::ReadOnly;
                if(!enumerable) attr |= (int)v8::PropertyAttribute::DontEnum;
                object->DefineOwnProperty(context, js::JSValue(key), js::JSValue(val), (v8::PropertyAttribute)attr);
            }
        }

        void Freeze()
        {
            object->SetIntegrityLevel(context, v8::IntegrityLevel::kFrozen);
        }

        void Seal()
        {
            object->SetIntegrityLevel(context, v8::IntegrityLevel::kSealed);
        }

        template<class T>
        T* GetExtraInternalFieldValue()
        {
            if(Get()->InternalFieldCount() != 2) return nullptr;
            return static_cast<T*>(Get()->GetAlignedPointerFromInternalField(1));
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
        T Get(uint32_t index, const T& defaultValue = T())
        {
            v8::MaybeLocal<v8::Value> maybeVal = array->Get(context, index);
            v8::Local<v8::Value> val;
            if(!maybeVal.ToLocal(&val)) return defaultValue;
            std::optional<T> result = js::CppValue<T>(val);
            return result.has_value() ? result.value() : defaultValue;
        }

        template<typename T>
        bool Get(uint32_t index, T& out, bool throwOnError = true)
        {
            v8::MaybeLocal<v8::Value> maybeVal = array->Get(context, index);
            v8::Local<v8::Value> val;
            if(!maybeVal.ToLocal(&val))
            {
                if(throwOnError) Throw("Failed to get array value at index " + std::to_string(index) + ", invalid index");
                return false;
            }
            std::optional<T> result = js::CppValue<T>(val);
            if(!result.has_value())
            {
                if(throwOnError) Throw("Failed to get array value at index " + std::to_string(index) + ", invalid type");
                return false;
            }
            out = result.value();
            return true;
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
            v8::MaybeLocal<v8::Value> retValue;
            if constexpr(sizeof...(args) == 0)
            {
                retValue = CallNative(v8::Undefined(context->GetIsolate()), nullptr, 0);
            }
            else
            {
                v8::Local<v8::Value> argv[] = { js::JSValue(args)... };
                retValue = CallNative(v8::Undefined(context->GetIsolate()), argv, sizeof...(args));
            }
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
            v8::MaybeLocal<v8::Value> retValue;
            if constexpr(sizeof...(args) == 0)
            {
                retValue = CallNative(thisObj.Get(), nullptr, 0);
            }
            else
            {
                v8::Local<v8::Value> argv[] = { js::JSValue(args)... };
                retValue = CallNative(thisObj.Get(), argv, sizeof...(args));
            }
            if constexpr(std::is_same_v<Ret, void>) return;
            else
            {
                v8::Local<v8::Value> val;
                if(!retValue.ToLocal(&val)) return std::nullopt;
                return js::CppValue<Ret>(val);
            }
        }
    };

    class Promise : public PersistentValue
    {
    public:
        using V8Type = v8::Promise::Resolver;

    private:
        Persistent<v8::Promise::Resolver> resolver;
        Persistent<v8::Promise> promise;
        Type resultType = Type::INVALID;

    public:
        Promise() : PersistentValue(true), resolver(v8::Isolate::GetCurrent(), v8::Promise::Resolver::New(GetContext()).ToLocalChecked()) {}
        Promise(v8::Local<v8::Promise> _promise) : PersistentValue(!_promise.IsEmpty()), promise(v8::Isolate::GetCurrent(), _promise) {}

        v8::Local<v8::Promise> Get()
        {
            if(!HasPromise() && HasResolver()) promise.Reset(v8::Isolate::GetCurrent(), GetResolver()->GetPromise());
            return promise.Get(v8::Isolate::GetCurrent());
        }

        v8::Local<v8::Promise::Resolver> GetResolver() const
        {
            return resolver.Get(v8::Isolate::GetCurrent());
        }

        bool HasResolver() const
        {
            return !resolver.IsEmpty();
        }
        bool HasPromise() const
        {
            return !promise.IsEmpty();
        }

        v8::Promise::PromiseState State()
        {
            return Get()->State();
        }

        template<typename T>
        T GetResult(const T& defaultValue = T())
        {
            if(State() == v8::Promise::PromiseState::kPending) return defaultValue;
            v8::Local<v8::Value> val = Get()->Result();
            std::optional<T> result = js::CppValue<T>(val);
            return result.has_value() ? result.value() : defaultValue;
        }

        template<typename T>
        bool GetResult(T& out, bool throwOnError = true)
        {
            if(State() == v8::Promise::PromiseState::kPending)
            {
                if(throwOnError) Throw("Promise is still pending");
                return false;
            }
            v8::Local<v8::Value> val = Get()->Result();
            std::optional<T> result = js::CppValue<T>(val);
            if(!result.has_value())
            {
                if(throwOnError) Throw("Failed to get promise result, expected " + CppTypeToString<T>() + " but got " + TypeToString(GetResultType()));
                return false;
            }
            out = result.value();
            return true;
        }

        Type GetResultType()
        {
            if(Get()->State() == v8::Promise::PromiseState::kPending) return Type::INVALID;
            if(resultType == Type::INVALID)
            {
                v8::Local<v8::Value> val = Get()->Result();
                resultType = GetType(val, GetResource());
            }
            return resultType;
        }

        bool Await()
        {
            v8::Local<v8::Promise> promise = Get();
            while(true)
            {
                v8::Promise::PromiseState state = promise->State();
                switch(state)
                {
                    case v8::Promise::PromiseState::kPending: RunEventLoop(); break;
                    case v8::Promise::PromiseState::kFulfilled: return true;
                    case v8::Promise::PromiseState::kRejected: return false;
                }
                std::this_thread::sleep_for(std::chrono::milliseconds(1));
            }
        }

        template<typename T>
        void Resolve(const T& value)
        {
            static_assert(IsJSValueConvertible<T>, "Type is not convertible to JS value");
            if(!HasResolver()) return;
            GetResolver()->Resolve(GetContext(), JSValue(value));
        }

        template<typename T>
        void Reject(const T& value)
        {
            static_assert(IsJSValueConvertible<T>, "Type is not convertible to JS value");
            if(!HasResolver()) return;
            GetResolver()->Reject(GetContext(), JSValue(value));
        }

        static std::shared_ptr<Promise> Create()
        {
            return std::make_shared<Promise>();
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
        TemporaryGlobalExtension(v8::Local<v8::Context> _ctx, const std::string& _name, FunctionCallback _callback);
        ~TemporaryGlobalExtension()
        {
            ctx->Global()->Delete(ctx, js::JSValue(name));
        }
    };

    class ExternalString : public v8::String::ExternalOneByteStringResource
    {
        const char* str;
        size_t size;

    public:
        explicit ExternalString(const char* _str, size_t _size) : str(_str), size(_size) {}
        ExternalString() : str(nullptr), size(0) {}

        ExternalString(const ExternalString&) = delete;
        ExternalString& operator=(const ExternalString&) = delete;

        const char* data() const override
        {
            return str;
        }
        size_t length() const override
        {
            return size;
        }

        void Dispose() override
        {
            // We should only do this for "eternal" strings that never get deleted,
            // so don't do anything here
        }
    };
}  // namespace js
