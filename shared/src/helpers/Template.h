#pragma once

#include <type_traits>

#include "v8.h"
#include "JS.h"
#include "Convert.h"
#include "FunctionContext.h"

namespace js
{
    class Namespace;

    using FunctionCallback = void (*)(FunctionContext&);

    namespace Wrapper
    {
        alt::IBaseObject* GetThisObjectFromInfo(const v8::PropertyCallbackInfo<v8::Value>& info);
        alt::IBaseObject* GetThisObjectFromInfo(const v8::FunctionCallbackInfo<v8::Value>& info);

        static void FunctionHandler(const v8::FunctionCallbackInfo<v8::Value>& info)
        {
            FunctionContext ctx{ info };
            auto callback = static_cast<FunctionCallback>(info.Data().As<v8::External>()->Value());
            callback(ctx);
        }

        template<class Class, auto(Class::*Getter)() const>
        static void PropertyGetterHandler(v8::Local<v8::String>, const v8::PropertyCallbackInfo<v8::Value>& info)
        {
            Class* obj = dynamic_cast<Class*>(GetThisObjectFromInfo(info));
            if(obj == nullptr) return;
            constexpr bool isEnum = std::is_enum_v<decltype((obj->*Getter)())>;
            if constexpr(isEnum) info.GetReturnValue().Set(JSValue((int)(obj->*Getter)()));
            else
                info.GetReturnValue().Set(JSValue((obj->*Getter)()));
        }
        template<class Class, typename Type, void (Class::*Setter)(Type)>
        static void PropertySetterHandler(v8::Local<v8::String>, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<v8::Value>& info)
        {
            Class* obj = dynamic_cast<Class*>(GetThisObjectFromInfo(info));
            if(obj == nullptr) return;
            constexpr bool isEnum = std::is_enum_v<Type>;
            if constexpr(isEnum) (obj->*Setter)(static_cast<Type>(value->Int32Value().ToChecked()));
            else
                (obj->*Setter)(CppValue<typename std::remove_cv_t<typename std::remove_reference_t<Type>>>(value));
        }

#pragma region "Template method handlers"
        template<class Class, typename Ret, Ret (Class::*Method)()>
        static void MethodHandler(const v8::FunctionCallbackInfo<v8::Value>& info)
        {
            Class* obj = dynamic_cast<Class*>(GetThisObjectFromInfo(info));
            if(obj == nullptr) return;
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
            if(obj == nullptr) return;
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

        template<class Class, typename Ret, typename Arg0, Ret (Class::*Method)(Arg0)>
        static void MethodHandler(const v8::FunctionCallbackInfo<v8::Value>& info)
        {
            Class* obj = dynamic_cast<Class*>(GetThisObjectFromInfo(info));
            if(obj == nullptr) return;
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
            if(obj == nullptr) return;
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
            if(obj == nullptr) return;
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
            if(obj == nullptr) return;
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
            if(obj == nullptr) return;
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
            if(obj == nullptr) return;
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
            if(obj == nullptr) return;
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
            if(obj == nullptr) return;
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
            if(obj == nullptr) return;
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
            if(obj == nullptr) return;
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
            if(obj == nullptr) return;
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
            if(obj == nullptr) return;
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
            if(obj == nullptr) return;
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
            if(obj == nullptr) return;
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
            if(obj == nullptr) return;
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
            if(obj == nullptr) return;
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
            if(obj == nullptr) return;
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
            if(obj == nullptr) return;
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
            if(obj == nullptr) return;
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
            if(obj == nullptr) return;
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
            if(obj == nullptr) return;
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
            if(obj == nullptr) return;
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
            if(obj == nullptr) return;
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
            if(obj == nullptr) return;
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
            if(obj == nullptr) return;
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
            if(obj == nullptr) return;
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
            if(obj == nullptr) return;
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
            if(obj == nullptr) return;
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
            if(obj == nullptr) return;
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
            if(obj == nullptr) return;
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
            if(obj == nullptr) return;
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
            if(obj == nullptr) return;
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

    }  // namespace Wrapper

    static v8::Local<v8::FunctionTemplate> WrapFunction(FunctionCallback cb)
    {
        v8::Isolate* isolate = v8::Isolate::GetCurrent();
        v8::Local<v8::FunctionTemplate> tpl = v8::FunctionTemplate::New(isolate, Wrapper::FunctionHandler, v8::External::New(isolate, cb));
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
            Get()->Set(js::JSValue(name), js::JSValue(value));
        }

        void StaticFunction(const std::string& name, FunctionCallback callback)
        {
            Get()->Set(js::JSValue(name), WrapFunction(callback));
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

        void Namespace(const std::string& name, Namespace& namespace_);
        // Creates an empty namespace that can be extended by JS bindings
        void Namespace(const std::string& name)
        {
            Get()->Set(js::JSValue(name), v8::ObjectTemplate::New(GetIsolate()));
        }
    };

    class ClassTemplate : public Template<v8::FunctionTemplate>
    {
    public:
        ClassTemplate(v8::Isolate* isolate, v8::Local<v8::FunctionTemplate> tpl) : Template(isolate, tpl) {}

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
    };
}  // namespace js
