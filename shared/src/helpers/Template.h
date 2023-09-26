#pragma once

#include <type_traits>

#include "v8.h"

#include "JS.h"
#include "Convert.h"
#include "CallContext.h"
#include "Logger.h"
#include "Callbacks.h"

template<auto x>
struct function_traits;

template<class Class, class Return, class... Args, Return (Class::*FuncPtr)(Args...)>
struct function_traits<FuncPtr>
{
    using ClassType = Class;
    using ReturnType = Return;
    typedef Return (Class::*FunctionPointerType)(Args...);
    using Arguments = std::tuple<Args...>;

    static constexpr decltype(FuncPtr) FunctionPtr = FuncPtr;
};

template<class Class, class Return, class... Args, Return (Class::*FuncPtr)(Args...) const>
struct function_traits<FuncPtr>
{
    using ClassType = Class;
    using ReturnType = Return;
    typedef Return (Class::*FunctionPointerType)(Args...);
    using Arguments = std::tuple<Args...>;

    static constexpr decltype(FuncPtr) FunctionPtr = FuncPtr;
};

namespace js
{
    class Namespace;
    class Class;

    namespace Wrapper
    {
        template<class T>
        using CleanArg = typename std::remove_cv_t<typename std::remove_reference_t<T>>;

        static void FunctionHandler(const v8::FunctionCallbackInfo<v8::Value>& info)
        {
            FunctionContext ctx{ info };
            auto callback = reinterpret_cast<internal::FunctionCallback>(info.Data().As<v8::External>()->Value());
            callback(ctx);
        }

        static void PropertyHandler(const v8::FunctionCallbackInfo<v8::Value>& info)
        {
            PropertyContext ctx{ info, info[0] };
            auto callback = reinterpret_cast<internal::PropertyCallback>(info.Data().As<v8::External>()->Value());
            callback(ctx);
        }

        static void LazyPropertyHandler(v8::Local<v8::Name>, const v8::PropertyCallbackInfo<v8::Value>& info)
        {
            LazyPropertyContext ctx{ info };
            auto callback = reinterpret_cast<internal::LazyPropertyCallback>(info.Data().As<v8::External>()->Value());
            callback(ctx);
        }

        class BadArgException : public std::exception
        {
            std::string msg;

        public:
            BadArgException(const std::string& _msg) : msg(_msg) {}

            const char* what() const noexcept override
            {
                return msg.c_str();
            }
        };

        template<class T>
        inline T GetArg(FunctionContext& ctx, int i)
        {
            T value;
            if(!ctx.GetArg(i, value)) throw BadArgException(ctx.GetError());
            return value;
        }

        template<auto Func>
        static void MethodHandler(const v8::FunctionCallbackInfo<v8::Value>& info)
        {
            using FT = function_traits<Func>;
            using Class = FT::ClassType;
            using Return = FT::ReturnType;
            using Arguments = FT::Arguments;

            FunctionContext ctx{ info };
            if(!ctx.CheckThis()) return;

            ctx.MarkAsNoThrow();
            Class* obj = ctx.GetThisObject<Class>();
            js::IResource* resource = ctx.GetResource();

            try
            {
                auto MakeTuple = [&]<size_t... Ints>(std::index_sequence<Ints...>)->auto
                {
                    return std::make_tuple(Wrapper::GetArg<Wrapper::CleanArg<std::tuple_element_t<Ints, Arguments>>>(ctx, Ints)...);
                };

                auto values = MakeTuple(std::make_index_sequence<std::tuple_size_v<Arguments>>());
                if constexpr(std::is_same_v<void, Return>) std::apply(std::bind_front(Func, obj), values);
                else
                    ctx.Return(std::apply(std::bind_front(Func, obj), values));
            }
            catch(BadArgException& e)
            {
                js::Throw(e.what());
            }
        }
        template<auto Getter>
        static void PropertyGetterHandler(v8::Local<v8::String>, const v8::PropertyCallbackInfo<v8::Value>& info)
        {
            using FT = function_traits<Getter>;
            using Class = FT::ClassType;

            PropertyContextBase<v8::PropertyCallbackInfo<v8::Value>> ctx{ info };
            if(!ctx.CheckThis()) return;

            Class* obj = ctx.GetThisObject<Class>();
            ctx.Return((obj->*Getter)());
        }
        template<auto Setter>
        static void PropertySetterHandler(v8::Local<v8::String>, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void>& info)
        {
            using FT = function_traits<Setter>;
            using Class = FT::ClassType;
            using Arguments = FT::Arguments;
            using Type = std::tuple_element_t<0, Arguments>;
            using CleanType = CleanArg<Type>;

            PropertyContextBase<v8::PropertyCallbackInfo<void>> ctx{ info, value };
            if(!ctx.CheckThis()) return;

            Class* obj = ctx.GetThisObject<Class>();
            CleanType val;
            if(!ctx.GetValue(val)) return;
            (obj->*Setter)(val);
        }
        template<auto Getter>
        static void LazyPropertyHandler(v8::Local<v8::Name>, const v8::PropertyCallbackInfo<v8::Value>& info)
        {
            using FT = function_traits<Getter>;
            using Class = FT::ClassType;

            PropertyContextBase<v8::PropertyCallbackInfo<v8::Value>> ctx{ info };
            if(!ctx.CheckThis()) return;

            Class* obj = ctx.GetThisObject<Class>();
            ctx.Return((obj->*Getter)());
        }

        void DynamicPropertyLazyHandler(v8::Local<v8::Name> property, const v8::PropertyCallbackInfo<v8::Value>& info);

        void DynamicPropertyGetterHandler(v8::Local<v8::Name> property, const v8::PropertyCallbackInfo<v8::Value>& info);
        void DynamicPropertySetterHandler(v8::Local<v8::Name> property, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<v8::Value>& info);
        void DynamicPropertyDeleterHandler(v8::Local<v8::Name> property, const v8::PropertyCallbackInfo<v8::Boolean>& info);
        void DynamicPropertyEnumeratorHandler(const v8::PropertyCallbackInfo<v8::Array>& info);

        template<alt::IBaseObject::Type Type>
        void GetByIDHandler(FunctionContext& ctx)
        {
            if(!ctx.CheckArgCount(1)) return;

            uint32_t id;
            if(!ctx.GetArg(0, id)) return;

            alt::IBaseObject* entity = alt::ICore::Instance().GetBaseObjectByID(Type, id);
            ctx.Return(entity);
        }

#ifdef ALT_CLIENT_API
        template<alt::IBaseObject::Type Type>
        void GetByRemoteIDHandler(FunctionContext& ctx)
        {
            if(!ctx.CheckArgCount(1)) return;

            uint32_t id;
            if(!ctx.GetArg(0, id)) return;

            alt::IBaseObject* entity = alt::ICore::Instance().GetBaseObjectByRemoteID(Type, id);
            ctx.Return(entity);
        }
#endif
    }  // namespace Wrapper

    static v8::Local<v8::FunctionTemplate> WrapFunction(internal::FunctionCallback cb)
    {
        v8::Isolate* isolate = v8::Isolate::GetCurrent();
        v8::Local<v8::FunctionTemplate> tpl = v8::FunctionTemplate::New(isolate, Wrapper::FunctionHandler, v8::External::New(isolate, (void*)cb));
        return tpl;
    }

    static v8::Local<v8::FunctionTemplate> WrapProperty(internal::PropertyCallback cb)
    {
        v8::Isolate* isolate = v8::Isolate::GetCurrent();
        v8::Local<v8::FunctionTemplate> tpl = v8::FunctionTemplate::New(isolate, Wrapper::PropertyHandler, v8::External::New(isolate, (void*)cb));
        return tpl;
    }

    template<typename TemplateType>
    class Template
    {
        v8::Isolate* isolate;
        Persistent<TemplateType> tpl;

    public:
        struct DynamicPropertyData
        {
            internal::DynamicPropertyGetter getter;
            internal::DynamicPropertySetter setter;
            internal::DynamicPropertyDeleter deleter;
            internal::DynamicPropertyEnumerator enumerator;

            DynamicPropertyData(internal::DynamicPropertyGetter _getter,
                                internal::DynamicPropertySetter _setter,
                                internal::DynamicPropertyDeleter _deleter,
                                internal::DynamicPropertyEnumerator _enumerator)
                : getter(_getter), setter(_setter), deleter(_deleter), enumerator(_enumerator)
            {
            }
        };

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
        void StaticProperty(const std::string& name, const T& value)
        {
            static_assert(IsJSValueConvertible<T>, "Type is not convertible to JS value");
            Get()->Set(js::JSValue(name), js::JSValue(value), (v8::PropertyAttribute)(v8::PropertyAttribute::ReadOnly | v8::PropertyAttribute::DontDelete));
        }
        void StaticProperty(const std::string& name, internal::PropertyCallback getter, internal::PropertyCallback setter = nullptr)
        {
            Get()->SetAccessorProperty(js::JSValue(name), WrapProperty(getter), setter ? WrapProperty(setter) : v8::Local<v8::FunctionTemplate>());
        }
        // Property returns an object that will call the specified handlers
        void StaticDynamicProperty(const std::string& name,
                                   internal::DynamicPropertyGetter getter,
                                   internal::DynamicPropertySetter setter = nullptr,
                                   internal::DynamicPropertyDeleter deleter = nullptr,
                                   internal::DynamicPropertyEnumerator enumerator = nullptr)
        {
            DynamicPropertyData* data = new DynamicPropertyData(getter, setter, deleter, enumerator);
            Get()->SetLazyDataProperty(js::JSValue(name), Wrapper::DynamicPropertyLazyHandler, v8::External::New(GetIsolate(), data));
        }

        void StaticLazyProperty(const std::string& name, internal::LazyPropertyCallback callback)
        {
            Get()->SetLazyDataProperty(js::JSValue(name), Wrapper::LazyPropertyHandler, v8::External::New(GetIsolate(), (void*)callback));
        }

        virtual void StaticFunction(const std::string& name, internal::FunctionCallback callback)
        {
            Get()->Set(js::JSValue(name), WrapFunction(callback), (v8::PropertyAttribute)(v8::PropertyAttribute::ReadOnly | v8::PropertyAttribute::DontDelete));
        }

        void StaticFunction(const std::string& name, v8::Local<v8::FunctionTemplate> callbackTpl)
        {
            Get()->Set(js::JSValue(name), callbackTpl, (v8::PropertyAttribute)(v8::PropertyAttribute::ReadOnly | v8::PropertyAttribute::DontDelete));
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
        friend class Class;

        Class* class_;

#ifdef DEBUG_BINDINGS
        std::unordered_map<std::string, std::string> registeredKeys;

        void RegisterKey(const std::string& type, const std::string& key)
        {
            registeredKeys.insert({ key, type });
        }
#endif

        std::unordered_map<std::string, js::internal::FunctionCallback> staticMethods;

        template<class T>
        using ClassMap = std::unordered_map<v8::Isolate*, std::unordered_map<Class*, T>>;

        static ClassMap<std::unordered_map<std::string, DynamicPropertyData*>>& GetDynamicPropertyDataMap()
        {
            static ClassMap<std::unordered_map<std::string, DynamicPropertyData*>> dynamicPropertyDataMap;
            return dynamicPropertyDataMap;
        }
        static DynamicPropertyData* GetDynamicPropertyData(v8::Isolate* isolate, Class* class_, const std::string& name);
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

        void RegisterStaticMethods()
        {
            for(auto& [name, callback] : staticMethods) Template::StaticFunction(name, callback);
        }

    public:
        ClassTemplate(v8::Isolate* isolate, Class* _class, v8::Local<v8::FunctionTemplate> tpl) : Template(isolate, tpl), class_(_class) {}

        template<auto Func>
        void Method(const std::string& name)
        {
            Get()->PrototypeTemplate()->Set(js::JSValue(name), v8::FunctionTemplate::New(GetIsolate(), Wrapper::MethodHandler<Func>));
        }

#ifdef DEBUG_BINDINGS
        void DumpRegisteredKeys();
#endif

        void Method(const std::string& name, internal::FunctionCallback callback)
        {
#ifdef DEBUG_BINDINGS
            RegisterKey("Method", name);
#endif
            Get()->PrototypeTemplate()->Set(js::JSValue(name), WrapFunction(callback));
        }
#pragma endregion

        template<auto Getter>
        void Property(const std::string& name)
        {
#ifdef DEBUG_BINDINGS
            RegisterKey("Property", name);
#endif
            Get()->PrototypeTemplate()->SetAccessor(js::JSValue(name), Wrapper::PropertyGetterHandler<Getter>, nullptr, v8::Local<v8::Value>(), v8::DEFAULT, v8::ReadOnly);
        }

        template<auto Getter, auto Setter>
        void Property(const std::string& name)
        {
#ifdef DEBUG_BINDINGS
            RegisterKey("Property", name);
#endif
            Get()->PrototypeTemplate()->SetAccessor(js::JSValue(name), Wrapper::PropertyGetterHandler<Getter>, Wrapper::PropertySetterHandler<Setter>);
        }

        // If getter is nullptr, tries to get the getter defined by a base class
        void Property(const std::string& name, internal::PropertyCallback getter = nullptr, internal::PropertyCallback setter = nullptr)
        {
#ifdef DEBUG_BINDINGS
            RegisterKey("Property", name);
#endif
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
                    if(getterTemplate.IsEmpty())
                    {
                        Logger::Error("Trying to register property setter for property", name, "without a previously registered getter");
                        return;
                    }
                }
                else
                    getterTemplate = WrapProperty(getter);
                Get()->PrototypeTemplate()->SetAccessorProperty(js::JSValue(name), getterTemplate, WrapProperty(setter), setter ? v8::None : v8::ReadOnly);
            }
        }

        template<auto Getter>
        void LazyProperty(const std::string& name)
        {
#ifdef DEBUG_BINDINGS
            RegisterKey("LazyProperty", name);
#endif
            Get()->InstanceTemplate()->SetLazyDataProperty(js::JSValue(name), Wrapper::LazyPropertyHandler<Getter>, v8::Local<v8::Value>(), v8::PropertyAttribute::ReadOnly);
        }
        void LazyProperty(const std::string& name, internal::LazyPropertyCallback callback)
        {
#ifdef DEBUG_BINDINGS
            RegisterKey("LazyProperty", name);
#endif
            Get()->InstanceTemplate()->SetLazyDataProperty(
              js::JSValue(name), Wrapper::LazyPropertyHandler, v8::External::New(GetIsolate(), (void*)callback), v8::PropertyAttribute::ReadOnly);
        }

        // Property returns an object that will call the specified handlers
        void DynamicProperty(const std::string& name,
                             internal::DynamicPropertyGetter getter,
                             internal::DynamicPropertySetter setter = nullptr,
                             internal::DynamicPropertyDeleter deleter = nullptr,
                             internal::DynamicPropertyEnumerator enumerator = nullptr)
        {
#ifdef DEBUG_BINDINGS
            RegisterKey("DynamicProperty", name);
#endif
            DynamicPropertyData* data = GetDynamicPropertyData(GetIsolate(), class_, name);
            if(!data)
            {
                data = new DynamicPropertyData(getter, setter, deleter, enumerator);
                InsertDynamicPropertyData(GetIsolate(), class_, name, data);
            }
            else
            {
                if(getter) data->getter = getter;
                if(setter) data->setter = setter;
                if(deleter) data->deleter = deleter;
                if(enumerator) data->enumerator = enumerator;
            }
            Get()->InstanceTemplate()->SetLazyDataProperty(
              js::JSValue(name), Wrapper::DynamicPropertyLazyHandler, v8::External::New(GetIsolate(), data), (v8::PropertyAttribute)(v8::ReadOnly | v8::DontEnum));
        }

        void StaticFunction(const std::string& name, internal::FunctionCallback callback) override
        {
            staticMethods[name] = callback;
        }

        template<alt::IBaseObject::Type Type>
        void GetByID()
        {
            StaticFunction("getByID", Wrapper::GetByIDHandler<Type>);
        }

#ifdef ALT_CLIENT_API
        template<alt::IBaseObject::Type Type>
        void GetByRemoteID()
        {
            StaticFunction("getByRemoteID", Wrapper::GetByRemoteIDHandler<Type>);
        }
#endif

        // Allows instances of this class to be called as a function
        void CallHandler(internal::FunctionCallback cb)
        {
            Get()->PrototypeTemplate()->SetCallAsFunctionHandler(Wrapper::FunctionHandler, v8::External::New(GetIsolate(), (void*)cb));
        }

        void Inherit(ClassTemplate& parent);
        void BindToType(alt::IBaseObject::Type type);
    };
}  // namespace js
