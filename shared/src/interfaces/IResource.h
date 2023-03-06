#pragma once

#include "v8.h"
#include "cpp-sdk/SDK.h"

#include "Bindings.h"
#include "Class.h"
#include "Module.h"
#include "IScriptObjectHandler.h"
#include "Event.h"

namespace js
{
    class IResource : public alt::IResource::Impl, public IScriptObjectHandler
    {
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
            // IScriptObjectHandler::CreateScriptObject(GetContext(), object);
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
        }
        v8::Local<v8::Value> GetBindingExport(const std::string& name)
        {
            if(!bindingExports.contains(name)) return v8::Local<v8::Value>();
            return bindingExports.at(name).Get(isolate);
        }

        static IResource* GetFromContext(v8::Local<v8::Context> context)
        {
            return static_cast<IResource*>(context->GetAlignedPointerFromEmbedderData(ContextInternalFieldIdx));
        }
    };
}  // namespace js
