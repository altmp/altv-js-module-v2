#pragma once

#include "v8.h"
#include "cpp-sdk/SDK.h"

#include "Convert.h"
#include "Logger.h"
#include "Type.h"

namespace js
{
    class IResource;

    static void Throw(const std::string& message);

    template<class CallbackInfo>
    class CallContext
    {
    protected:
        CallbackInfo info;
        bool errored = false;
        std::string error;
        bool noThrow = false;
        mutable IResource* resource = nullptr;

        alt::IBaseObject* GetThisObjectUntyped()
        {
            if(errored) return nullptr;
            std::optional<alt::IBaseObject*> object = CppValue<alt::IBaseObject*>(info.This());
            if(!object.has_value()) return nullptr;
            return object.value();
        }

        IResource* GetResourceCached() const
        {
            if(resource) return resource;
            resource = GetCurrentResource(info.GetIsolate());
            return resource;
        }

    public:
        CallContext(const CallbackInfo& _info) : info(_info) {}

        v8::Isolate* GetIsolate() const
        {
            return info.GetIsolate();
        }

        template<class ResourceType = js::IResource>
        ResourceType* GetResource() const
        {
            return static_cast<ResourceType*>(GetResourceCached());
        }

        v8::Local<v8::Context> GetContext() const
        {
            return GetIsolate()->GetCurrentContext();
        }

        const std::string& GetError()
        {
            return error;
        }

        bool Errored() const
        {
            return errored;
        }

        // Don't throw a JS exception if a check fails
        // Make sure to manually check for errors when using this
        void MarkAsNoThrow()
        {
            noThrow = true;
        }

        void Throw(const std::string& message)
        {
            if(!noThrow) js::Throw(message);
            error = message;
            errored = true;
        }

        bool Check(bool condition, const std::string& message)
        {
            if(!condition)
            {
                Throw(message);
                return false;
            }
            return true;
        }

        bool CheckThis()
        {
            return Check(GetThisObjectUntyped() != nullptr, "Invalid base object");
        }

        bool CheckExtraInternalFieldValue()
        {
            return Check(GetExtraInternalFieldValue<void*>() != nullptr, "Invalid extra internal field value");
        }

        bool CheckExtraInternalFieldJSValue()
        {
            return Check(!info.This()->GetInternalField(1)->IsNullOrUndefined(), "Invalid extra internal field value");
        }

        v8::Local<v8::Object> GetThis()
        {
            return info.This();
        }

        template<class T>
        T* GetThisObject()
        {
            if(errored) return nullptr;
            return dynamic_cast<T*>(GetThisObjectUntyped());
        }

        template<class T>
        T* GetExtraInternalFieldValue()
        {
            if(errored) return nullptr;
            if(info.This()->InternalFieldCount() != 2) return nullptr;
            return static_cast<T*>(info.This()->GetAlignedPointerFromInternalField(1));
        }

        template<typename T>
        T GetExtraInternalFieldJSValue()
        {
            if(errored) return {};
            if(info.This()->InternalFieldCount() != 2) return {};
            std::optional<T> value = CppValue<T>(info.This()->GetInternalField(1));
            if(!value.has_value()) return T{};
            return value.value();
        }

        void SetExtraInternalFieldValue(void* value)
        {
            if(errored) return;
            if(info.This()->InternalFieldCount() != 2) return;
            info.This()->SetAlignedPointerInInternalField(1, value);
        }

        template<typename T>
        void SetExtraInternalFieldJSValue(const T& value)
        {
            static_assert(IsJSValueConvertible<T>, "Type is not convertible to JS value");
            if(errored) return;
            if(info.This()->InternalFieldCount() != 2) return;
            info.This()->SetInternalField(1, JSValue(value));
        }

        template<class T>
        void Return(const T& value)
        {
            using Type = std::conditional_t<std::is_enum_v<T>, int, T>;

            if(errored) return;

            // Convert 64-bit integers to BigInt
            if constexpr(std::is_same_v<Type, int64_t> || std::is_same_v<Type, uint64_t>)
            {
                bool constexpr isUnsigned = std::is_same_v<Type, uint64_t>;
                if constexpr(isUnsigned)
                    info.GetReturnValue().Set(v8::BigInt::NewFromUnsigned(info.GetIsolate(), value));
                else
                    info.GetReturnValue().Set(v8::BigInt::New(info.GetIsolate(), value));
            }
            // Then try to convert the value to primitive types
            else if constexpr(std::is_same_v<Type, bool> || std::is_same_v<Type, double> || std::is_same_v<Type, float> || std::is_same_v<Type, int32_t> || std::is_same_v<Type, uint32_t>)
                info.GetReturnValue().Set((Type)value);
            else if constexpr(std::is_same_v<Type, std::nullptr_t>)
                info.GetReturnValue().SetNull();
            else if constexpr(std::is_same_v<Type, std::string>)
            {
                if(value.length() == 0) info.GetReturnValue().SetEmptyString();
                else
                    info.GetReturnValue().Set(JSValue((Type)value));
            }
            else
            {
                static_assert(IsJSValueConvertible<Type>, "Type is not convertible to JS value");
                info.GetReturnValue().Set(JSValue((Type)value));
            }
        }

        void Deprecate(const std::string& message)
        {
            Logger::Warn("This API is deprecated: " + message);
        }
    };

    class FunctionContext : public CallContext<v8::FunctionCallbackInfo<v8::Value>>
    {
        std::vector<Type> argTypes;  // Cache argument types

    public:
        FunctionContext(const v8::FunctionCallbackInfo<v8::Value>& _info) : CallContext(_info)
        {
            argTypes.resize(info.Length());
        }

        bool CheckArgCount(int count)
        {
            return Check(info.Length() == count, "Invalid number of arguments, expected " + std::to_string(count) + " arguments");
        }
        bool CheckArgCount(int min, int max)
        {
            return Check(info.Length() >= min && info.Length() <= max,
                         "Invalid number of arguments, expected minimum " + std::to_string(min) + " and maximum " + std::to_string(max) + " arguments");
        }
        bool CheckArgType(int index, Type type)
        {
            return Check(GetArgType(index) == type,
                         "Invalid argument type at index " + std::to_string(index) + ", expected " + TypeToString(type) + " but got " + TypeToString(GetArgType(index)));
        }
        bool CheckArgType(int index, std::initializer_list<Type> types)
        {
            bool result = false;
            for(Type type : types)
            {
                if(GetArgType(index) == type)
                {
                    result = true;
                    break;
                }
            }
            return Check(result, "Invalid argument type at index " + std::to_string(index) + ", expected one of " + TypeToString(types) + " but got " + TypeToString(GetArgType(index)));
        }
        bool CheckCtor()
        {
            return Check(info.IsConstructCall(), "Constructor called as function");
        }

        Type GetArgType(int index)
        {
            if (index < 0 || index >= argTypes.size()) return Type::INVALID;
            if(argTypes[index] != Type::INVALID) return argTypes[index];
            Type argType = GetType(info[index], GetResource());
            argTypes[index] = argType;
            return argType;
        }

        int GetArgCount()
        {
            return info.Length();
        }

        // If no type to check is specified, it will try to convert the value to the specified type
        template<class T>
        bool GetArg(int index, T& outValue, Type typeToCheck = Type::INVALID)
        {
            if(errored) return false;
            if(index >= info.Length())
            {
                Throw("Missing argument at index " + std::to_string(index));
                return false;
            }
            if(typeToCheck != js::Type::INVALID && !CheckArgType(index, typeToCheck)) return false;

            std::optional<T> result = CppValue<T>(info[index]);
            if(!result.has_value())
            {
                Throw("Invalid argument type at index " + std::to_string(index) + ", expected " + CppTypeToString<T>() + " but got " + TypeToString(GetArgType(index)));
                return false;
            }
            outValue = (T)result.value();
            return true;
        }

        // If no type to check is specified, it will try to convert the value to the specified type
        template<class T>
        T GetArg(int index, const T& defaultValue = T(), Type typeToCheck = Type::INVALID)
        {
            if(errored) return defaultValue;
            if(index >= info.Length()) return defaultValue;
            if(typeToCheck != js::Type::INVALID && !CheckArgType(index, typeToCheck)) return defaultValue;

            std::optional<T> result = CppValue<T>(info[index]);
            return result.has_value() ? (T)result.value() : defaultValue;
        }

        bool GetArgAsHash(int index, uint32_t& outValue)
        {
            if(errored) return false;
            Type argType = GetArgType(index);
            if(argType == Type::STRING)
            {
                std::string str = CppValue(info[index].As<v8::String>());
                outValue = alt::ICore::Instance().Hash(str.c_str());
                return true;
            }
            else if(argType == Type::NUMBER)
            {
                outValue = (uint32_t)CppValue(info[index].As<v8::Number>());
                return true;
            }
            Throw("Invalid argument type at index " + std::to_string(index) + ", expected string or number but got " + TypeToString(argType));
            return false;
        }
    };

    template<class Info>
    class PropertyContextBase : public CallContext<Info>
    {
        v8::Local<v8::Value> value;
        Type valueType = Type::INVALID;

    public:
        PropertyContextBase(const Info& _info) : CallContext<Info>(_info) {}
        PropertyContextBase(const Info& _info, v8::Local<v8::Value> _value) : CallContext<Info>(_info), value(_value) {}

        Type GetValueType()
        {
            if(valueType != Type::INVALID) return valueType;
            valueType = GetType(value, this->GetResource());
            return valueType;
        }

        bool CheckValueType(Type type)
        {
            return this->Check(GetValueType() == type, "Invalid value type, expected " + TypeToString(type) + " but got " + TypeToString(GetValueType()));
        }

        bool CheckValueType(std::initializer_list<Type> types)
        {
            bool result = false;
            for(Type type : types)
            {
                if(GetValueType() == type)
                {
                    result = true;
                    break;
                }
            }
            return this->Check(result, "Invalid value type, expected one of " + TypeToString(types) + " but got " + TypeToString(GetValueType()));
        }

        template<class T>
        bool GetValue(T& outValue, Type typeToCheck = Type::INVALID)
        {
            if(this->errored) return false;
            if(typeToCheck != js::Type::INVALID && !CheckValueType(typeToCheck)) return false;

            std::optional<T> result = CppValue<T>(value);
            if(!result.has_value())
            {
                Throw("Invalid value type, expected " + CppTypeToString<T>() + " but got " + TypeToString(GetValueType()));
                return false;
            }
            outValue = (T)result.value();
            return true;
        }
        bool GetValueAsHash(uint32_t& outValue)
        {
            if(this->errored) return false;
            Type argType = GetValueType();
            if(argType == Type::STRING)
            {
                std::string str = CppValue(value.As<v8::String>());
                outValue = alt::ICore::Instance().Hash(str.c_str());
                return true;
            }
            else if(argType == Type::NUMBER)
            {
                outValue = (uint32_t)CppValue(value.As<v8::Number>());
                return true;
            }
            return false;
        }
    };

    template<class Type>
    class DynamicPropertyContext : public PropertyContextBase<v8::PropertyCallbackInfo<Type>>
    {
        std::string property;
        v8::Local<v8::Object> parent;           // Used for dynamic properties
        alt::IBaseObject* parentObj = nullptr;  //

    public:
        template<class T>
        DynamicPropertyContext(const v8::PropertyCallbackInfo<T>& _info) : PropertyContextBase<v8::PropertyCallbackInfo<T>>(_info)
        {
        }
        template<class T>
        DynamicPropertyContext(const v8::PropertyCallbackInfo<T>& _info, v8::Local<v8::Name> _property)
            : PropertyContextBase<v8::PropertyCallbackInfo<T>>(_info), property(js::CppValue<std::string>(_property.As<v8::Value>()).value())
        {
        }
        template<class T>
        DynamicPropertyContext(const v8::PropertyCallbackInfo<T>& _info, v8::Local<v8::Name> _property, v8::Local<v8::Value> _value)
            : PropertyContextBase<v8::PropertyCallbackInfo<T>>(_info, _value), property(js::CppValue<std::string>(_property.As<v8::Value>()).value())
        {
        }

        void SetParent(v8::Local<v8::Object> _parent)
        {
            parent = _parent;
        }
        bool CheckParent()
        {
            return this->Check(GetParent<alt::IBaseObject>() != nullptr, "Invalid parent base object");
        }

        template<class T>
        T* GetParent()
        {
            if(parentObj) return dynamic_cast<T*>(parentObj);
            if(this->errored) return nullptr;
            std::optional<alt::IBaseObject*> object = CppValue<alt::IBaseObject*>(parent.As<v8::Value>());
            if(!object.has_value()) return nullptr;
            parentObj = object.value();
            return dynamic_cast<T*>(parentObj);
        }

        const std::string& GetProperty()
        {
            return property;
        }
    };

    using PropertyContext = PropertyContextBase<v8::FunctionCallbackInfo<v8::Value>>;
    using LazyPropertyContext = PropertyContextBase<v8::PropertyCallbackInfo<v8::Value>>;

    using DynamicPropertyGetterContext = DynamicPropertyContext<v8::Value>;
    using DynamicPropertySetterContext = DynamicPropertyContext<v8::Value>;
    using DynamicPropertyDeleterContext = DynamicPropertyContext<v8::Boolean>;
    using DynamicPropertyEnumeratorContext = DynamicPropertyContext<v8::Array>;
}  // namespace js
