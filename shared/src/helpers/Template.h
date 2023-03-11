#pragma once

#include <type_traits>

#include "v8.h"

#include "JS.h"
#include "Convert.h"
#include "CallContext.h"

namespace js
{
    class Namespace;
    class Class;

    using FunctionCallback = void (*)(FunctionContext&);
    using PropertyCallback = void (*)(PropertyContext&);
    using LazyPropertyCallback = void (*)(LazyPropertyContext&);

    using DynamicPropertyGetter = void (*)(DynamicPropertyContext<v8::Value>&);
    using DynamicPropertySetter = void (*)(DynamicPropertyContext<v8::Value>&);
    using DynamicPropertyDeleter = void (*)(DynamicPropertyContext<v8::Boolean>&);
    using DynamicPropertyEnumerator = void (*)(DynamicPropertyContext<v8::Array>&);

    namespace Wrapper
    {
        alt::IBaseObject* GetThisObjectFromInfo(const v8::PropertyCallbackInfo<v8::Value>& info);
        alt::IBaseObject* GetThisObjectFromInfo(const v8::PropertyCallbackInfo<void>& info);
        alt::IBaseObject* GetThisObjectFromInfo(const v8::FunctionCallbackInfo<v8::Value>& info);

        static void FunctionHandler(const v8::FunctionCallbackInfo<v8::Value>& info)
        {
            FunctionContext ctx{ info };
            auto callback = static_cast<FunctionCallback>(info.Data().As<v8::External>()->Value());
            callback(ctx);
        }

        static void PropertyHandler(const v8::FunctionCallbackInfo<v8::Value>& info)
        {
            PropertyContext ctx{ info, info[0] };
            auto callback = static_cast<PropertyCallback>(info.Data().As<v8::External>()->Value());
            callback(ctx);
        }

        static void LazyPropertyHandler(v8::Local<v8::Name>, const v8::PropertyCallbackInfo<v8::Value>& info)
        {
            LazyPropertyContext ctx{ info };
            auto callback = static_cast<LazyPropertyCallback>(info.Data().As<v8::External>()->Value());
            callback(ctx);
        }
        template<class Class, auto(Class::*Getter)() const>
        static void LazyPropertyHandler(v8::Local<v8::Name>, const v8::PropertyCallbackInfo<v8::Value>& info)
        {
            Class* obj = dynamic_cast<Class*>(GetThisObjectFromInfo(info));
            if(obj == nullptr)
            {
                info.GetIsolate()->ThrowException(v8::Exception::Error(JSValue("Invalid base object")));
                return;
            }
            constexpr bool isEnum = std::is_enum_v<decltype((obj->*Getter)())>;
            if constexpr(isEnum) info.GetReturnValue().Set(JSValue((int)(obj->*Getter)()));
            else
                info.GetReturnValue().Set(JSValue((obj->*Getter)()));
        }

        template<class Class, auto(Class::*Getter)() const>
        static void PropertyGetterHandler(v8::Local<v8::String>, const v8::PropertyCallbackInfo<v8::Value>& info)
        {
            Class* obj = dynamic_cast<Class*>(GetThisObjectFromInfo(info));
            if(obj == nullptr)
            {
                info.GetIsolate()->ThrowException(v8::Exception::Error(JSValue("Invalid base object")));
                return;
            }
            constexpr bool isEnum = std::is_enum_v<decltype((obj->*Getter)())>;
            if constexpr(isEnum) info.GetReturnValue().Set(JSValue((int)(obj->*Getter)()));
            else
                info.GetReturnValue().Set(JSValue((obj->*Getter)()));
        }
        template<class Class, typename Type, void (Class::*Setter)(Type)>
        static void PropertySetterHandler(v8::Local<v8::String>, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void>& info)
        {
            Class* obj = dynamic_cast<Class*>(GetThisObjectFromInfo(info));
            if(obj == nullptr)
            {
                info.GetIsolate()->ThrowException(v8::Exception::Error(JSValue("Invalid base object")));
                return;
            }
            constexpr bool isEnum = std::is_enum_v<Type>;
            if constexpr(isEnum) (obj->*Setter)(static_cast<Type>(value->Int32Value().ToChecked()));
            else
            {
                auto val = CppValue<typename std::remove_cv_t<typename std::remove_reference_t<Type>>>(value);
                if(!val.has_value())
                {
                    info.GetIsolate()->ThrowException(v8::Exception::Error(JSValue("Invalid value")));
                    return;
                }
                (obj->*Setter)(val.value());
            }
        }

        template<class Class, typename Ret, Ret (Class::*Method)()>
        static void MethodHandler(const v8::FunctionCallbackInfo<v8::Value>& info)
        {
            Class* obj = dynamic_cast<Class*>(GetThisObjectFromInfo(info));
            if(obj == nullptr)
            {
                info.GetIsolate()->ThrowException(v8::Exception::Error(JSValue("Invalid base object")));
                return;
            }
            if constexpr(std::is_same_v<void, Ret>)
            {
                (obj->*Method)();
            }
            else
            {
                info.GetReturnValue().Set(JSValue((obj->*Method)()));
            }
        }
        template<class Class, typename Ret, Ret (Class::*Method)() const>
        static void MethodHandler(const v8::FunctionCallbackInfo<v8::Value>& info)
        {
            Class* obj = dynamic_cast<Class*>(GetThisObjectFromInfo(info));
            if(obj == nullptr)
            {
                info.GetIsolate()->ThrowException(v8::Exception::Error(JSValue("Invalid base object")));
                return;
            }
            if constexpr(std::is_same_v<void, Ret>)
            {
                (obj->*Method)();
            }
            else
            {
                info.GetReturnValue().Set(JSValue((obj->*Method)()));
            }
        }

        template<class T>
        using CleanArg = typename std::remove_cv_t<typename std::remove_reference_t<T>>;

        template<class T>
        inline T GetArg(const v8::FunctionCallbackInfo<v8::Value>& info, int i)
        {
            if(info.Length() <= i) return T();
            std::optional<T> val = CppValue<T>(info[i]);
            return val.has_value() ? val.value() : T();
        }

#pragma region "Template method handlers"

        template<class Class, typename Ret, typename Arg0, Ret (Class::*Method)(Arg0)>
        static void MethodHandler(const v8::FunctionCallbackInfo<v8::Value>& info)
        {
            Class* obj = dynamic_cast<Class*>(GetThisObjectFromInfo(info));
            if(obj == nullptr)
            {
                info.GetIsolate()->ThrowException(v8::Exception::Error(JSValue("Invalid base object")));
                return;
            }
            if constexpr(std::is_same_v<void, Ret>)
            {
                (obj->*Method)(GetArg<CleanArg<Arg0>>(info, 0));
            }
            else
            {
                info.GetReturnValue().Set(JSValue((obj->*Method)(GetArg<CleanArg<Arg0>>(info, 0))));
            }
        }
        template<class Class, typename Ret, typename Arg0, Ret (Class::*Method)(Arg0) const>
        static void MethodHandler(const v8::FunctionCallbackInfo<v8::Value>& info)
        {
            Class* obj = dynamic_cast<Class*>(GetThisObjectFromInfo(info));
            if(obj == nullptr)
            {
                info.GetIsolate()->ThrowException(v8::Exception::Error(JSValue("Invalid base object")));
                return;
            }
            if constexpr(std::is_same_v<void, Ret>)
            {
                (obj->*Method)(GetArg<CleanArg<Arg0>>(info, 0));
            }
            else
            {
                info.GetReturnValue().Set(JSValue((obj->*Method)(GetArg<CleanArg<Arg0>>(info, 0))));
            }
        }
        template<class Class, typename Ret, typename Arg0, typename Arg1, Ret (Class::*Method)(Arg0, Arg1)>
        static void MethodHandler(const v8::FunctionCallbackInfo<v8::Value>& info)
        {
            Class* obj = dynamic_cast<Class*>(GetThisObjectFromInfo(info));
            if(obj == nullptr)
            {
                info.GetIsolate()->ThrowException(v8::Exception::Error(JSValue("Invalid base object")));
                return;
            }
            if constexpr(std::is_same_v<void, Ret>)
            {
                (obj->*Method)(GetArg<CleanArg<Arg0>>(info, 0), GetArg<CleanArg<Arg1>>(info, 1));
            }
            else
            {
                info.GetReturnValue().Set(JSValue((obj->*Method)(GetArg<CleanArg<Arg0>>(info, 0), GetArg<CleanArg<Arg1>>(info, 1))));
            }
        }
        template<class Class, typename Ret, typename Arg0, typename Arg1, Ret (Class::*Method)(Arg0, Arg1) const>
        static void MethodHandler(const v8::FunctionCallbackInfo<v8::Value>& info)
        {
            Class* obj = dynamic_cast<Class*>(GetThisObjectFromInfo(info));
            if(obj == nullptr)
            {
                info.GetIsolate()->ThrowException(v8::Exception::Error(JSValue("Invalid base object")));
                return;
            }
            if constexpr(std::is_same_v<void, Ret>)
            {
                (obj->*Method)(GetArg<CleanArg<Arg0>>(info, 0), GetArg<CleanArg<Arg1>>(info, 1));
            }
            else
            {
                info.GetReturnValue().Set(JSValue((obj->*Method)(GetArg<CleanArg<Arg0>>(info, 0), GetArg<CleanArg<Arg1>>(info, 1))));
            }
        }
        template<class Class, typename Ret, typename Arg0, typename Arg1, typename Arg2, Ret (Class::*Method)(Arg0, Arg1, Arg2)>
        static void MethodHandler(const v8::FunctionCallbackInfo<v8::Value>& info)
        {
            Class* obj = dynamic_cast<Class*>(GetThisObjectFromInfo(info));
            if(obj == nullptr)
            {
                info.GetIsolate()->ThrowException(v8::Exception::Error(JSValue("Invalid base object")));
                return;
            }
            if constexpr(std::is_same_v<void, Ret>)
            {
                (obj->*Method)(GetArg<CleanArg<Arg0>>(info, 0), GetArg<CleanArg<Arg1>>(info, 1), GetArg<CleanArg<Arg2>>(info, 2));
            }
            else
            {
                info.GetReturnValue().Set(JSValue((obj->*Method)(GetArg<CleanArg<Arg0>>(info, 0), GetArg<CleanArg<Arg1>>(info, 1), GetArg<CleanArg<Arg2>>(info, 2))));
            }
        }
        template<class Class, typename Ret, typename Arg0, typename Arg1, typename Arg2, Ret (Class::*Method)(Arg0, Arg1, Arg2) const>
        static void MethodHandler(const v8::FunctionCallbackInfo<v8::Value>& info)
        {
            Class* obj = dynamic_cast<Class*>(GetThisObjectFromInfo(info));
            if(obj == nullptr)
            {
                info.GetIsolate()->ThrowException(v8::Exception::Error(JSValue("Invalid base object")));
                return;
            }
            if constexpr(std::is_same_v<void, Ret>)
            {
                (obj->*Method)(GetArg<CleanArg<Arg0>>(info, 0), GetArg<CleanArg<Arg1>>(info, 1), GetArg<CleanArg<Arg2>>(info, 2));
            }
            else
            {
                info.GetReturnValue().Set(JSValue((obj->*Method)(GetArg<CleanArg<Arg0>>(info, 0), GetArg<CleanArg<Arg1>>(info, 1), GetArg<CleanArg<Arg2>>(info, 2))));
            }
        }
        template<class Class, typename Ret, typename Arg0, typename Arg1, typename Arg2, typename Arg3, Ret (Class::*Method)(Arg0, Arg1, Arg2, Arg3)>
        static void MethodHandler(const v8::FunctionCallbackInfo<v8::Value>& info)
        {
            Class* obj = dynamic_cast<Class*>(GetThisObjectFromInfo(info));
            if(obj == nullptr)
            {
                info.GetIsolate()->ThrowException(v8::Exception::Error(JSValue("Invalid base object")));
                return;
            }
            if constexpr(std::is_same_v<void, Ret>)
            {
                (obj->*Method)(GetArg<CleanArg<Arg0>>(info, 0), GetArg<CleanArg<Arg1>>(info, 1), GetArg<CleanArg<Arg2>>(info, 2), GetArg<CleanArg<Arg3>>(info, 3));
            }
            else
            {
                info.GetReturnValue().Set(
                  JSValue((obj->*Method)(GetArg<CleanArg<Arg0>>(info, 0), GetArg<CleanArg<Arg1>>(info, 1), GetArg<CleanArg<Arg2>>(info, 2), GetArg<CleanArg<Arg3>>(info, 3))));
            }
        }
        template<class Class, typename Ret, typename Arg0, typename Arg1, typename Arg2, typename Arg3, Ret (Class::*Method)(Arg0, Arg1, Arg2, Arg3) const>
        static void MethodHandler(const v8::FunctionCallbackInfo<v8::Value>& info)
        {
            Class* obj = dynamic_cast<Class*>(GetThisObjectFromInfo(info));
            if(obj == nullptr)
            {
                info.GetIsolate()->ThrowException(v8::Exception::Error(JSValue("Invalid base object")));
                return;
            }
            if constexpr(std::is_same_v<void, Ret>)
            {
                (obj->*Method)(GetArg<CleanArg<Arg0>>(info, 0), GetArg<CleanArg<Arg1>>(info, 1), GetArg<CleanArg<Arg2>>(info, 2), GetArg<CleanArg<Arg3>>(info, 3));
            }
            else
            {
                info.GetReturnValue().Set(
                  JSValue((obj->*Method)(GetArg<CleanArg<Arg0>>(info, 0), GetArg<CleanArg<Arg1>>(info, 1), GetArg<CleanArg<Arg2>>(info, 2), GetArg<CleanArg<Arg3>>(info, 3))));
            }
        }
        template<class Class, typename Ret, typename Arg0, typename Arg1, typename Arg2, typename Arg3, typename Arg4, Ret (Class::*Method)(Arg0, Arg1, Arg2, Arg3, Arg4)>
        static void MethodHandler(const v8::FunctionCallbackInfo<v8::Value>& info)
        {
            Class* obj = dynamic_cast<Class*>(GetThisObjectFromInfo(info));
            if(obj == nullptr)
            {
                info.GetIsolate()->ThrowException(v8::Exception::Error(JSValue("Invalid base object")));
                return;
            }
            if constexpr(std::is_same_v<void, Ret>)
            {
                (obj->*Method)(
                  GetArg<CleanArg<Arg0>>(info, 0), GetArg<CleanArg<Arg1>>(info, 1), GetArg<CleanArg<Arg2>>(info, 2), GetArg<CleanArg<Arg3>>(info, 3), GetArg<CleanArg<Arg4>>(info, 4));
            }
            else
            {
                info.GetReturnValue().Set(JSValue((obj->*Method)(
                  GetArg<CleanArg<Arg0>>(info, 0), GetArg<CleanArg<Arg1>>(info, 1), GetArg<CleanArg<Arg2>>(info, 2), GetArg<CleanArg<Arg3>>(info, 3), GetArg<CleanArg<Arg4>>(info, 4))));
            }
        }
        template<class Class, typename Ret, typename Arg0, typename Arg1, typename Arg2, typename Arg3, typename Arg4, Ret (Class::*Method)(Arg0, Arg1, Arg2, Arg3, Arg4) const>
        static void MethodHandler(const v8::FunctionCallbackInfo<v8::Value>& info)
        {
            Class* obj = dynamic_cast<Class*>(GetThisObjectFromInfo(info));
            if(obj == nullptr)
            {
                info.GetIsolate()->ThrowException(v8::Exception::Error(JSValue("Invalid base object")));
                return;
            }
            if constexpr(std::is_same_v<void, Ret>)
            {
                (obj->*Method)(
                  GetArg<CleanArg<Arg0>>(info, 0), GetArg<CleanArg<Arg1>>(info, 1), GetArg<CleanArg<Arg2>>(info, 2), GetArg<CleanArg<Arg3>>(info, 3), GetArg<CleanArg<Arg4>>(info, 4));
            }
            else
            {
                info.GetReturnValue().Set(JSValue((obj->*Method)(
                  GetArg<CleanArg<Arg0>>(info, 0), GetArg<CleanArg<Arg1>>(info, 1), GetArg<CleanArg<Arg2>>(info, 2), GetArg<CleanArg<Arg3>>(info, 3), GetArg<CleanArg<Arg4>>(info, 4))));
            }
        }
        template<class Class,
                 typename Ret,
                 typename Arg0,
                 typename Arg1,
                 typename Arg2,
                 typename Arg3,
                 typename Arg4,
                 typename Arg5,
                 Ret (Class::*Method)(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5)>
        static void MethodHandler(const v8::FunctionCallbackInfo<v8::Value>& info)
        {
            Class* obj = dynamic_cast<Class*>(GetThisObjectFromInfo(info));
            if(obj == nullptr)
            {
                info.GetIsolate()->ThrowException(v8::Exception::Error(JSValue("Invalid base object")));
                return;
            }
            if constexpr(std::is_same_v<void, Ret>)
            {
                (obj->*Method)(GetArg<CleanArg<Arg0>>(info, 0),
                               GetArg<CleanArg<Arg1>>(info, 1),
                               GetArg<CleanArg<Arg2>>(info, 2),
                               GetArg<CleanArg<Arg3>>(info, 3),
                               GetArg<CleanArg<Arg4>>(info, 4),
                               GetArg<CleanArg<Arg5>>(info, 5));
            }
            else
            {
                info.GetReturnValue().Set(JSValue((obj->*Method)(GetArg<CleanArg<Arg0>>(info, 0),
                                                                 GetArg<CleanArg<Arg1>>(info, 1),
                                                                 GetArg<CleanArg<Arg2>>(info, 2),
                                                                 GetArg<CleanArg<Arg3>>(info, 3),
                                                                 GetArg<CleanArg<Arg4>>(info, 4),
                                                                 GetArg<CleanArg<Arg5>>(info, 5))));
            }
        }
        template<class Class,
                 typename Ret,
                 typename Arg0,
                 typename Arg1,
                 typename Arg2,
                 typename Arg3,
                 typename Arg4,
                 typename Arg5,
                 Ret (Class::*Method)(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5) const>
        static void MethodHandler(const v8::FunctionCallbackInfo<v8::Value>& info)
        {
            Class* obj = dynamic_cast<Class*>(GetThisObjectFromInfo(info));
            if(obj == nullptr)
            {
                info.GetIsolate()->ThrowException(v8::Exception::Error(JSValue("Invalid base object")));
                return;
            }
            if constexpr(std::is_same_v<void, Ret>)
            {
                (obj->*Method)(GetArg<CleanArg<Arg0>>(info, 0),
                               GetArg<CleanArg<Arg1>>(info, 1),
                               GetArg<CleanArg<Arg2>>(info, 2),
                               GetArg<CleanArg<Arg3>>(info, 3),
                               GetArg<CleanArg<Arg4>>(info, 4),
                               GetArg<CleanArg<Arg5>>(info, 5));
            }
            else
            {
                info.GetReturnValue().Set(JSValue((obj->*Method)(GetArg<CleanArg<Arg0>>(info, 0),
                                                                 GetArg<CleanArg<Arg1>>(info, 1),
                                                                 GetArg<CleanArg<Arg2>>(info, 2),
                                                                 GetArg<CleanArg<Arg3>>(info, 3),
                                                                 GetArg<CleanArg<Arg4>>(info, 4),
                                                                 GetArg<CleanArg<Arg5>>(info, 5))));
            }
        }
        template<class Class,
                 typename Ret,
                 typename Arg0,
                 typename Arg1,
                 typename Arg2,
                 typename Arg3,
                 typename Arg4,
                 typename Arg5,
                 typename Arg6,
                 Ret (Class::*Method)(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6)>
        static void MethodHandler(const v8::FunctionCallbackInfo<v8::Value>& info)
        {
            Class* obj = dynamic_cast<Class*>(GetThisObjectFromInfo(info));
            if(obj == nullptr)
            {
                info.GetIsolate()->ThrowException(v8::Exception::Error(JSValue("Invalid base object")));
                return;
            }
            if constexpr(std::is_same_v<void, Ret>)
            {
                (obj->*Method)(GetArg<CleanArg<Arg0>>(info, 0),
                               GetArg<CleanArg<Arg1>>(info, 1),
                               GetArg<CleanArg<Arg2>>(info, 2),
                               GetArg<CleanArg<Arg3>>(info, 3),
                               GetArg<CleanArg<Arg4>>(info, 4),
                               GetArg<CleanArg<Arg5>>(info, 5),
                               GetArg<CleanArg<Arg6>>(info, 6));
            }
            else
            {
                info.GetReturnValue().Set(JSValue((obj->*Method)(GetArg<CleanArg<Arg0>>(info, 0),
                                                                 GetArg<CleanArg<Arg1>>(info, 1),
                                                                 GetArg<CleanArg<Arg2>>(info, 2),
                                                                 GetArg<CleanArg<Arg3>>(info, 3),
                                                                 GetArg<CleanArg<Arg4>>(info, 4),
                                                                 GetArg<CleanArg<Arg5>>(info, 5),
                                                                 GetArg<CleanArg<Arg6>>(info, 6))));
            }
        }
        template<class Class,
                 typename Ret,
                 typename Arg0,
                 typename Arg1,
                 typename Arg2,
                 typename Arg3,
                 typename Arg4,
                 typename Arg5,
                 typename Arg6,
                 Ret (Class::*Method)(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6) const>
        static void MethodHandler(const v8::FunctionCallbackInfo<v8::Value>& info)
        {
            Class* obj = dynamic_cast<Class*>(GetThisObjectFromInfo(info));
            if(obj == nullptr)
            {
                info.GetIsolate()->ThrowException(v8::Exception::Error(JSValue("Invalid base object")));
                return;
            }
            if constexpr(std::is_same_v<void, Ret>)
            {
                (obj->*Method)(GetArg<CleanArg<Arg0>>(info, 0),
                               GetArg<CleanArg<Arg1>>(info, 1),
                               GetArg<CleanArg<Arg2>>(info, 2),
                               GetArg<CleanArg<Arg3>>(info, 3),
                               GetArg<CleanArg<Arg4>>(info, 4),
                               GetArg<CleanArg<Arg5>>(info, 5),
                               GetArg<CleanArg<Arg6>>(info, 6));
            }
            else
            {
                info.GetReturnValue().Set(JSValue((obj->*Method)(GetArg<CleanArg<Arg0>>(info, 0),
                                                                 GetArg<CleanArg<Arg1>>(info, 1),
                                                                 GetArg<CleanArg<Arg2>>(info, 2),
                                                                 GetArg<CleanArg<Arg3>>(info, 3),
                                                                 GetArg<CleanArg<Arg4>>(info, 4),
                                                                 GetArg<CleanArg<Arg5>>(info, 5),
                                                                 GetArg<CleanArg<Arg6>>(info, 6))));
            }
        }
        template<class Class,
                 typename Ret,
                 typename Arg0,
                 typename Arg1,
                 typename Arg2,
                 typename Arg3,
                 typename Arg4,
                 typename Arg5,
                 typename Arg6,
                 typename Arg7,
                 Ret (Class::*Method)(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7)>
        static void MethodHandler(const v8::FunctionCallbackInfo<v8::Value>& info)
        {
            Class* obj = dynamic_cast<Class*>(GetThisObjectFromInfo(info));
            if(obj == nullptr)
            {
                info.GetIsolate()->ThrowException(v8::Exception::Error(JSValue("Invalid base object")));
                return;
            }
            if constexpr(std::is_same_v<void, Ret>)
            {
                (obj->*Method)(GetArg<CleanArg<Arg0>>(info, 0),
                               GetArg<CleanArg<Arg1>>(info, 1),
                               GetArg<CleanArg<Arg2>>(info, 2),
                               GetArg<CleanArg<Arg3>>(info, 3),
                               GetArg<CleanArg<Arg4>>(info, 4),
                               GetArg<CleanArg<Arg5>>(info, 5),
                               GetArg<CleanArg<Arg6>>(info, 6),
                               GetArg<CleanArg<Arg7>>(info, 7));
            }
            else
            {
                info.GetReturnValue().Set(JSValue((obj->*Method)(GetArg<CleanArg<Arg0>>(info, 0),
                                                                 GetArg<CleanArg<Arg1>>(info, 1),
                                                                 GetArg<CleanArg<Arg2>>(info, 2),
                                                                 GetArg<CleanArg<Arg3>>(info, 3),
                                                                 GetArg<CleanArg<Arg4>>(info, 4),
                                                                 GetArg<CleanArg<Arg5>>(info, 5),
                                                                 GetArg<CleanArg<Arg6>>(info, 6),
                                                                 GetArg<CleanArg<Arg7>>(info, 7))));
            }
        }
        template<class Class,
                 typename Ret,
                 typename Arg0,
                 typename Arg1,
                 typename Arg2,
                 typename Arg3,
                 typename Arg4,
                 typename Arg5,
                 typename Arg6,
                 typename Arg7,
                 Ret (Class::*Method)(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7) const>
        static void MethodHandler(const v8::FunctionCallbackInfo<v8::Value>& info)
        {
            Class* obj = dynamic_cast<Class*>(GetThisObjectFromInfo(info));
            if(obj == nullptr)
            {
                info.GetIsolate()->ThrowException(v8::Exception::Error(JSValue("Invalid base object")));
                return;
            }
            if constexpr(std::is_same_v<void, Ret>)
            {
                (obj->*Method)(GetArg<CleanArg<Arg0>>(info, 0),
                               GetArg<CleanArg<Arg1>>(info, 1),
                               GetArg<CleanArg<Arg2>>(info, 2),
                               GetArg<CleanArg<Arg3>>(info, 3),
                               GetArg<CleanArg<Arg4>>(info, 4),
                               GetArg<CleanArg<Arg5>>(info, 5),
                               GetArg<CleanArg<Arg6>>(info, 6),
                               GetArg<CleanArg<Arg7>>(info, 7));
            }
            else
            {
                info.GetReturnValue().Set(JSValue((obj->*Method)(GetArg<CleanArg<Arg0>>(info, 0),
                                                                 GetArg<CleanArg<Arg1>>(info, 1),
                                                                 GetArg<CleanArg<Arg2>>(info, 2),
                                                                 GetArg<CleanArg<Arg3>>(info, 3),
                                                                 GetArg<CleanArg<Arg4>>(info, 4),
                                                                 GetArg<CleanArg<Arg5>>(info, 5),
                                                                 GetArg<CleanArg<Arg6>>(info, 6),
                                                                 GetArg<CleanArg<Arg7>>(info, 7))));
            }
        }
        template<class Class,
                 typename Ret,
                 typename Arg0,
                 typename Arg1,
                 typename Arg2,
                 typename Arg3,
                 typename Arg4,
                 typename Arg5,
                 typename Arg6,
                 typename Arg7,
                 typename Arg8,
                 Ret (Class::*Method)(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8)>
        static void MethodHandler(const v8::FunctionCallbackInfo<v8::Value>& info)
        {
            Class* obj = dynamic_cast<Class*>(GetThisObjectFromInfo(info));
            if(obj == nullptr)
            {
                info.GetIsolate()->ThrowException(v8::Exception::Error(JSValue("Invalid base object")));
                return;
            }
            if constexpr(std::is_same_v<void, Ret>)
            {
                (obj->*Method)(GetArg<CleanArg<Arg0>>(info, 0),
                               GetArg<CleanArg<Arg1>>(info, 1),
                               GetArg<CleanArg<Arg2>>(info, 2),
                               GetArg<CleanArg<Arg3>>(info, 3),
                               GetArg<CleanArg<Arg4>>(info, 4),
                               GetArg<CleanArg<Arg5>>(info, 5),
                               GetArg<CleanArg<Arg6>>(info, 6),
                               GetArg<CleanArg<Arg7>>(info, 7),
                               GetArg<CleanArg<Arg8>>(info, 8));
            }
            else
            {
                info.GetReturnValue().Set(JSValue((obj->*Method)(GetArg<CleanArg<Arg0>>(info, 0),
                                                                 GetArg<CleanArg<Arg1>>(info, 1),
                                                                 GetArg<CleanArg<Arg2>>(info, 2),
                                                                 GetArg<CleanArg<Arg3>>(info, 3),
                                                                 GetArg<CleanArg<Arg4>>(info, 4),
                                                                 GetArg<CleanArg<Arg5>>(info, 5),
                                                                 GetArg<CleanArg<Arg6>>(info, 6),
                                                                 GetArg<CleanArg<Arg7>>(info, 7),
                                                                 GetArg<CleanArg<Arg8>>(info, 8))));
            }
        }
        template<class Class,
                 typename Ret,
                 typename Arg0,
                 typename Arg1,
                 typename Arg2,
                 typename Arg3,
                 typename Arg4,
                 typename Arg5,
                 typename Arg6,
                 typename Arg7,
                 typename Arg8,
                 Ret (Class::*Method)(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8) const>
        static void MethodHandler(const v8::FunctionCallbackInfo<v8::Value>& info)
        {
            Class* obj = dynamic_cast<Class*>(GetThisObjectFromInfo(info));
            if(obj == nullptr)
            {
                info.GetIsolate()->ThrowException(v8::Exception::Error(JSValue("Invalid base object")));
                return;
            }
            if constexpr(std::is_same_v<void, Ret>)
            {
                (obj->*Method)(GetArg<CleanArg<Arg0>>(info, 0),
                               GetArg<CleanArg<Arg1>>(info, 1),
                               GetArg<CleanArg<Arg2>>(info, 2),
                               GetArg<CleanArg<Arg3>>(info, 3),
                               GetArg<CleanArg<Arg4>>(info, 4),
                               GetArg<CleanArg<Arg5>>(info, 5),
                               GetArg<CleanArg<Arg6>>(info, 6),
                               GetArg<CleanArg<Arg7>>(info, 7),
                               GetArg<CleanArg<Arg8>>(info, 8));
            }
            else
            {
                info.GetReturnValue().Set(JSValue((obj->*Method)(GetArg<CleanArg<Arg0>>(info, 0),
                                                                 GetArg<CleanArg<Arg1>>(info, 1),
                                                                 GetArg<CleanArg<Arg2>>(info, 2),
                                                                 GetArg<CleanArg<Arg3>>(info, 3),
                                                                 GetArg<CleanArg<Arg4>>(info, 4),
                                                                 GetArg<CleanArg<Arg5>>(info, 5),
                                                                 GetArg<CleanArg<Arg6>>(info, 6),
                                                                 GetArg<CleanArg<Arg7>>(info, 7),
                                                                 GetArg<CleanArg<Arg8>>(info, 8))));
            }
        }
        template<class Class,
                 typename Ret,
                 typename Arg0,
                 typename Arg1,
                 typename Arg2,
                 typename Arg3,
                 typename Arg4,
                 typename Arg5,
                 typename Arg6,
                 typename Arg7,
                 typename Arg8,
                 typename Arg9,
                 Ret (Class::*Method)(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8, Arg9)>
        static void MethodHandler(const v8::FunctionCallbackInfo<v8::Value>& info)
        {
            Class* obj = dynamic_cast<Class*>(GetThisObjectFromInfo(info));
            if(obj == nullptr)
            {
                info.GetIsolate()->ThrowException(v8::Exception::Error(JSValue("Invalid base object")));
                return;
            }
            if constexpr(std::is_same_v<void, Ret>)
            {
                (obj->*Method)(GetArg<CleanArg<Arg0>>(info, 0),
                               GetArg<CleanArg<Arg1>>(info, 1),
                               GetArg<CleanArg<Arg2>>(info, 2),
                               GetArg<CleanArg<Arg3>>(info, 3),
                               GetArg<CleanArg<Arg4>>(info, 4),
                               GetArg<CleanArg<Arg5>>(info, 5),
                               GetArg<CleanArg<Arg6>>(info, 6),
                               GetArg<CleanArg<Arg7>>(info, 7),
                               GetArg<CleanArg<Arg8>>(info, 8),
                               GetArg<CleanArg<Arg9>>(info, 9));
            }
            else
            {
                info.GetReturnValue().Set(JSValue((obj->*Method)(GetArg<CleanArg<Arg0>>(info, 0),
                                                                 GetArg<CleanArg<Arg1>>(info, 1),
                                                                 GetArg<CleanArg<Arg2>>(info, 2),
                                                                 GetArg<CleanArg<Arg3>>(info, 3),
                                                                 GetArg<CleanArg<Arg4>>(info, 4),
                                                                 GetArg<CleanArg<Arg5>>(info, 5),
                                                                 GetArg<CleanArg<Arg6>>(info, 6),
                                                                 GetArg<CleanArg<Arg7>>(info, 7),
                                                                 GetArg<CleanArg<Arg8>>(info, 8),
                                                                 GetArg<CleanArg<Arg9>>(info, 9))));
            }
        }
        template<class Class,
                 typename Ret,
                 typename Arg0,
                 typename Arg1,
                 typename Arg2,
                 typename Arg3,
                 typename Arg4,
                 typename Arg5,
                 typename Arg6,
                 typename Arg7,
                 typename Arg8,
                 typename Arg9,
                 Ret (Class::*Method)(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8, Arg9) const>
        static void MethodHandler(const v8::FunctionCallbackInfo<v8::Value>& info)
        {
            Class* obj = dynamic_cast<Class*>(GetThisObjectFromInfo(info));
            if(obj == nullptr)
            {
                info.GetIsolate()->ThrowException(v8::Exception::Error(JSValue("Invalid base object")));
                return;
            }
            if constexpr(std::is_same_v<void, Ret>)
            {
                (obj->*Method)(GetArg<CleanArg<Arg0>>(info, 0),
                               GetArg<CleanArg<Arg1>>(info, 1),
                               GetArg<CleanArg<Arg2>>(info, 2),
                               GetArg<CleanArg<Arg3>>(info, 3),
                               GetArg<CleanArg<Arg4>>(info, 4),
                               GetArg<CleanArg<Arg5>>(info, 5),
                               GetArg<CleanArg<Arg6>>(info, 6),
                               GetArg<CleanArg<Arg7>>(info, 7),
                               GetArg<CleanArg<Arg8>>(info, 8),
                               GetArg<CleanArg<Arg9>>(info, 9));
            }
            else
            {
                info.GetReturnValue().Set(JSValue((obj->*Method)(GetArg<CleanArg<Arg0>>(info, 0),
                                                                 GetArg<CleanArg<Arg1>>(info, 1),
                                                                 GetArg<CleanArg<Arg2>>(info, 2),
                                                                 GetArg<CleanArg<Arg3>>(info, 3),
                                                                 GetArg<CleanArg<Arg4>>(info, 4),
                                                                 GetArg<CleanArg<Arg5>>(info, 5),
                                                                 GetArg<CleanArg<Arg6>>(info, 6),
                                                                 GetArg<CleanArg<Arg7>>(info, 7),
                                                                 GetArg<CleanArg<Arg8>>(info, 8),
                                                                 GetArg<CleanArg<Arg9>>(info, 9))));
            }
        }
        template<class Class,
                 typename Ret,
                 typename Arg0,
                 typename Arg1,
                 typename Arg2,
                 typename Arg3,
                 typename Arg4,
                 typename Arg5,
                 typename Arg6,
                 typename Arg7,
                 typename Arg8,
                 typename Arg9,
                 typename Arg10,
                 Ret (Class::*Method)(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8, Arg9, Arg10)>
        static void MethodHandler(const v8::FunctionCallbackInfo<v8::Value>& info)
        {
            Class* obj = dynamic_cast<Class*>(GetThisObjectFromInfo(info));
            if(obj == nullptr)
            {
                info.GetIsolate()->ThrowException(v8::Exception::Error(JSValue("Invalid base object")));
                return;
            }
            if constexpr(std::is_same_v<void, Ret>)
            {
                (obj->*Method)(GetArg<CleanArg<Arg0>>(info, 0),
                               GetArg<CleanArg<Arg1>>(info, 1),
                               GetArg<CleanArg<Arg2>>(info, 2),
                               GetArg<CleanArg<Arg3>>(info, 3),
                               GetArg<CleanArg<Arg4>>(info, 4),
                               GetArg<CleanArg<Arg5>>(info, 5),
                               GetArg<CleanArg<Arg6>>(info, 6),
                               GetArg<CleanArg<Arg7>>(info, 7),
                               GetArg<CleanArg<Arg8>>(info, 8),
                               GetArg<CleanArg<Arg9>>(info, 9),
                               GetArg<CleanArg<Arg10>>(info, 10));
            }
            else
            {
                info.GetReturnValue().Set(JSValue((obj->*Method)(GetArg<CleanArg<Arg0>>(info, 0),
                                                                 GetArg<CleanArg<Arg1>>(info, 1),
                                                                 GetArg<CleanArg<Arg2>>(info, 2),
                                                                 GetArg<CleanArg<Arg3>>(info, 3),
                                                                 GetArg<CleanArg<Arg4>>(info, 4),
                                                                 GetArg<CleanArg<Arg5>>(info, 5),
                                                                 GetArg<CleanArg<Arg6>>(info, 6),
                                                                 GetArg<CleanArg<Arg7>>(info, 7),
                                                                 GetArg<CleanArg<Arg8>>(info, 8),
                                                                 GetArg<CleanArg<Arg9>>(info, 9),
                                                                 GetArg<CleanArg<Arg10>>(info, 10))));
            }
        }
        template<class Class,
                 typename Ret,
                 typename Arg0,
                 typename Arg1,
                 typename Arg2,
                 typename Arg3,
                 typename Arg4,
                 typename Arg5,
                 typename Arg6,
                 typename Arg7,
                 typename Arg8,
                 typename Arg9,
                 typename Arg10,
                 Ret (Class::*Method)(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8, Arg9, Arg10) const>
        static void MethodHandler(const v8::FunctionCallbackInfo<v8::Value>& info)
        {
            Class* obj = dynamic_cast<Class*>(GetThisObjectFromInfo(info));
            if(obj == nullptr)
            {
                info.GetIsolate()->ThrowException(v8::Exception::Error(JSValue("Invalid base object")));
                return;
            }
            if constexpr(std::is_same_v<void, Ret>)
            {
                (obj->*Method)(GetArg<CleanArg<Arg0>>(info, 0),
                               GetArg<CleanArg<Arg1>>(info, 1),
                               GetArg<CleanArg<Arg2>>(info, 2),
                               GetArg<CleanArg<Arg3>>(info, 3),
                               GetArg<CleanArg<Arg4>>(info, 4),
                               GetArg<CleanArg<Arg5>>(info, 5),
                               GetArg<CleanArg<Arg6>>(info, 6),
                               GetArg<CleanArg<Arg7>>(info, 7),
                               GetArg<CleanArg<Arg8>>(info, 8),
                               GetArg<CleanArg<Arg9>>(info, 9),
                               GetArg<CleanArg<Arg10>>(info, 10));
            }
            else
            {
                info.GetReturnValue().Set(JSValue((obj->*Method)(GetArg<CleanArg<Arg0>>(info, 0),
                                                                 GetArg<CleanArg<Arg1>>(info, 1),
                                                                 GetArg<CleanArg<Arg2>>(info, 2),
                                                                 GetArg<CleanArg<Arg3>>(info, 3),
                                                                 GetArg<CleanArg<Arg4>>(info, 4),
                                                                 GetArg<CleanArg<Arg5>>(info, 5),
                                                                 GetArg<CleanArg<Arg6>>(info, 6),
                                                                 GetArg<CleanArg<Arg7>>(info, 7),
                                                                 GetArg<CleanArg<Arg8>>(info, 8),
                                                                 GetArg<CleanArg<Arg9>>(info, 9),
                                                                 GetArg<CleanArg<Arg10>>(info, 10))));
            }
        }
        template<class Class,
                 typename Ret,
                 typename Arg0,
                 typename Arg1,
                 typename Arg2,
                 typename Arg3,
                 typename Arg4,
                 typename Arg5,
                 typename Arg6,
                 typename Arg7,
                 typename Arg8,
                 typename Arg9,
                 typename Arg10,
                 typename Arg11,
                 Ret (Class::*Method)(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8, Arg9, Arg10, Arg11)>
        static void MethodHandler(const v8::FunctionCallbackInfo<v8::Value>& info)
        {
            Class* obj = dynamic_cast<Class*>(GetThisObjectFromInfo(info));
            if(obj == nullptr)
            {
                info.GetIsolate()->ThrowException(v8::Exception::Error(JSValue("Invalid base object")));
                return;
            }
            if constexpr(std::is_same_v<void, Ret>)
            {
                (obj->*Method)(GetArg<CleanArg<Arg0>>(info, 0),
                               GetArg<CleanArg<Arg1>>(info, 1),
                               GetArg<CleanArg<Arg2>>(info, 2),
                               GetArg<CleanArg<Arg3>>(info, 3),
                               GetArg<CleanArg<Arg4>>(info, 4),
                               GetArg<CleanArg<Arg5>>(info, 5),
                               GetArg<CleanArg<Arg6>>(info, 6),
                               GetArg<CleanArg<Arg7>>(info, 7),
                               GetArg<CleanArg<Arg8>>(info, 8),
                               GetArg<CleanArg<Arg9>>(info, 9),
                               GetArg<CleanArg<Arg10>>(info, 10),
                               GetArg<CleanArg<Arg11>>(info, 11));
            }
            else
            {
                info.GetReturnValue().Set(JSValue((obj->*Method)(GetArg<CleanArg<Arg0>>(info, 0),
                                                                 GetArg<CleanArg<Arg1>>(info, 1),
                                                                 GetArg<CleanArg<Arg2>>(info, 2),
                                                                 GetArg<CleanArg<Arg3>>(info, 3),
                                                                 GetArg<CleanArg<Arg4>>(info, 4),
                                                                 GetArg<CleanArg<Arg5>>(info, 5),
                                                                 GetArg<CleanArg<Arg6>>(info, 6),
                                                                 GetArg<CleanArg<Arg7>>(info, 7),
                                                                 GetArg<CleanArg<Arg8>>(info, 8),
                                                                 GetArg<CleanArg<Arg9>>(info, 9),
                                                                 GetArg<CleanArg<Arg10>>(info, 10),
                                                                 GetArg<CleanArg<Arg11>>(info, 11))));
            }
        }
        template<class Class,
                 typename Ret,
                 typename Arg0,
                 typename Arg1,
                 typename Arg2,
                 typename Arg3,
                 typename Arg4,
                 typename Arg5,
                 typename Arg6,
                 typename Arg7,
                 typename Arg8,
                 typename Arg9,
                 typename Arg10,
                 typename Arg11,
                 Ret (Class::*Method)(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8, Arg9, Arg10, Arg11) const>
        static void MethodHandler(const v8::FunctionCallbackInfo<v8::Value>& info)
        {
            Class* obj = dynamic_cast<Class*>(GetThisObjectFromInfo(info));
            if(obj == nullptr)
            {
                info.GetIsolate()->ThrowException(v8::Exception::Error(JSValue("Invalid base object")));
                return;
            }
            if constexpr(std::is_same_v<void, Ret>)
            {
                (obj->*Method)(GetArg<CleanArg<Arg0>>(info, 0),
                               GetArg<CleanArg<Arg1>>(info, 1),
                               GetArg<CleanArg<Arg2>>(info, 2),
                               GetArg<CleanArg<Arg3>>(info, 3),
                               GetArg<CleanArg<Arg4>>(info, 4),
                               GetArg<CleanArg<Arg5>>(info, 5),
                               GetArg<CleanArg<Arg6>>(info, 6),
                               GetArg<CleanArg<Arg7>>(info, 7),
                               GetArg<CleanArg<Arg8>>(info, 8),
                               GetArg<CleanArg<Arg9>>(info, 9),
                               GetArg<CleanArg<Arg10>>(info, 10),
                               GetArg<CleanArg<Arg11>>(info, 11));
            }
            else
            {
                info.GetReturnValue().Set(JSValue((obj->*Method)(GetArg<CleanArg<Arg0>>(info, 0),
                                                                 GetArg<CleanArg<Arg1>>(info, 1),
                                                                 GetArg<CleanArg<Arg2>>(info, 2),
                                                                 GetArg<CleanArg<Arg3>>(info, 3),
                                                                 GetArg<CleanArg<Arg4>>(info, 4),
                                                                 GetArg<CleanArg<Arg5>>(info, 5),
                                                                 GetArg<CleanArg<Arg6>>(info, 6),
                                                                 GetArg<CleanArg<Arg7>>(info, 7),
                                                                 GetArg<CleanArg<Arg8>>(info, 8),
                                                                 GetArg<CleanArg<Arg9>>(info, 9),
                                                                 GetArg<CleanArg<Arg10>>(info, 10),
                                                                 GetArg<CleanArg<Arg11>>(info, 11))));
            }
        }
        template<class Class,
                 typename Ret,
                 typename Arg0,
                 typename Arg1,
                 typename Arg2,
                 typename Arg3,
                 typename Arg4,
                 typename Arg5,
                 typename Arg6,
                 typename Arg7,
                 typename Arg8,
                 typename Arg9,
                 typename Arg10,
                 typename Arg11,
                 typename Arg12,
                 Ret (Class::*Method)(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8, Arg9, Arg10, Arg11, Arg12)>
        static void MethodHandler(const v8::FunctionCallbackInfo<v8::Value>& info)
        {
            Class* obj = dynamic_cast<Class*>(GetThisObjectFromInfo(info));
            if(obj == nullptr)
            {
                info.GetIsolate()->ThrowException(v8::Exception::Error(JSValue("Invalid base object")));
                return;
            }
            if constexpr(std::is_same_v<void, Ret>)
            {
                (obj->*Method)(GetArg<CleanArg<Arg0>>(info, 0),
                               GetArg<CleanArg<Arg1>>(info, 1),
                               GetArg<CleanArg<Arg2>>(info, 2),
                               GetArg<CleanArg<Arg3>>(info, 3),
                               GetArg<CleanArg<Arg4>>(info, 4),
                               GetArg<CleanArg<Arg5>>(info, 5),
                               GetArg<CleanArg<Arg6>>(info, 6),
                               GetArg<CleanArg<Arg7>>(info, 7),
                               GetArg<CleanArg<Arg8>>(info, 8),
                               GetArg<CleanArg<Arg9>>(info, 9),
                               GetArg<CleanArg<Arg10>>(info, 10),
                               GetArg<CleanArg<Arg11>>(info, 11),
                               GetArg<CleanArg<Arg12>>(info, 12));
            }
            else
            {
                info.GetReturnValue().Set(JSValue((obj->*Method)(GetArg<CleanArg<Arg0>>(info, 0),
                                                                 GetArg<CleanArg<Arg1>>(info, 1),
                                                                 GetArg<CleanArg<Arg2>>(info, 2),
                                                                 GetArg<CleanArg<Arg3>>(info, 3),
                                                                 GetArg<CleanArg<Arg4>>(info, 4),
                                                                 GetArg<CleanArg<Arg5>>(info, 5),
                                                                 GetArg<CleanArg<Arg6>>(info, 6),
                                                                 GetArg<CleanArg<Arg7>>(info, 7),
                                                                 GetArg<CleanArg<Arg8>>(info, 8),
                                                                 GetArg<CleanArg<Arg9>>(info, 9),
                                                                 GetArg<CleanArg<Arg10>>(info, 10),
                                                                 GetArg<CleanArg<Arg11>>(info, 11),
                                                                 GetArg<CleanArg<Arg12>>(info, 12))));
            }
        }
        template<class Class,
                 typename Ret,
                 typename Arg0,
                 typename Arg1,
                 typename Arg2,
                 typename Arg3,
                 typename Arg4,
                 typename Arg5,
                 typename Arg6,
                 typename Arg7,
                 typename Arg8,
                 typename Arg9,
                 typename Arg10,
                 typename Arg11,
                 typename Arg12,
                 Ret (Class::*Method)(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8, Arg9, Arg10, Arg11, Arg12) const>
        static void MethodHandler(const v8::FunctionCallbackInfo<v8::Value>& info)
        {
            Class* obj = dynamic_cast<Class*>(GetThisObjectFromInfo(info));
            if(obj == nullptr)
            {
                info.GetIsolate()->ThrowException(v8::Exception::Error(JSValue("Invalid base object")));
                return;
            }
            if constexpr(std::is_same_v<void, Ret>)
            {
                (obj->*Method)(GetArg<CleanArg<Arg0>>(info, 0),
                               GetArg<CleanArg<Arg1>>(info, 1),
                               GetArg<CleanArg<Arg2>>(info, 2),
                               GetArg<CleanArg<Arg3>>(info, 3),
                               GetArg<CleanArg<Arg4>>(info, 4),
                               GetArg<CleanArg<Arg5>>(info, 5),
                               GetArg<CleanArg<Arg6>>(info, 6),
                               GetArg<CleanArg<Arg7>>(info, 7),
                               GetArg<CleanArg<Arg8>>(info, 8),
                               GetArg<CleanArg<Arg9>>(info, 9),
                               GetArg<CleanArg<Arg10>>(info, 10),
                               GetArg<CleanArg<Arg11>>(info, 11),
                               GetArg<CleanArg<Arg12>>(info, 12));
            }
            else
            {
                info.GetReturnValue().Set(JSValue((obj->*Method)(GetArg<CleanArg<Arg0>>(info, 0),
                                                                 GetArg<CleanArg<Arg1>>(info, 1),
                                                                 GetArg<CleanArg<Arg2>>(info, 2),
                                                                 GetArg<CleanArg<Arg3>>(info, 3),
                                                                 GetArg<CleanArg<Arg4>>(info, 4),
                                                                 GetArg<CleanArg<Arg5>>(info, 5),
                                                                 GetArg<CleanArg<Arg6>>(info, 6),
                                                                 GetArg<CleanArg<Arg7>>(info, 7),
                                                                 GetArg<CleanArg<Arg8>>(info, 8),
                                                                 GetArg<CleanArg<Arg9>>(info, 9),
                                                                 GetArg<CleanArg<Arg10>>(info, 10),
                                                                 GetArg<CleanArg<Arg11>>(info, 11),
                                                                 GetArg<CleanArg<Arg12>>(info, 12))));
            }
        }
        template<class Class,
                 typename Ret,
                 typename Arg0,
                 typename Arg1,
                 typename Arg2,
                 typename Arg3,
                 typename Arg4,
                 typename Arg5,
                 typename Arg6,
                 typename Arg7,
                 typename Arg8,
                 typename Arg9,
                 typename Arg10,
                 typename Arg11,
                 typename Arg12,
                 typename Arg13,
                 Ret (Class::*Method)(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8, Arg9, Arg10, Arg11, Arg12, Arg13)>
        static void MethodHandler(const v8::FunctionCallbackInfo<v8::Value>& info)
        {
            Class* obj = dynamic_cast<Class*>(GetThisObjectFromInfo(info));
            if(obj == nullptr)
            {
                info.GetIsolate()->ThrowException(v8::Exception::Error(JSValue("Invalid base object")));
                return;
            }
            if constexpr(std::is_same_v<void, Ret>)
            {
                (obj->*Method)(GetArg<CleanArg<Arg0>>(info, 0),
                               GetArg<CleanArg<Arg1>>(info, 1),
                               GetArg<CleanArg<Arg2>>(info, 2),
                               GetArg<CleanArg<Arg3>>(info, 3),
                               GetArg<CleanArg<Arg4>>(info, 4),
                               GetArg<CleanArg<Arg5>>(info, 5),
                               GetArg<CleanArg<Arg6>>(info, 6),
                               GetArg<CleanArg<Arg7>>(info, 7),
                               GetArg<CleanArg<Arg8>>(info, 8),
                               GetArg<CleanArg<Arg9>>(info, 9),
                               GetArg<CleanArg<Arg10>>(info, 10),
                               GetArg<CleanArg<Arg11>>(info, 11),
                               GetArg<CleanArg<Arg12>>(info, 12),
                               GetArg<CleanArg<Arg13>>(info, 13));
            }
            else
            {
                info.GetReturnValue().Set(JSValue((obj->*Method)(GetArg<CleanArg<Arg0>>(info, 0),
                                                                 GetArg<CleanArg<Arg1>>(info, 1),
                                                                 GetArg<CleanArg<Arg2>>(info, 2),
                                                                 GetArg<CleanArg<Arg3>>(info, 3),
                                                                 GetArg<CleanArg<Arg4>>(info, 4),
                                                                 GetArg<CleanArg<Arg5>>(info, 5),
                                                                 GetArg<CleanArg<Arg6>>(info, 6),
                                                                 GetArg<CleanArg<Arg7>>(info, 7),
                                                                 GetArg<CleanArg<Arg8>>(info, 8),
                                                                 GetArg<CleanArg<Arg9>>(info, 9),
                                                                 GetArg<CleanArg<Arg10>>(info, 10),
                                                                 GetArg<CleanArg<Arg11>>(info, 11),
                                                                 GetArg<CleanArg<Arg12>>(info, 12),
                                                                 GetArg<CleanArg<Arg13>>(info, 13))));
            }
        }
        template<class Class,
                 typename Ret,
                 typename Arg0,
                 typename Arg1,
                 typename Arg2,
                 typename Arg3,
                 typename Arg4,
                 typename Arg5,
                 typename Arg6,
                 typename Arg7,
                 typename Arg8,
                 typename Arg9,
                 typename Arg10,
                 typename Arg11,
                 typename Arg12,
                 typename Arg13,
                 Ret (Class::*Method)(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8, Arg9, Arg10, Arg11, Arg12, Arg13) const>
        static void MethodHandler(const v8::FunctionCallbackInfo<v8::Value>& info)
        {
            Class* obj = dynamic_cast<Class*>(GetThisObjectFromInfo(info));
            if(obj == nullptr)
            {
                info.GetIsolate()->ThrowException(v8::Exception::Error(JSValue("Invalid base object")));
                return;
            }
            if constexpr(std::is_same_v<void, Ret>)
            {
                (obj->*Method)(GetArg<CleanArg<Arg0>>(info, 0),
                               GetArg<CleanArg<Arg1>>(info, 1),
                               GetArg<CleanArg<Arg2>>(info, 2),
                               GetArg<CleanArg<Arg3>>(info, 3),
                               GetArg<CleanArg<Arg4>>(info, 4),
                               GetArg<CleanArg<Arg5>>(info, 5),
                               GetArg<CleanArg<Arg6>>(info, 6),
                               GetArg<CleanArg<Arg7>>(info, 7),
                               GetArg<CleanArg<Arg8>>(info, 8),
                               GetArg<CleanArg<Arg9>>(info, 9),
                               GetArg<CleanArg<Arg10>>(info, 10),
                               GetArg<CleanArg<Arg11>>(info, 11),
                               GetArg<CleanArg<Arg12>>(info, 12),
                               GetArg<CleanArg<Arg13>>(info, 13));
            }
            else
            {
                info.GetReturnValue().Set(JSValue((obj->*Method)(GetArg<CleanArg<Arg0>>(info, 0),
                                                                 GetArg<CleanArg<Arg1>>(info, 1),
                                                                 GetArg<CleanArg<Arg2>>(info, 2),
                                                                 GetArg<CleanArg<Arg3>>(info, 3),
                                                                 GetArg<CleanArg<Arg4>>(info, 4),
                                                                 GetArg<CleanArg<Arg5>>(info, 5),
                                                                 GetArg<CleanArg<Arg6>>(info, 6),
                                                                 GetArg<CleanArg<Arg7>>(info, 7),
                                                                 GetArg<CleanArg<Arg8>>(info, 8),
                                                                 GetArg<CleanArg<Arg9>>(info, 9),
                                                                 GetArg<CleanArg<Arg10>>(info, 10),
                                                                 GetArg<CleanArg<Arg11>>(info, 11),
                                                                 GetArg<CleanArg<Arg12>>(info, 12),
                                                                 GetArg<CleanArg<Arg13>>(info, 13))));
            }
        }
        template<class Class,
                 typename Ret,
                 typename Arg0,
                 typename Arg1,
                 typename Arg2,
                 typename Arg3,
                 typename Arg4,
                 typename Arg5,
                 typename Arg6,
                 typename Arg7,
                 typename Arg8,
                 typename Arg9,
                 typename Arg10,
                 typename Arg11,
                 typename Arg12,
                 typename Arg13,
                 typename Arg14,
                 Ret (Class::*Method)(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8, Arg9, Arg10, Arg11, Arg12, Arg13, Arg14)>
        static void MethodHandler(const v8::FunctionCallbackInfo<v8::Value>& info)
        {
            Class* obj = dynamic_cast<Class*>(GetThisObjectFromInfo(info));
            if(obj == nullptr)
            {
                info.GetIsolate()->ThrowException(v8::Exception::Error(JSValue("Invalid base object")));
                return;
            }
            if constexpr(std::is_same_v<void, Ret>)
            {
                (obj->*Method)(GetArg<CleanArg<Arg0>>(info, 0),
                               GetArg<CleanArg<Arg1>>(info, 1),
                               GetArg<CleanArg<Arg2>>(info, 2),
                               GetArg<CleanArg<Arg3>>(info, 3),
                               GetArg<CleanArg<Arg4>>(info, 4),
                               GetArg<CleanArg<Arg5>>(info, 5),
                               GetArg<CleanArg<Arg6>>(info, 6),
                               GetArg<CleanArg<Arg7>>(info, 7),
                               GetArg<CleanArg<Arg8>>(info, 8),
                               GetArg<CleanArg<Arg9>>(info, 9),
                               GetArg<CleanArg<Arg10>>(info, 10),
                               GetArg<CleanArg<Arg11>>(info, 11),
                               GetArg<CleanArg<Arg12>>(info, 12),
                               GetArg<CleanArg<Arg13>>(info, 13),
                               GetArg<CleanArg<Arg14>>(info, 14));
            }
            else
            {
                info.GetReturnValue().Set(JSValue((obj->*Method)(GetArg<CleanArg<Arg0>>(info, 0),
                                                                 GetArg<CleanArg<Arg1>>(info, 1),
                                                                 GetArg<CleanArg<Arg2>>(info, 2),
                                                                 GetArg<CleanArg<Arg3>>(info, 3),
                                                                 GetArg<CleanArg<Arg4>>(info, 4),
                                                                 GetArg<CleanArg<Arg5>>(info, 5),
                                                                 GetArg<CleanArg<Arg6>>(info, 6),
                                                                 GetArg<CleanArg<Arg7>>(info, 7),
                                                                 GetArg<CleanArg<Arg8>>(info, 8),
                                                                 GetArg<CleanArg<Arg9>>(info, 9),
                                                                 GetArg<CleanArg<Arg10>>(info, 10),
                                                                 GetArg<CleanArg<Arg11>>(info, 11),
                                                                 GetArg<CleanArg<Arg12>>(info, 12),
                                                                 GetArg<CleanArg<Arg13>>(info, 13),
                                                                 GetArg<CleanArg<Arg14>>(info, 14))));
            }
        }
        template<class Class,
                 typename Ret,
                 typename Arg0,
                 typename Arg1,
                 typename Arg2,
                 typename Arg3,
                 typename Arg4,
                 typename Arg5,
                 typename Arg6,
                 typename Arg7,
                 typename Arg8,
                 typename Arg9,
                 typename Arg10,
                 typename Arg11,
                 typename Arg12,
                 typename Arg13,
                 typename Arg14,
                 Ret (Class::*Method)(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8, Arg9, Arg10, Arg11, Arg12, Arg13, Arg14) const>
        static void MethodHandler(const v8::FunctionCallbackInfo<v8::Value>& info)
        {
            Class* obj = dynamic_cast<Class*>(GetThisObjectFromInfo(info));
            if(obj == nullptr)
            {
                info.GetIsolate()->ThrowException(v8::Exception::Error(JSValue("Invalid base object")));
                return;
            }
            if constexpr(std::is_same_v<void, Ret>)
            {
                (obj->*Method)(GetArg<CleanArg<Arg0>>(info, 0),
                               GetArg<CleanArg<Arg1>>(info, 1),
                               GetArg<CleanArg<Arg2>>(info, 2),
                               GetArg<CleanArg<Arg3>>(info, 3),
                               GetArg<CleanArg<Arg4>>(info, 4),
                               GetArg<CleanArg<Arg5>>(info, 5),
                               GetArg<CleanArg<Arg6>>(info, 6),
                               GetArg<CleanArg<Arg7>>(info, 7),
                               GetArg<CleanArg<Arg8>>(info, 8),
                               GetArg<CleanArg<Arg9>>(info, 9),
                               GetArg<CleanArg<Arg10>>(info, 10),
                               GetArg<CleanArg<Arg11>>(info, 11),
                               GetArg<CleanArg<Arg12>>(info, 12),
                               GetArg<CleanArg<Arg13>>(info, 13),
                               GetArg<CleanArg<Arg14>>(info, 14));
            }
            else
            {
                info.GetReturnValue().Set(JSValue((obj->*Method)(GetArg<CleanArg<Arg0>>(info, 0),
                                                                 GetArg<CleanArg<Arg1>>(info, 1),
                                                                 GetArg<CleanArg<Arg2>>(info, 2),
                                                                 GetArg<CleanArg<Arg3>>(info, 3),
                                                                 GetArg<CleanArg<Arg4>>(info, 4),
                                                                 GetArg<CleanArg<Arg5>>(info, 5),
                                                                 GetArg<CleanArg<Arg6>>(info, 6),
                                                                 GetArg<CleanArg<Arg7>>(info, 7),
                                                                 GetArg<CleanArg<Arg8>>(info, 8),
                                                                 GetArg<CleanArg<Arg9>>(info, 9),
                                                                 GetArg<CleanArg<Arg10>>(info, 10),
                                                                 GetArg<CleanArg<Arg11>>(info, 11),
                                                                 GetArg<CleanArg<Arg12>>(info, 12),
                                                                 GetArg<CleanArg<Arg13>>(info, 13),
                                                                 GetArg<CleanArg<Arg14>>(info, 14))));
            }
        }
        template<class Class,
                 typename Ret,
                 typename Arg0,
                 typename Arg1,
                 typename Arg2,
                 typename Arg3,
                 typename Arg4,
                 typename Arg5,
                 typename Arg6,
                 typename Arg7,
                 typename Arg8,
                 typename Arg9,
                 typename Arg10,
                 typename Arg11,
                 typename Arg12,
                 typename Arg13,
                 typename Arg14,
                 typename Arg15,
                 Ret (Class::*Method)(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8, Arg9, Arg10, Arg11, Arg12, Arg13, Arg14, Arg15)>
        static void MethodHandler(const v8::FunctionCallbackInfo<v8::Value>& info)
        {
            Class* obj = dynamic_cast<Class*>(GetThisObjectFromInfo(info));
            if(obj == nullptr)
            {
                info.GetIsolate()->ThrowException(v8::Exception::Error(JSValue("Invalid base object")));
                return;
            }
            if constexpr(std::is_same_v<void, Ret>)
            {
                (obj->*Method)(GetArg<CleanArg<Arg0>>(info, 0),
                               GetArg<CleanArg<Arg1>>(info, 1),
                               GetArg<CleanArg<Arg2>>(info, 2),
                               GetArg<CleanArg<Arg3>>(info, 3),
                               GetArg<CleanArg<Arg4>>(info, 4),
                               GetArg<CleanArg<Arg5>>(info, 5),
                               GetArg<CleanArg<Arg6>>(info, 6),
                               GetArg<CleanArg<Arg7>>(info, 7),
                               GetArg<CleanArg<Arg8>>(info, 8),
                               GetArg<CleanArg<Arg9>>(info, 9),
                               GetArg<CleanArg<Arg10>>(info, 10),
                               GetArg<CleanArg<Arg11>>(info, 11),
                               GetArg<CleanArg<Arg12>>(info, 12),
                               GetArg<CleanArg<Arg13>>(info, 13),
                               GetArg<CleanArg<Arg14>>(info, 14),
                               GetArg<CleanArg<Arg15>>(info, 15));
            }
            else
            {
                info.GetReturnValue().Set(JSValue((obj->*Method)(GetArg<CleanArg<Arg0>>(info, 0),
                                                                 GetArg<CleanArg<Arg1>>(info, 1),
                                                                 GetArg<CleanArg<Arg2>>(info, 2),
                                                                 GetArg<CleanArg<Arg3>>(info, 3),
                                                                 GetArg<CleanArg<Arg4>>(info, 4),
                                                                 GetArg<CleanArg<Arg5>>(info, 5),
                                                                 GetArg<CleanArg<Arg6>>(info, 6),
                                                                 GetArg<CleanArg<Arg7>>(info, 7),
                                                                 GetArg<CleanArg<Arg8>>(info, 8),
                                                                 GetArg<CleanArg<Arg9>>(info, 9),
                                                                 GetArg<CleanArg<Arg10>>(info, 10),
                                                                 GetArg<CleanArg<Arg11>>(info, 11),
                                                                 GetArg<CleanArg<Arg12>>(info, 12),
                                                                 GetArg<CleanArg<Arg13>>(info, 13),
                                                                 GetArg<CleanArg<Arg14>>(info, 14),
                                                                 GetArg<CleanArg<Arg15>>(info, 15))));
            }
        }
        template<class Class,
                 typename Ret,
                 typename Arg0,
                 typename Arg1,
                 typename Arg2,
                 typename Arg3,
                 typename Arg4,
                 typename Arg5,
                 typename Arg6,
                 typename Arg7,
                 typename Arg8,
                 typename Arg9,
                 typename Arg10,
                 typename Arg11,
                 typename Arg12,
                 typename Arg13,
                 typename Arg14,
                 typename Arg15,
                 Ret (Class::*Method)(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8, Arg9, Arg10, Arg11, Arg12, Arg13, Arg14, Arg15) const>
        static void MethodHandler(const v8::FunctionCallbackInfo<v8::Value>& info)
        {
            Class* obj = dynamic_cast<Class*>(GetThisObjectFromInfo(info));
            if(obj == nullptr)
            {
                info.GetIsolate()->ThrowException(v8::Exception::Error(JSValue("Invalid base object")));
                return;
            }
            if constexpr(std::is_same_v<void, Ret>)
            {
                (obj->*Method)(GetArg<CleanArg<Arg0>>(info, 0),
                               GetArg<CleanArg<Arg1>>(info, 1),
                               GetArg<CleanArg<Arg2>>(info, 2),
                               GetArg<CleanArg<Arg3>>(info, 3),
                               GetArg<CleanArg<Arg4>>(info, 4),
                               GetArg<CleanArg<Arg5>>(info, 5),
                               GetArg<CleanArg<Arg6>>(info, 6),
                               GetArg<CleanArg<Arg7>>(info, 7),
                               GetArg<CleanArg<Arg8>>(info, 8),
                               GetArg<CleanArg<Arg9>>(info, 9),
                               GetArg<CleanArg<Arg10>>(info, 10),
                               GetArg<CleanArg<Arg11>>(info, 11),
                               GetArg<CleanArg<Arg12>>(info, 12),
                               GetArg<CleanArg<Arg13>>(info, 13),
                               GetArg<CleanArg<Arg14>>(info, 14),
                               GetArg<CleanArg<Arg15>>(info, 15));
            }
            else
            {
                info.GetReturnValue().Set(JSValue((obj->*Method)(GetArg<CleanArg<Arg0>>(info, 0),
                                                                 GetArg<CleanArg<Arg1>>(info, 1),
                                                                 GetArg<CleanArg<Arg2>>(info, 2),
                                                                 GetArg<CleanArg<Arg3>>(info, 3),
                                                                 GetArg<CleanArg<Arg4>>(info, 4),
                                                                 GetArg<CleanArg<Arg5>>(info, 5),
                                                                 GetArg<CleanArg<Arg6>>(info, 6),
                                                                 GetArg<CleanArg<Arg7>>(info, 7),
                                                                 GetArg<CleanArg<Arg8>>(info, 8),
                                                                 GetArg<CleanArg<Arg9>>(info, 9),
                                                                 GetArg<CleanArg<Arg10>>(info, 10),
                                                                 GetArg<CleanArg<Arg11>>(info, 11),
                                                                 GetArg<CleanArg<Arg12>>(info, 12),
                                                                 GetArg<CleanArg<Arg13>>(info, 13),
                                                                 GetArg<CleanArg<Arg14>>(info, 14),
                                                                 GetArg<CleanArg<Arg15>>(info, 15))));
            }
        }

#pragma endregion

        void DynamicPropertyLazyHandler(v8::Local<v8::Name> property, const v8::PropertyCallbackInfo<v8::Value>& info);

        void DynamicPropertyGetterHandler(v8::Local<v8::Name> property, const v8::PropertyCallbackInfo<v8::Value>& info);
        void DynamicPropertySetterHandler(v8::Local<v8::Name> property, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<v8::Value>& info);
        void DynamicPropertyDeleterHandler(v8::Local<v8::Name> property, const v8::PropertyCallbackInfo<v8::Boolean>& info);
        void DynamicPropertyEnumeratorHandler(const v8::PropertyCallbackInfo<v8::Array>& info);

    }  // namespace Wrapper

    static v8::Local<v8::FunctionTemplate> WrapFunction(FunctionCallback cb)
    {
        v8::Isolate* isolate = v8::Isolate::GetCurrent();
        v8::Local<v8::FunctionTemplate> tpl = v8::FunctionTemplate::New(isolate, Wrapper::FunctionHandler, v8::External::New(isolate, cb));
        return tpl;
    }

    static v8::Local<v8::FunctionTemplate> WrapProperty(PropertyCallback cb)
    {
        v8::Isolate* isolate = v8::Isolate::GetCurrent();
        v8::Local<v8::FunctionTemplate> tpl = v8::FunctionTemplate::New(isolate, Wrapper::PropertyHandler, v8::External::New(isolate, cb));
        return tpl;
    }

    template<typename TemplateType>
    class Template
    {
        v8::Isolate* isolate;
        Persistent<TemplateType> tpl;

    public:
        Template(v8::Isolate* _isolate, v8::Local<TemplateType> _templ) : isolate(_isolate), tpl(_isolate, _templ) {}

        v8::Local<TemplateType> Get() const
        {
            return tpl.Get(isolate);
        }
        v8::Isolate* GetIsolate() const
        {
            return isolate;
        }

        template<typename T>
        void StaticProperty(const std::string& name, T value)
        {
            Get()->Set(js::JSValue(name), js::JSValue(value), (v8::PropertyAttribute)(v8::PropertyAttribute::ReadOnly | v8::PropertyAttribute::DontDelete));
        }
        void StaticProperty(const std::string& name, PropertyCallback getter, PropertyCallback setter = nullptr)
        {
            // todo: use native data property
            Get()->SetAccessorProperty(js::JSValue(name), WrapProperty(getter), setter ? WrapProperty(setter) : v8::Local<v8::FunctionTemplate>());
        }

        void StaticLazyProperty(const std::string& name, LazyPropertyCallback callback)
        {
            Get()->SetLazyDataProperty(js::JSValue(name), Wrapper::LazyPropertyHandler, v8::External::New(GetIsolate(), callback));
        }

        void StaticFunction(const std::string& name, FunctionCallback callback)
        {
            Get()->Set(js::JSValue(name), WrapFunction(callback), (v8::PropertyAttribute)(v8::PropertyAttribute::ReadOnly | v8::PropertyAttribute::DontDelete));
        }
    };

    class NamespaceTemplate : public Template<v8::ObjectTemplate>
    {
    public:
        NamespaceTemplate(v8::Isolate* isolate, v8::Local<v8::ObjectTemplate> tpl) : Template(isolate, tpl) {}
    };

    class ModuleTemplate : public Template<v8::ObjectTemplate>
    {
    public:
        ModuleTemplate(v8::Isolate* isolate, v8::Local<v8::ObjectTemplate> tpl) : Template(isolate, tpl) {}

        void Namespace(const std::string& name, js::Namespace& namespace_);
        void Namespace(js::Namespace& namespace_);
        // Creates an empty namespace that can be extended by JS bindings
        void Namespace(const std::string& name)
        {
            Get()->Set(js::JSValue(name), v8::ObjectTemplate::New(GetIsolate()));
        }

        void StaticBindingExport(const std::string& name, const std::string& exportName);
    };

    class ClassTemplate : public Template<v8::FunctionTemplate>
    {
    public:
        struct DynamicPropertyData
        {
            DynamicPropertyGetter getter;
            DynamicPropertySetter setter;
            DynamicPropertyDeleter deleter;
            DynamicPropertyEnumerator enumerator;

            DynamicPropertyData(DynamicPropertyGetter _getter, DynamicPropertySetter _setter, DynamicPropertyDeleter _deleter, DynamicPropertyEnumerator _enumerator)
                : getter(_getter), setter(_setter), deleter(_deleter), enumerator(_enumerator)
            {
            }
        };

    private:
        friend class Class;

        Class* class_;

        template<class T>
        using ClassMap = std::unordered_map<v8::Isolate*, std::unordered_map<Class*, T>>;

        static ClassMap<std::unordered_map<std::string, DynamicPropertyData*>>& GetDynamicPropertyDataMap()
        {
            static ClassMap<std::unordered_map<std::string, DynamicPropertyData*>> dynamicPropertyDataMap;
            return dynamicPropertyDataMap;
        }
        static void InsertDynamicPropertyData(v8::Isolate* isolate, Class* cls, const std::string& name, DynamicPropertyData* data)
        {
            auto& dynamicPropertyDataMap = GetDynamicPropertyDataMap();
            auto& clsMap = dynamicPropertyDataMap[isolate];
            auto& nameMap = clsMap[cls];
            nameMap.insert({ name, data });
        }
        static void CleanupDynamicPropertyData(v8::Isolate* isolate)
        {
            auto& dynamicPropertyDataMap = GetDynamicPropertyDataMap();
            {
                auto it = dynamicPropertyDataMap.find(isolate);
                if(it == dynamicPropertyDataMap.end()) return;
                auto& clsMap = it->second;
                for(auto& [_, nameMap] : clsMap)
                {
                    for(auto& [__, data] : nameMap)
                    {
                        delete data;
                    }
                }
            }
            dynamicPropertyDataMap.erase(isolate);
        }

        static ClassMap<std::unordered_map<std::string, Persistent<v8::FunctionTemplate>>>& GetPropertyGetterMap()
        {
            static ClassMap<std::unordered_map<std::string, Persistent<v8::FunctionTemplate>>> propertyGetterMap;
            return propertyGetterMap;
        }
        static void InsertPropertyGetter(v8::Isolate* isolate, Class* cls, const std::string& name, v8::Local<v8::FunctionTemplate> getter)
        {
            auto& propertyGetterMap = GetPropertyGetterMap();
            auto& clsMap = propertyGetterMap[isolate];
            auto& nameMap = clsMap[cls];
            nameMap.insert({ name, Persistent<v8::FunctionTemplate>(isolate, getter) });
        }
        static v8::Local<v8::FunctionTemplate> GetPropertyGetter(v8::Isolate* isolate, Class* cls, const std::string& name);
        static void CleanupPropertyGetterMap(v8::Isolate* isolate)
        {
            GetPropertyGetterMap().erase(isolate);
        }

    public:
        ClassTemplate(v8::Isolate* isolate, Class* _class, v8::Local<v8::FunctionTemplate> tpl) : Template(isolate, tpl), class_(_class) {}

        void Method(const std::string& name, FunctionCallback callback)
        {
            Get()->PrototypeTemplate()->Set(js::JSValue(name), WrapFunction(callback));
        }
#pragma region "Method overloads"
        template<class Class, typename Ret, Ret (Class::*Method)()>
        void Method(const std::string& name)
        {
            Get()->PrototypeTemplate()->Set(js::JSValue(name), v8::FunctionTemplate::New(GetIsolate(), Wrapper::MethodHandler<Class, Ret, Method>));
        }
        template<class Class, typename Ret, Ret (Class::*Method)() const>
        void Method(const std::string& name)
        {
            Get()->PrototypeTemplate()->Set(js::JSValue(name), v8::FunctionTemplate::New(GetIsolate(), Wrapper::MethodHandler<Class, Ret, Method>));
        }
        template<class Class, typename Ret, typename Arg0, Ret (Class::*Method)(Arg0)>
        void Method(const std::string& name)
        {
            Get()->PrototypeTemplate()->Set(js::JSValue(name), v8::FunctionTemplate::New(GetIsolate(), Wrapper::MethodHandler<Class, Ret, Arg0, Method>));
        }
        template<class Class, typename Ret, typename Arg0, Ret (Class::*Method)(Arg0) const>
        void Method(const std::string& name)
        {
            Get()->PrototypeTemplate()->Set(js::JSValue(name), v8::FunctionTemplate::New(GetIsolate(), Wrapper::MethodHandler<Class, Ret, Arg0, Method>));
        }
        template<class Class, typename Ret, typename Arg0, typename Arg1, Ret (Class::*Method)(Arg0, Arg1)>
        void Method(const std::string& name)
        {
            Get()->PrototypeTemplate()->Set(js::JSValue(name), v8::FunctionTemplate::New(GetIsolate(), Wrapper::MethodHandler<Class, Ret, Arg0, Arg1, Method>));
        }
        template<class Class, typename Ret, typename Arg0, typename Arg1, Ret (Class::*Method)(Arg0, Arg1) const>
        void Method(const std::string& name)
        {
            Get()->PrototypeTemplate()->Set(js::JSValue(name), v8::FunctionTemplate::New(GetIsolate(), Wrapper::MethodHandler<Class, Ret, Arg0, Arg1, Method>));
        }
        template<class Class, typename Ret, typename Arg0, typename Arg1, typename Arg2, Ret (Class::*Method)(Arg0, Arg1, Arg2)>
        void Method(const std::string& name)
        {
            Get()->PrototypeTemplate()->Set(js::JSValue(name), v8::FunctionTemplate::New(GetIsolate(), Wrapper::MethodHandler<Class, Ret, Arg0, Arg1, Arg2, Method>));
        }
        template<class Class, typename Ret, typename Arg0, typename Arg1, typename Arg2, Ret (Class::*Method)(Arg0, Arg1, Arg2) const>
        void Method(const std::string& name)
        {
            Get()->PrototypeTemplate()->Set(js::JSValue(name), v8::FunctionTemplate::New(GetIsolate(), Wrapper::MethodHandler<Class, Ret, Arg0, Arg1, Arg2, Method>));
        }
        template<class Class, typename Ret, typename Arg0, typename Arg1, typename Arg2, typename Arg3, Ret (Class::*Method)(Arg0, Arg1, Arg2, Arg3)>
        void Method(const std::string& name)
        {
            Get()->PrototypeTemplate()->Set(js::JSValue(name), v8::FunctionTemplate::New(GetIsolate(), Wrapper::MethodHandler<Class, Ret, Arg0, Arg1, Arg2, Arg3, Method>));
        }
        template<class Class, typename Ret, typename Arg0, typename Arg1, typename Arg2, typename Arg3, Ret (Class::*Method)(Arg0, Arg1, Arg2, Arg3) const>
        void Method(const std::string& name)
        {
            Get()->PrototypeTemplate()->Set(js::JSValue(name), v8::FunctionTemplate::New(GetIsolate(), Wrapper::MethodHandler<Class, Ret, Arg0, Arg1, Arg2, Arg3, Method>));
        }
        template<class Class, typename Ret, typename Arg0, typename Arg1, typename Arg2, typename Arg3, typename Arg4, Ret (Class::*Method)(Arg0, Arg1, Arg2, Arg3, Arg4)>
        void Method(const std::string& name)
        {
            Get()->PrototypeTemplate()->Set(js::JSValue(name), v8::FunctionTemplate::New(GetIsolate(), Wrapper::MethodHandler<Class, Ret, Arg0, Arg1, Arg2, Arg3, Arg4, Method>));
        }
        template<class Class, typename Ret, typename Arg0, typename Arg1, typename Arg2, typename Arg3, typename Arg4, Ret (Class::*Method)(Arg0, Arg1, Arg2, Arg3, Arg4) const>
        void Method(const std::string& name)
        {
            Get()->PrototypeTemplate()->Set(js::JSValue(name), v8::FunctionTemplate::New(GetIsolate(), Wrapper::MethodHandler<Class, Ret, Arg0, Arg1, Arg2, Arg3, Arg4, Method>));
        }
        template<class Class,
                 typename Ret,
                 typename Arg0,
                 typename Arg1,
                 typename Arg2,
                 typename Arg3,
                 typename Arg4,
                 typename Arg5,
                 Ret (Class::*Method)(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5)>
        void Method(const std::string& name)
        {
            Get()->PrototypeTemplate()->Set(js::JSValue(name), v8::FunctionTemplate::New(GetIsolate(), Wrapper::MethodHandler<Class, Ret, Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Method>));
        }
        template<class Class,
                 typename Ret,
                 typename Arg0,
                 typename Arg1,
                 typename Arg2,
                 typename Arg3,
                 typename Arg4,
                 typename Arg5,
                 Ret (Class::*Method)(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5) const>
        void Method(const std::string& name)
        {
            Get()->PrototypeTemplate()->Set(js::JSValue(name), v8::FunctionTemplate::New(GetIsolate(), Wrapper::MethodHandler<Class, Ret, Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Method>));
        }
        template<class Class,
                 typename Ret,
                 typename Arg0,
                 typename Arg1,
                 typename Arg2,
                 typename Arg3,
                 typename Arg4,
                 typename Arg5,
                 typename Arg6,
                 Ret (Class::*Method)(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6)>
        void Method(const std::string& name)
        {
            Get()->PrototypeTemplate()->Set(js::JSValue(name), v8::FunctionTemplate::New(GetIsolate(), Wrapper::MethodHandler<Class, Ret, Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Method>));
        }
        template<class Class,
                 typename Ret,
                 typename Arg0,
                 typename Arg1,
                 typename Arg2,
                 typename Arg3,
                 typename Arg4,
                 typename Arg5,
                 typename Arg6,
                 Ret (Class::*Method)(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6) const>
        void Method(const std::string& name)
        {
            Get()->PrototypeTemplate()->Set(js::JSValue(name), v8::FunctionTemplate::New(GetIsolate(), Wrapper::MethodHandler<Class, Ret, Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Method>));
        }
        template<class Class,
                 typename Ret,
                 typename Arg0,
                 typename Arg1,
                 typename Arg2,
                 typename Arg3,
                 typename Arg4,
                 typename Arg5,
                 typename Arg6,
                 typename Arg7,
                 Ret (Class::*Method)(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7)>
        void Method(const std::string& name)
        {
            Get()->PrototypeTemplate()->Set(js::JSValue(name),
                                            v8::FunctionTemplate::New(GetIsolate(), Wrapper::MethodHandler<Class, Ret, Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Method>));
        }
        template<class Class,
                 typename Ret,
                 typename Arg0,
                 typename Arg1,
                 typename Arg2,
                 typename Arg3,
                 typename Arg4,
                 typename Arg5,
                 typename Arg6,
                 typename Arg7,
                 Ret (Class::*Method)(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7) const>
        void Method(const std::string& name)
        {
            Get()->PrototypeTemplate()->Set(js::JSValue(name),
                                            v8::FunctionTemplate::New(GetIsolate(), Wrapper::MethodHandler<Class, Ret, Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Method>));
        }
        template<class Class,
                 typename Ret,
                 typename Arg0,
                 typename Arg1,
                 typename Arg2,
                 typename Arg3,
                 typename Arg4,
                 typename Arg5,
                 typename Arg6,
                 typename Arg7,
                 typename Arg8,
                 Ret (Class::*Method)(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8)>
        void Method(const std::string& name)
        {
            Get()->PrototypeTemplate()->Set(js::JSValue(name),
                                            v8::FunctionTemplate::New(GetIsolate(), Wrapper::MethodHandler<Class, Ret, Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8, Method>));
        }
        template<class Class,
                 typename Ret,
                 typename Arg0,
                 typename Arg1,
                 typename Arg2,
                 typename Arg3,
                 typename Arg4,
                 typename Arg5,
                 typename Arg6,
                 typename Arg7,
                 typename Arg8,
                 Ret (Class::*Method)(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8) const>
        void Method(const std::string& name)
        {
            Get()->PrototypeTemplate()->Set(js::JSValue(name),
                                            v8::FunctionTemplate::New(GetIsolate(), Wrapper::MethodHandler<Class, Ret, Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8, Method>));
        }
        template<class Class,
                 typename Ret,
                 typename Arg0,
                 typename Arg1,
                 typename Arg2,
                 typename Arg3,
                 typename Arg4,
                 typename Arg5,
                 typename Arg6,
                 typename Arg7,
                 typename Arg8,
                 typename Arg9,
                 Ret (Class::*Method)(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8, Arg9)>
        void Method(const std::string& name)
        {
            Get()->PrototypeTemplate()->Set(js::JSValue(name),
                                            v8::FunctionTemplate::New(GetIsolate(), Wrapper::MethodHandler<Class, Ret, Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8, Arg9, Method>));
        }
        template<class Class,
                 typename Ret,
                 typename Arg0,
                 typename Arg1,
                 typename Arg2,
                 typename Arg3,
                 typename Arg4,
                 typename Arg5,
                 typename Arg6,
                 typename Arg7,
                 typename Arg8,
                 typename Arg9,
                 Ret (Class::*Method)(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8, Arg9) const>
        void Method(const std::string& name)
        {
            Get()->PrototypeTemplate()->Set(js::JSValue(name),
                                            v8::FunctionTemplate::New(GetIsolate(), Wrapper::MethodHandler<Class, Ret, Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8, Arg9, Method>));
        }
        template<class Class,
                 typename Ret,
                 typename Arg0,
                 typename Arg1,
                 typename Arg2,
                 typename Arg3,
                 typename Arg4,
                 typename Arg5,
                 typename Arg6,
                 typename Arg7,
                 typename Arg8,
                 typename Arg9,
                 typename Arg10,
                 Ret (Class::*Method)(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8, Arg9, Arg10)>
        void Method(const std::string& name)
        {
            Get()->PrototypeTemplate()->Set(
              js::JSValue(name), v8::FunctionTemplate::New(GetIsolate(), Wrapper::MethodHandler<Class, Ret, Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8, Arg9, Arg10, Method>));
        }
        template<class Class,
                 typename Ret,
                 typename Arg0,
                 typename Arg1,
                 typename Arg2,
                 typename Arg3,
                 typename Arg4,
                 typename Arg5,
                 typename Arg6,
                 typename Arg7,
                 typename Arg8,
                 typename Arg9,
                 typename Arg10,
                 Ret (Class::*Method)(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8, Arg9, Arg10) const>
        void Method(const std::string& name)
        {
            Get()->PrototypeTemplate()->Set(
              js::JSValue(name), v8::FunctionTemplate::New(GetIsolate(), Wrapper::MethodHandler<Class, Ret, Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8, Arg9, Arg10, Method>));
        }
        template<class Class,
                 typename Ret,
                 typename Arg0,
                 typename Arg1,
                 typename Arg2,
                 typename Arg3,
                 typename Arg4,
                 typename Arg5,
                 typename Arg6,
                 typename Arg7,
                 typename Arg8,
                 typename Arg9,
                 typename Arg10,
                 typename Arg11,
                 Ret (Class::*Method)(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8, Arg9, Arg10, Arg11)>
        void Method(const std::string& name)
        {
            Get()->PrototypeTemplate()->Set(
              js::JSValue(name),
              v8::FunctionTemplate::New(GetIsolate(), Wrapper::MethodHandler<Class, Ret, Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8, Arg9, Arg10, Arg11, Method>));
        }
        template<class Class,
                 typename Ret,
                 typename Arg0,
                 typename Arg1,
                 typename Arg2,
                 typename Arg3,
                 typename Arg4,
                 typename Arg5,
                 typename Arg6,
                 typename Arg7,
                 typename Arg8,
                 typename Arg9,
                 typename Arg10,
                 typename Arg11,
                 Ret (Class::*Method)(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8, Arg9, Arg10, Arg11) const>
        void Method(const std::string& name)
        {
            Get()->PrototypeTemplate()->Set(
              js::JSValue(name),
              v8::FunctionTemplate::New(GetIsolate(), Wrapper::MethodHandler<Class, Ret, Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8, Arg9, Arg10, Arg11, Method>));
        }
        template<class Class,
                 typename Ret,
                 typename Arg0,
                 typename Arg1,
                 typename Arg2,
                 typename Arg3,
                 typename Arg4,
                 typename Arg5,
                 typename Arg6,
                 typename Arg7,
                 typename Arg8,
                 typename Arg9,
                 typename Arg10,
                 typename Arg11,
                 typename Arg12,
                 Ret (Class::*Method)(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8, Arg9, Arg10, Arg11, Arg12)>
        void Method(const std::string& name)
        {
            Get()->PrototypeTemplate()->Set(
              js::JSValue(name),
              v8::FunctionTemplate::New(GetIsolate(), Wrapper::MethodHandler<Class, Ret, Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8, Arg9, Arg10, Arg11, Arg12, Method>));
        }
        template<class Class,
                 typename Ret,
                 typename Arg0,
                 typename Arg1,
                 typename Arg2,
                 typename Arg3,
                 typename Arg4,
                 typename Arg5,
                 typename Arg6,
                 typename Arg7,
                 typename Arg8,
                 typename Arg9,
                 typename Arg10,
                 typename Arg11,
                 typename Arg12,
                 Ret (Class::*Method)(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8, Arg9, Arg10, Arg11, Arg12) const>
        void Method(const std::string& name)
        {
            Get()->PrototypeTemplate()->Set(
              js::JSValue(name),
              v8::FunctionTemplate::New(GetIsolate(), Wrapper::MethodHandler<Class, Ret, Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8, Arg9, Arg10, Arg11, Arg12, Method>));
        }
        template<class Class,
                 typename Ret,
                 typename Arg0,
                 typename Arg1,
                 typename Arg2,
                 typename Arg3,
                 typename Arg4,
                 typename Arg5,
                 typename Arg6,
                 typename Arg7,
                 typename Arg8,
                 typename Arg9,
                 typename Arg10,
                 typename Arg11,
                 typename Arg12,
                 typename Arg13,
                 Ret (Class::*Method)(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8, Arg9, Arg10, Arg11, Arg12, Arg13)>
        void Method(const std::string& name)
        {
            Get()->PrototypeTemplate()->Set(
              js::JSValue(name),
              v8::FunctionTemplate::New(GetIsolate(), Wrapper::MethodHandler<Class, Ret, Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8, Arg9, Arg10, Arg11, Arg12, Arg13, Method>));
        }
        template<class Class,
                 typename Ret,
                 typename Arg0,
                 typename Arg1,
                 typename Arg2,
                 typename Arg3,
                 typename Arg4,
                 typename Arg5,
                 typename Arg6,
                 typename Arg7,
                 typename Arg8,
                 typename Arg9,
                 typename Arg10,
                 typename Arg11,
                 typename Arg12,
                 typename Arg13,
                 Ret (Class::*Method)(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8, Arg9, Arg10, Arg11, Arg12, Arg13) const>
        void Method(const std::string& name)
        {
            Get()->PrototypeTemplate()->Set(
              js::JSValue(name),
              v8::FunctionTemplate::New(GetIsolate(), Wrapper::MethodHandler<Class, Ret, Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8, Arg9, Arg10, Arg11, Arg12, Arg13, Method>));
        }
        template<class Class,
                 typename Ret,
                 typename Arg0,
                 typename Arg1,
                 typename Arg2,
                 typename Arg3,
                 typename Arg4,
                 typename Arg5,
                 typename Arg6,
                 typename Arg7,
                 typename Arg8,
                 typename Arg9,
                 typename Arg10,
                 typename Arg11,
                 typename Arg12,
                 typename Arg13,
                 typename Arg14,
                 Ret (Class::*Method)(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8, Arg9, Arg10, Arg11, Arg12, Arg13, Arg14)>
        void Method(const std::string& name)
        {
            Get()->PrototypeTemplate()->Set(
              js::JSValue(name),
              v8::FunctionTemplate::New(GetIsolate(),
                                        Wrapper::MethodHandler<Class, Ret, Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8, Arg9, Arg10, Arg11, Arg12, Arg13, Arg14, Method>));
        }
        template<class Class,
                 typename Ret,
                 typename Arg0,
                 typename Arg1,
                 typename Arg2,
                 typename Arg3,
                 typename Arg4,
                 typename Arg5,
                 typename Arg6,
                 typename Arg7,
                 typename Arg8,
                 typename Arg9,
                 typename Arg10,
                 typename Arg11,
                 typename Arg12,
                 typename Arg13,
                 typename Arg14,
                 Ret (Class::*Method)(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8, Arg9, Arg10, Arg11, Arg12, Arg13, Arg14) const>
        void Method(const std::string& name)
        {
            Get()->PrototypeTemplate()->Set(
              js::JSValue(name),
              v8::FunctionTemplate::New(GetIsolate(),
                                        Wrapper::MethodHandler<Class, Ret, Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8, Arg9, Arg10, Arg11, Arg12, Arg13, Arg14, Method>));
        }
        template<class Class,
                 typename Ret,
                 typename Arg0,
                 typename Arg1,
                 typename Arg2,
                 typename Arg3,
                 typename Arg4,
                 typename Arg5,
                 typename Arg6,
                 typename Arg7,
                 typename Arg8,
                 typename Arg9,
                 typename Arg10,
                 typename Arg11,
                 typename Arg12,
                 typename Arg13,
                 typename Arg14,
                 typename Arg15,
                 Ret (Class::*Method)(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8, Arg9, Arg10, Arg11, Arg12, Arg13, Arg14, Arg15)>
        void Method(const std::string& name)
        {
            Get()->PrototypeTemplate()->Set(
              js::JSValue(name),
              v8::FunctionTemplate::New(GetIsolate(),
                                        Wrapper::MethodHandler<Class, Ret, Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8, Arg9, Arg10, Arg11, Arg12, Arg13, Arg14, Arg15, Method>));
        }
        template<class Class,
                 typename Ret,
                 typename Arg0,
                 typename Arg1,
                 typename Arg2,
                 typename Arg3,
                 typename Arg4,
                 typename Arg5,
                 typename Arg6,
                 typename Arg7,
                 typename Arg8,
                 typename Arg9,
                 typename Arg10,
                 typename Arg11,
                 typename Arg12,
                 typename Arg13,
                 typename Arg14,
                 typename Arg15,
                 Ret (Class::*Method)(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8, Arg9, Arg10, Arg11, Arg12, Arg13, Arg14, Arg15) const>
        void Method(const std::string& name)
        {
            Get()->PrototypeTemplate()->Set(
              js::JSValue(name),
              v8::FunctionTemplate::New(GetIsolate(),
                                        Wrapper::MethodHandler<Class, Ret, Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8, Arg9, Arg10, Arg11, Arg12, Arg13, Arg14, Arg15, Method>));
        }

#pragma endregion

        template<class Class, auto(Class::*Getter)() const>
        void Property(const std::string& name)
        {
            Get()->PrototypeTemplate()->SetAccessor(js::JSValue(name), Wrapper::PropertyGetterHandler<Class, Getter>);
        }
        template<class Class, typename Type, Type (Class::*Getter)() const, void (Class::*Setter)(Type)>
        void Property(const std::string& name)
        {
            Get()->PrototypeTemplate()->SetAccessor(js::JSValue(name), Wrapper::PropertyGetterHandler<Class, Getter>, Wrapper::PropertySetterHandler<Class, Type, Setter>);
        }
        // If getter is nullptr, tries to get the getter defined by a base class
        void Property(const std::string& name, PropertyCallback getter = nullptr, PropertyCallback setter = nullptr)
        {
            if(getter && !setter)
            {
                v8::Local<v8::FunctionTemplate> getterTemplate = WrapProperty(getter);
                InsertPropertyGetter(GetIsolate(), class_, name, getterTemplate);
                Get()->PrototypeTemplate()->SetAccessorProperty(js::JSValue(name), getterTemplate);
            }
            else
            {
                v8::Local<v8::FunctionTemplate> getterTemplate;
                if(!getter)
                {
                    getterTemplate = GetPropertyGetter(GetIsolate(), class_, name);
                    if(getterTemplate.IsEmpty()) return;
                }
                else
                    getterTemplate = WrapProperty(getter);
                Get()->PrototypeTemplate()->SetAccessorProperty(js::JSValue(name), getterTemplate, WrapProperty(setter));
            }
        }

        template<class Class, auto(Class::*Getter)() const>
        void LazyProperty(const std::string& name)
        {
            Get()->InstanceTemplate()->SetLazyDataProperty(js::JSValue(name), Wrapper::LazyPropertyHandler<Class, Getter>);
        }
        void LazyProperty(const std::string& name, LazyPropertyCallback callback)
        {
            Get()->InstanceTemplate()->SetLazyDataProperty(js::JSValue(name), Wrapper::LazyPropertyHandler, v8::External::New(GetIsolate(), callback));
        }

        // Property returns an object that will call the specified handlers
        void DynamicProperty(const std::string& name,
                             DynamicPropertyGetter getter,
                             DynamicPropertySetter setter = nullptr,
                             DynamicPropertyDeleter deleter = nullptr,
                             DynamicPropertyEnumerator enumerator = nullptr)
        {
            DynamicPropertyData* data = new DynamicPropertyData(getter, setter, deleter, enumerator);
            InsertDynamicPropertyData(GetIsolate(), class_, name, data);
            Get()->PrototypeTemplate()->SetLazyDataProperty(js::JSValue(name), Wrapper::DynamicPropertyLazyHandler, v8::External::New(GetIsolate(), data));
        }

        // Allows instances of this class to be called as a function
        void CallHandler(FunctionCallback cb)
        {
            Get()->PrototypeTemplate()->SetCallAsFunctionHandler(Wrapper::FunctionHandler, v8::External::New(GetIsolate(), cb));
        }

        void BindToType(alt::IBaseObject::Type type);
    };
}  // namespace js
