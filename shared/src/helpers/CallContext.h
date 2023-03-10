#pragma once

#include "v8.h"
#include "cpp-sdk/SDK.h"

#include "Convert.h"
#include "Type.h"

namespace js
{
    class IResource;

    template<class CallbackInfo>
    class CallContext
    {
    protected:
        CallbackInfo info;
        bool errored = false;
        IResource* resource = nullptr;
        alt::IBaseObject* thisObject = nullptr;

        alt::IBaseObject* GetThisObjectUntyped()
        {
            if(errored) return nullptr;
            if(thisObject) return thisObject;
            std::optional<alt::IBaseObject*> object = CppValue<alt::IBaseObject*>(info.This().As<v8::Value>());
            if(!object.has_value()) return nullptr;
            thisObject = object.value();
            return thisObject;
        }

    public:
        CallContext(const CallbackInfo& _info) : info(_info) {}

        v8::Isolate* GetIsolate() const
        {
            return info.GetIsolate();
        }

        IResource* GetResource() const
        {
            return GetCurrentResource(info.GetIsolate());
        }

        v8::Local<v8::Context> GetContext() const
        {
            return GetIsolate()->GetCurrentContext();
        }

        bool Errored() const
        {
            return errored;
        }

        void Throw(const std::string& message)
        {
            info.GetIsolate()->ThrowException(v8::Exception::Error(JSValue(message)));
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

        template<class T>
        void Return(const T& value)
        {
            if(errored) return;
            // Use fast primitive setters if possible
            if constexpr(std::is_same_v<T, bool> || std::is_same_v<T, double> || std::is_same_v<T, float> || std::is_same_v<T, int32_t> || std::is_same_v<T, uint32_t>)
                info.GetReturnValue().Set(value);
            else if constexpr(std::is_same_v<T, std::nullptr_t>)
                info.GetReturnValue().SetNull();
            else if constexpr(std::is_same_v<T, std::string>)
            {
                if(value.length() == 0) info.GetReturnValue().SetEmptyString();
                else
                    info.GetReturnValue().Set(JSValue(value));
            }
            else
                info.GetReturnValue().Set(JSValue(value));
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
        bool CheckCtor()
        {
            return Check(info.IsConstructCall(), "Constructor called as function");
        }

        Type GetArgType(int index)
        {
            if(argTypes[index] != Type::Invalid) return argTypes[index];
            Type argType = GetType(info[index], GetResource());
            argTypes[index] = argType;
            return argType;
        }

        int GetArgCount()
        {
            return info.Length();
        }

        void SetThisObject(alt::IBaseObject* object);

        // If no type to check is specified, it will try to convert the value to the specified type
        template<class T>
        bool GetArg(int index, T& outValue, Type typeToCheck = Type::Invalid)
        {
            if(errored) return false;
            if(typeToCheck != Type::Invalid && !CheckArgType(index, typeToCheck)) return false;

            std::optional<T> result = CppValue<T>(info[index]);
            if(result.has_value())
            {
                outValue = result.value();
                return true;
            }
            return false;
        }

        bool GetArgAsHash(int index, uint32_t& outValue)
        {
            if(errored) return false;
            Type argType = GetArgType(index);
            if(argType == Type::String)
            {
                std::string str = CppValue(info[index].As<v8::String>());
                outValue = alt::ICore::Instance().Hash(str.c_str());
                return true;
            }
            else if(argType == Type::Number)
            {
                outValue = (uint32_t)CppValue(info[index].As<v8::Number>());
                return true;
            }
            return false;
        }

        bool GetArgRaw(int index, v8::Local<v8::Value>& outValue)
        {
            if(errored) return false;
            outValue = info[index];
            return true;
        }
    };

    template<class T = v8::Value>
    class PropertyContextBase : public CallContext<T>
    {
        v8::Local<v8::Value> value;
        Type valueType = Type::Invalid;

        Type GetValueType()
        {
            if(valueType != Type::Invalid) return valueType;
            valueType = GetType(value, this->GetResource());
            return valueType;
        }

    public:
        PropertyContextBase(const T& _info) : CallContext<T>(_info) {}
        PropertyContextBase(const T& _info, v8::Local<v8::Value> _value) : CallContext<T>(_info), value(_value) {}

        bool CheckValueType(Type type)
        {
            return this->Check(GetValueType() == type, "Invalid value, expected " + TypeToString(type) + " but got " + TypeToString(GetValueType()));
        }

        template<class T>
        bool GetValue(T& outValue, Type typeToCheck = Type::Invalid)
        {
            if(this->errored) return false;
            if(typeToCheck != Type::Invalid && !CheckValueType(typeToCheck)) return false;

            std::optional<T> result = CppValue<T>(value);
            if(result.has_value())
            {
                outValue = result.value();
                return true;
            }
            return false;
        }
    };

    template<class T>
    class DynamicPropertyContext : public PropertyContextBase<v8::PropertyCallbackInfo<T>>
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
            return parentObj;
        }

        const std::string& GetProperty()
        {
            return property;
        }
    };

    using PropertyContext = PropertyContextBase<v8::FunctionCallbackInfo<v8::Value>>;
    using LazyPropertyContext = PropertyContextBase<v8::PropertyCallbackInfo<v8::Value>>;
}  // namespace js
