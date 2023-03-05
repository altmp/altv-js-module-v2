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

    public:
        FunctionContext() = delete;
        FunctionContext(const v8::FunctionCallbackInfo<v8::Value>& _info) : info(_info) {}

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

        bool CheckArgCount(int count)
        {
            if(info.Length() != count)
            {
                Throw("Not enough arguments, expected " + std::to_string(count) + " arguments");
                return false;
            }
            return true;
        }
        bool CheckArgCount(int min, int max)
        {
            if(info.Length() > max || info.Length() < min)
            {
                Throw("Invalid number of arguments, expected minimum " + std::to_string(min) + " and maximum " + std::to_string(max) + " arguments");
                return false;
            }
            return true;
        }
        bool CheckArgType(int index, Type type)
        {
            Type argType = GetType(info[index]);
            if(argType != type)
            {
                Throw("Invalid argument type at index " + std::to_string(index) + ", expected " + TypeToString(type) + " but got " + TypeToString(argType));
                return false;
            }
            return true;
        }
        bool CheckCtor()
        {
            if(!info.IsConstructCall())
            {
                Throw("Constructor called as function");
                return false;
            }
            return true;
        }

        IResource* GetResource();

        template<class T>
        T* GetThis()
        {
            if(errored) return nullptr;
            return static_cast<T*>(GetResource()->GetScriptObject(info.This()));
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

        template<class T>
        void Return(const T& value)
        {
            if(errored) return;
            info.GetReturnValue().Set(JSValue(value));
        }
    };
}  // namespace js
