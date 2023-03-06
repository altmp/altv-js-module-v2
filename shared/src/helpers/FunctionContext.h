#pragma once

#include "v8.h"
#include "cpp-sdk/SDK.h"

#include "Convert.h"
#include "Type.h"

namespace js
{
    class IResource;

    class FunctionContext
    {
        v8::FunctionCallbackInfo<v8::Value> info;
        bool errored = false;
        IResource* resource = nullptr;
        std::vector<Type> argTypes;  // Cache argument types

        alt::IBaseObject* GetThisObjectUntyped();

    public:
        FunctionContext() = delete;
        FunctionContext(const v8::FunctionCallbackInfo<v8::Value>& _info) : info(_info)
        {
            argTypes.resize(info.Length());
        }

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

        IResource* GetResource();

        template<class T>
        T* GetThisObject()
        {
            if(errored) return nullptr;
            return dynamic_cast<T*>(GetThisObjectUntyped());
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

        template<class T>
        void Return(const T& value)
        {
            if(errored) return;
            info.GetReturnValue().Set(JSValue(value));
        }
    };
}  // namespace js
