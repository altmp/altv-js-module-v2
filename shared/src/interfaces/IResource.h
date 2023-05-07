#pragma once

#include <array>
#include <type_traits>

#include "v8.h"
#include "cpp-sdk/SDK.h"

#include "Bindings.h"
#include "Class.h"
#include "Module.h"
#include "IScriptObjectHandler.h"
#include "Event.h"
#include "Logger.h"

namespace js
{
    class IResource : public alt::IResource::Impl, public IScriptObjectHandler
    {
    public:
        class Function : public alt::IMValueFunction::Impl
        {
            IResource* resource;
            Persistent<v8::Function> function;

        public:
            Function(v8::Local<v8::Context> context, v8::Local<v8::Function> _function) : resource(GetFromContext(context)), function(resource->GetIsolate(), _function) {}

            alt::MValue Call(alt::MValueArgs args) const override;

            static void ExternalFunctionCallback(const v8::FunctionCallbackInfo<v8::Value>& info);
        };

    protected:
        static constexpr int ContextInternalFieldIdx = 1;

        static void RequireBindingNamespaceWrapper(FunctionContext& ctx);

        alt::IResource* resource;
        v8::Isolate* isolate;
        Persistent<v8::Context> context;

        std::unordered_map<std::string, Persistent<v8::Value>> bindingExports;

        std::unordered_map<alt::IResource*, Persistent<v8::Object>> resourceObjects;

        void Initialize()
        {
            context.Get(isolate)->SetAlignedPointerInEmbedderData(ContextInternalFieldIdx, this);
        }

        void Reset()
        {
            Binding::CleanupForResource(this);
            Module::CleanupForResource(this);
            IScriptObjectHandler::Reset();

            resource = nullptr;
            isolate = nullptr;

            context.Reset();
            bindingExports.clear();
            resourceObjects.clear();
        }

        void InitializeBinding(Binding* binding);

    public:
        IResource(alt::IResource* _resource, v8::Isolate* _isolate) : resource(_resource), isolate(_isolate) {}
        virtual ~IResource() = default;

        alt::IResource* GetResource() const
        {
            return resource;
        }
        v8::Isolate* GetIsolate() const
        {
            return isolate;
        }
        v8::Local<v8::Context> GetContext() const
        {
            return context.Get(isolate);
        }

        void OnCreateBaseObject(alt::IBaseObject* object) override
        {
            // IScriptObjectHandler::GetOrCreateScriptObject(GetContext(), object);
        }

        void OnRemoveBaseObject(alt::IBaseObject* object) override
        {
            v8::Locker locker(isolate);
            v8::Isolate::Scope isolateScope(isolate);
            v8::HandleScope handleScope(isolate);
            v8::Context::Scope contextScope(GetContext());

            IScriptObjectHandler::DestroyScriptObject(object);
        }

        void OnEvent(const alt::CEvent* ev) override
        {
            v8::Locker locker(isolate);
            v8::Isolate::Scope isolateScope(isolate);
            v8::HandleScope handleScope(isolate);
            v8::Context::Scope contextScope(GetContext());

            if(ev->GetType() == alt::CEvent::Type::RESOURCE_STOP) DestroyResourceObject(static_cast<const alt::CResourceStopEvent*>(ev)->GetResource());

            Event::SendEvent(ev, this);
        }

        void OnTick() override
        {
            v8::Locker locker(isolate);
            v8::Isolate::Scope isolateScope(isolate);
            v8::HandleScope handleScope(isolate);
            v8::Context::Scope contextScope(GetContext());

            js::Function onTick = GetBindingExport<v8::Function>("timers:tick");
            if(onTick.IsValid()) onTick.Call();
        }
        virtual void RunEventLoop()
        {
            OnTick();
        }

        void InitializeBindings(Binding::Scope scope, Module& altModule);
        void SetBindingExport(const std::string& name, v8::Local<v8::Value> val)
        {
            bindingExports.insert({ name, Persistent<v8::Value>(isolate, val) });
        }
        bool HasBindingExport(const std::string& name)
        {
            return bindingExports.contains(name);
        }
        template<typename T = v8::Value>
        v8::Local<T> GetBindingExport(const std::string& name)
        {
            static_assert(std::is_base_of_v<v8::Value, T>, "T must inherit from v8::Value");
            if(!bindingExports.contains(name)) return v8::Local<T>();
            v8::Local<v8::Value> val = bindingExports.at(name).Get(isolate);
            return val.As<T>();
        }

        v8::Local<v8::Object> CreateResourceObject(alt::IResource* resource);
        void DestroyResourceObject(alt::IResource* resource)
        {
            if(!resourceObjects.contains(resource)) return;
            resourceObjects.at(resource).Get(isolate)->SetAlignedPointerInInternalField(1, nullptr);
            resourceObjects.erase(resource);
        }

        v8::Local<v8::Object> CreateVector3(alt::Vector3f vec)
        {
            v8::Local<v8::Function> vector3 = GetBindingExport<v8::Function>("classes:vector3");
            if(vector3.IsEmpty()) return v8::Local<v8::Object>();

            std::array<v8::Local<v8::Value>, 3> args = { js::JSValue(vec[0]), js::JSValue(vec[1]), js::JSValue(vec[2]) };
            return vector3->NewInstance(GetContext(), args.size(), args.data()).ToLocalChecked();
        }
        v8::Local<v8::Object> CreateVector2(alt::Vector2f vec)
        {
            v8::Local<v8::Function> vector2 = GetBindingExport<v8::Function>("classes:vector2");
            if(vector2.IsEmpty()) return v8::Local<v8::Object>();

            std::array<v8::Local<v8::Value>, 2> args = { js::JSValue(vec[0]), js::JSValue(vec[1]) };
            return vector2->NewInstance(GetContext(), args.size(), args.data()).ToLocalChecked();
        }
        v8::Local<v8::Object> CreateRGBA(alt::RGBA rgba)
        {
            v8::Local<v8::Function> rgbaClass = GetBindingExport<v8::Function>("classes:rgba");
            if(rgbaClass.IsEmpty()) return v8::Local<v8::Object>();

            std::array<v8::Local<v8::Value>, 4> args = { js::JSValue(rgba.r), js::JSValue(rgba.g), js::JSValue(rgba.b), js::JSValue(rgba.a) };
            return rgbaClass->NewInstance(GetContext(), args.size(), args.data()).ToLocalChecked();
        }
        v8::Local<v8::Object> CreateQuaternion(alt::Quaternion quaternion)
        {
            v8::Local<v8::Function> quaternionClass = GetBindingExport<v8::Function>("classes:quaternion");
            if(quaternionClass.IsEmpty()) return v8::Local<v8::Object>();

            std::array<v8::Local<v8::Value>, 4> args = { js::JSValue(quaternion.x), js::JSValue(quaternion.y), js::JSValue(quaternion.z), js::JSValue(quaternion.w) };
            return quaternionClass->NewInstance(GetContext(), args.size(), args.data()).ToLocalChecked();
        }
        bool IsVector3(v8::Local<v8::Value> val)
        {
            v8::Local<v8::Function> vector3 = GetBindingExport<v8::Function>("classes:vector3");
            if(vector3.IsEmpty()) return false;

            return val->IsObject() && val.As<v8::Object>()->InstanceOf(GetContext(), vector3).ToChecked();
        }
        bool IsVector2(v8::Local<v8::Value> val)
        {
            v8::Local<v8::Function> vector2 = GetBindingExport<v8::Function>("classes:vector2");
            if(vector2.IsEmpty()) return false;

            return val->IsObject() && val.As<v8::Object>()->InstanceOf(GetContext(), vector2).ToChecked();
        }
        bool IsRGBA(v8::Local<v8::Value> val)
        {
            v8::Local<v8::Function> rgbaClass = GetBindingExport<v8::Function>("classes:rgba");
            if(rgbaClass.IsEmpty()) return false;

            return val->IsObject() && val.As<v8::Object>()->InstanceOf(GetContext(), rgbaClass).ToChecked();
        }
        bool IsQuaternion(v8::Local<v8::Value> val)
        {
            v8::Local<v8::Function> quaternionClass = GetBindingExport<v8::Function>("classes:quaternion");
            if(quaternionClass.IsEmpty()) return false;

            return val->IsObject() && val.As<v8::Object>()->InstanceOf(GetContext(), quaternionClass).ToChecked();
        }
        bool IsBaseObject(v8::Local<v8::Value> val)
        {
            extern js::Class baseObjectClass;
            return val->IsObject() && val.As<v8::Object>()->InstanceOf(GetContext(), baseObjectClass.GetTemplate(isolate).Get()->GetFunction(GetContext()).ToLocalChecked()).ToChecked();
        }

        static IResource* GetFromContext(v8::Local<v8::Context> context)
        {
            return static_cast<IResource*>(context->GetAlignedPointerFromEmbedderData(ContextInternalFieldIdx));
        }
    };
}  // namespace js
