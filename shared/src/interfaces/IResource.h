#pragma once

#include <array>

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

        static void GetBindingNamespaceWrapper(FunctionContext& ctx);

        alt::IResource* resource;
        v8::Isolate* isolate;
        Persistent<v8::Context> context;

        std::unordered_map<std::string, Persistent<v8::Value>> bindingExports;

        void Initialize()
        {
            context.Get(isolate)->SetAlignedPointerInEmbedderData(ContextInternalFieldIdx, this);
        }

        void Reset()
        {
            Binding::CleanupForResource(this);
            context.Reset();
        }

        void InitializeBinding(Binding* binding);
        void RegisterBindingExport(const std::string& name, const std::string& bindingName, const std::string& exportName);

        void InitializeEvents()
        {
            Event::RegisterEvents(this);
        }

        void Started()
        {
            js::Event::EventArgs args{ { "resourceName", js::JSValue(resource->GetName()) } };
            js::Event::SendEvent(js::EventType::RESOURCE_START, args, this);
        }
        void Stopped()
        {
            js::Event::EventArgs args{ { "resourceName", js::JSValue(resource->GetName()) } };
            js::Event::SendEvent(js::EventType::RESOURCE_STOP, args, this);
        }

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
            IScriptObjectHandler::DestroyScriptObject(object);
        }

        void OnEvent(const alt::CEvent* ev) override
        {
            v8::Locker locker(isolate);
            v8::Isolate::Scope isolateScope(isolate);
            v8::HandleScope handleScope(isolate);
            v8::Context::Scope contextScope(GetContext());

            Event::SendEvent(ev, this);
        }

        void OnTick() override
        {
            v8::Locker locker(isolate);
            v8::Isolate::Scope isolateScope(isolate);
            v8::HandleScope handleScope(isolate);
            v8::Context::Scope contextScope(GetContext());

            v8::Local<v8::Value> onTick = GetBindingExport("timers:tick");
            if(!onTick.IsEmpty())
            {
                v8::Local<v8::Function> onTickFunc = onTick.As<v8::Function>();
                onTickFunc->Call(GetContext(), v8::Undefined(isolate), 0, nullptr);
            }
        }

        void InitializeBindings(Binding::Scope scope, Module& altModule);
        virtual void RegisterBindingExports()
        {
            // Register the needed exports of our bindings
            RegisterBindingExport("timers:tick", "shared/timers.js", "tick");
            RegisterBindingExport("events:setEvents", "shared/events.js", "setEvents");
            RegisterBindingExport("events:onEvent", "shared/events.js", "onEvent");

            RegisterBindingExport("classes:vector3", "shared/classes/vector.js", "Vector3");
            RegisterBindingExport("classes:vector2", "shared/classes/vector.js", "Vector2");
            RegisterBindingExport("classes:rgba", "shared/classes/rgba.js", "RGBA");

            RegisterBindingExport("logging:inspectMultiple", "shared/logging.js", "inspectMultiple");
        }
        v8::Local<v8::Value> GetBindingExport(const std::string& name)
        {
            if(!bindingExports.contains(name)) return v8::Local<v8::Value>();
            return bindingExports.at(name).Get(isolate);
        }

        v8::Local<v8::Object> CreateVector3(alt::Vector3f vec)
        {
            v8::Local<v8::Value> vector3 = GetBindingExport("classes:vector3");
            if(vector3.IsEmpty()) return v8::Local<v8::Object>();

            v8::Local<v8::Function> vector3Func = vector3.As<v8::Function>();
            std::array<v8::Local<v8::Value>, 3> args = { js::JSValue(vec[0]), js::JSValue(vec[1]), js::JSValue(vec[2]) };
            return vector3Func->NewInstance(GetContext(), args.size(), args.data()).ToLocalChecked();
        }
        v8::Local<v8::Object> CreateVector2(alt::Vector2f vec)
        {
            v8::Local<v8::Value> vector2 = GetBindingExport("classes:vector2");
            if(vector2.IsEmpty()) return v8::Local<v8::Object>();

            v8::Local<v8::Function> vector2Func = vector2.As<v8::Function>();
            std::array<v8::Local<v8::Value>, 2> args = { js::JSValue(vec[0]), js::JSValue(vec[1]) };
            return vector2Func->NewInstance(GetContext(), args.size(), args.data()).ToLocalChecked();
        }
        v8::Local<v8::Object> CreateRGBA(alt::RGBA rgba)
        {
            v8::Local<v8::Value> rgbaClass = GetBindingExport("classes:rgba");
            if(rgbaClass.IsEmpty()) return v8::Local<v8::Object>();

            v8::Local<v8::Function> rgbaFunc = rgbaClass.As<v8::Function>();
            std::array<v8::Local<v8::Value>, 4> args = { js::JSValue(rgba.r), js::JSValue(rgba.g), js::JSValue(rgba.b), js::JSValue(rgba.a) };
            return rgbaFunc->NewInstance(GetContext(), args.size(), args.data()).ToLocalChecked();
        }
        bool IsVector3(v8::Local<v8::Value> val)
        {
            v8::Local<v8::Value> vector3 = GetBindingExport("classes:vector3");
            if(vector3.IsEmpty()) return false;

            v8::Local<v8::Function> vector3Func = vector3.As<v8::Function>();
            return val->IsObject() && val.As<v8::Object>()->InstanceOf(GetContext(), vector3Func).ToChecked();
        }
        bool IsVector2(v8::Local<v8::Value> val)
        {
            v8::Local<v8::Value> vector2 = GetBindingExport("classes:vector2");
            if(vector2.IsEmpty()) return false;

            v8::Local<v8::Function> vector2Func = vector2.As<v8::Function>();
            return val->IsObject() && val.As<v8::Object>()->InstanceOf(GetContext(), vector2Func).ToChecked();
        }
        bool IsRGBA(v8::Local<v8::Value> val)
        {
            v8::Local<v8::Value> rgbaClass = GetBindingExport("classes:rgba");
            if(rgbaClass.IsEmpty()) return false;

            v8::Local<v8::Function> rgbaFunc = rgbaClass.As<v8::Function>();
            return val->IsObject() && val.As<v8::Object>()->InstanceOf(GetContext(), rgbaFunc).ToChecked();
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
