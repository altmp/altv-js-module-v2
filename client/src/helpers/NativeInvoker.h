#pragma once

#include "cpp-sdk/ICore.h"
#include "helpers/CallContext.h"
#include "magic_enum/include/magic_enum.hpp"

class CJavaScriptResource;

namespace js
{
    class NativeInvoker
    {
        std::shared_ptr<alt::INative::Context> nativeContext;
        alt::INative* native;
        CJavaScriptResource* resource;

        void* pointers[32] = { 0 };
        char* stringValues[32] = { 0 };
        int pointersCount = 0;
        int stringsCount = 0;
        int returnsCount = 1;

        char* SaveString(const std::string& str)
        {
            char* strVal = (char*)malloc(str.size() + 1);
            memcpy(strVal, str.c_str(), str.size() + 1);
            stringValues[stringsCount++] = strVal;

            return strVal;
        }

        template<typename T>
        T* SavePointer(T val)
        {
            T* ptr = reinterpret_cast<T*>(&pointers[pointersCount++]);
            *ptr = val;
            return ptr;
        }

        template<>
        alt::INative::Vector3* SavePointer(alt::INative::Vector3 val)
        {
            alt::INative::Vector3* ptr = reinterpret_cast<alt::INative::Vector3*>(&pointers[pointersCount]);
            pointersCount += 3;
            *ptr = val;
            return ptr;
        }

        int GetMinimumArgCount()
        {
            int count = 0;
            std::vector<alt::INative::Type> args = native->GetArgTypes();
            for(auto arg : args)
            {
                if(arg == alt::INative::Type::ARG_BOOL_PTR || arg == alt::INative::Type::ARG_INT32_PTR || arg == alt::INative::Type::ARG_UINT32_PTR ||
                   arg == alt::INative::Type::ARG_FLOAT_PTR || arg == alt::INative::Type::ARG_VOID || arg == alt::INative::Type::ARG_VECTOR3_PTR)
                    continue;
                count++;
            }
            return count;
        }

        template<typename T>
        bool PushArg(js::FunctionContext& ctx, int index)
        {
            constexpr bool isPointer = std::is_pointer_v<T>;
            using CleanT = std::remove_pointer_t<T>;

            CleanT value;
            if(!isPointer && !ctx.GetArg(index, value)) return false;

            if constexpr(isPointer)
            {
                returnsCount += 1;
                T ptr = SavePointer(value);
                nativeContext->Push(ptr);
            }
            else
                nativeContext->Push(value);
            return true;
        }
        template<>
        bool PushArg<alt::INative::Vector3*>(js::FunctionContext& ctx, int index)
        {
            returnsCount += 1;
            alt::INative::Vector3* ptr = SavePointer(alt::INative::Vector3{});
            nativeContext->Push(ptr);
            return true;
        }
        template<>
        bool PushArg<char*>(js::FunctionContext& ctx, int index)
        {
            v8::Local<v8::Value> val;
            if(!ctx.GetArg(index, val)) return false;

            char* ptr = nullptr;
            if(val->IsString())
            {
                std::string str = js::CppValue(val.As<v8::String>());
                ptr = SaveString(str);
            }
            nativeContext->Push(ptr);
            return true;
        }
        template<>
        bool PushArg<void*>(js::FunctionContext& ctx, int index)
        {
            v8::Local<v8::Value> val;
            if(!ctx.GetArg(index, val)) return false;

            nativeContext->Push(GetBufferFromValue(val));
            return true;
        }
        template<>
        bool PushArg<int32_t>(js::FunctionContext& ctx, int index)
        {
            int32_t val;
            if(ctx.GetArgType(index) == js::Type::BASE_OBJECT)
            {
                alt::IEntity* entity;
                if(!ctx.GetArg(index, entity)) return false;
                val = (int32_t)entity->GetScriptID();
            }
            else if(!ctx.GetArg(index, val))
                return false;

            nativeContext->Push(val);
            return true;
        }

        bool PushArgs(js::FunctionContext& ctx, alt::INative* native);

        v8::Local<v8::Value> GetPointerReturnValue(alt::INative::Type type);
        v8::Local<v8::Value> GetReturnValue();

        void* GetBufferFromValue(v8::Local<v8::Value> val);

        NativeInvoker(CJavaScriptResource* resource, alt::INative* native);
        ~NativeInvoker();

    public:
        static bool Invoke(js::FunctionContext& ctx, alt::INative* native);
    };
}  // namespace js
