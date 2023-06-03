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
        int pointersCount = 0;
        int returnsCount = 1;

        char* SaveString(const std::string& str)
        {
            static char* stringValues[256] = { 0 };
            static int nextString = 0;

            if(stringValues[nextString]) free(stringValues[nextString]);

            char* _str = _strdup(str.data());
            stringValues[nextString] = _str;
            nextString = (nextString + 1) % 256;

            return _str;
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
            if(!ctx.GetArg(index, value)) return false;

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
            v8::Local<v8::Value> val = ctx.GetArg<v8::Local<v8::Value>>(index);
            char* ptr = nullptr;

            if(val->IsString())
            {
                std::string str = js::CppValue(val.As<v8::String>());
                ptr = SaveString(str);
            }
            nativeContext->Push(ptr);
            return true;
        }

        bool PushArgs(js::FunctionContext& ctx, alt::INative* native);

        v8::Local<v8::Value> GetPointerReturnValue(alt::INative::Type type);
        v8::Local<v8::Value> GetReturnValue();

        NativeInvoker(CJavaScriptResource* resource, alt::INative* native);

    public:
        static bool Invoke(js::FunctionContext& ctx, alt::INative* native);
    };
}  // namespace js
