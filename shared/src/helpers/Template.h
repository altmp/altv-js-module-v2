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
            constexpr bool isEnum = std::is_enum_v<decltype((obj->*Getter)())>;
            if constexpr(isEnum) info.GetReturnValue().Set(JSValue((int)(obj->*Getter)()));
            else
                info.GetReturnValue().Set(JSValue((obj->*Getter)()));
        }
        template<class Class, typename Type, void (Class::*Setter)(Type)>
        static void PropertySetterHandler(v8::Local<v8::String>, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<v8::Value>& info)
        {
            Class* obj = dynamic_cast<Class*>(GetThisObjectFromInfo(info));
            constexpr bool isEnum = std::is_enum_v<Type>;
            if constexpr(isEnum) (obj->*Setter)(static_cast<Type>(value->Int32Value().ToChecked()));
            else
                (obj->*Setter)(CppValue<typename std::remove_cv<typename std::remove_reference<Type>::type>::type>(value));
        }
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

        template<class Class, auto(Class::*Getter)() const>
        void Property(const std::string& name)
        {
            Get()->PrototypeTemplate()->SetAccessor(js::JSValue(name), Wrapper::PropertyGetterHandler<Class, Getter>);
        }
        template<class Class, typename Type, auto(Class::*Getter)() const, void (Class::*Setter)(Type)>
        void Property(const std::string& name)
        {
            Get()->PrototypeTemplate()->SetAccessor(js::JSValue(name), Wrapper::PropertyGetterHandler<Class, Getter>, Wrapper::PropertySetterHandler<Class, Type, Setter>);
        }
    };
}  // namespace js
