#pragma once

#include "v8.h"
#include "cpp-sdk/SDK.h"

#include "Bindings.h"
#include "Class.h"
#include "Module.h"
#include "IScriptObjectHandler.h"

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
        v8::Local<v8::Value> GetBindingExport(const std::string& name)
        {
            if(!bindingExports.contains(name)) return v8::Local<v8::Value>();
            return bindingExports.at(name).Get(isolate);
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

        void OnTick() override
        {
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
        }

        static IResource* GetFromContext(v8::Local<v8::Context> context)
        {
            return static_cast<IResource*>(context->GetAlignedPointerFromEmbedderData(ContextInternalFieldIdx));
        }
    };
}  // namespace js
