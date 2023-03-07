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

        alt::IBaseObject* GetThisObjectUntyped()
        {
            if(errored) return nullptr;
            std::optional<alt::IBaseObject*> object = CppValue<alt::IBaseObject*>(info.This().As<v8::Value>());
            return object.has_value() ? object.value() : nullptr;
        }

    public:
        CallContext(const CallbackInfo& _info) : info(_info) {}

        v8::Isolate* GetIsolate() const
        {
            return info.GetIsolate();
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

        IResource* GetResource()
        {
            return GetCurrentResource(info.GetIsolate());
        }

        template<class T>
        T* GetThisObject()
        {
            if(errored) return nullptr;
            return dynamic_cast<T*>(GetThisObjectUntyped());
        }

        template<class T>
        void Return(const T& value)
        {
            if(errored) return;
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

    template<class T>
    class PropertyContext : public CallContext<v8::PropertyCallbackInfo<T>>
    {
        v8::Local<v8::Value> value;
        Type valueType = Type::Invalid;
        std::string property;
        v8::Local<v8::Object> parent;  // Used for dynamic properties

        Type GetValueType()
        {
            if(valueType != Type::Invalid) return valueType;
            valueType = GetType(value, this->GetResource());
            return valueType;
        }

    public:
        template<class T>
        PropertyContext(const v8::PropertyCallbackInfo<T>& _info) : CallContext<v8::PropertyCallbackInfo<T>>(_info)
        {
        }
        template<class T>
        PropertyContext(const v8::PropertyCallbackInfo<T>& _info, v8::Local<v8::Name> _property)
            : CallContext<v8::PropertyCallbackInfo<T>>(_info), property(js::CppValue<std::string>(_property.As<v8::Value>()).value())
        {
        }
        template<class T>
        PropertyContext(const v8::PropertyCallbackInfo<T>& _info, v8::Local<v8::Name> _property, v8::Local<v8::Value> _value)
            : CallContext<v8::PropertyCallbackInfo<T>>(_info), property(js::CppValue<std::string>(_property.As<v8::Value>()).value()), value(_value)
        {
        }

        void SetParent(v8::Local<v8::Object> _parent)
        {
            parent = _parent;
        }

        template<class T>
        T* GetParent()
        {
            if(this->errored) return nullptr;
            std::optional<alt::IBaseObject*> object = CppValue<alt::IBaseObject*>(parent.As<v8::Value>());
            return object.has_value() ? dynamic_cast<T*>(object.value()) : nullptr;
        }

        bool CheckValueType(Type type)
        {
            return this->Check(GetValueType() == type, "Invalid value, expected " + TypeToString(type) + " but got " + TypeToString(GetValueType()));
        }

        const std::string& GetProperty()
        {
            return property;
        }

        template<class T>
        bool GetValue(int index, T& outValue, Type typeToCheck = Type::Invalid)
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
}  // namespace js
