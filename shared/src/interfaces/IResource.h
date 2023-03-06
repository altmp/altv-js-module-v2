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

        void RegisterBindingExport(const std::string& name, const std::string& bindingName, const std::string& exportName)
        {
            Binding& binding = Binding::Get(bindingName);
            if(!binding.IsValid())
            {
                alt::ICore::Instance().LogError("INTERNAL ERROR: Failed to get binding " + bindingName);
                return;
            }
            v8::Local<v8::Module> mod = binding.GetCompiledModule(this);
            v8::Local<v8::Object> moduleNamespace = mod->GetModuleNamespace().As<v8::Object>();
            v8::MaybeLocal<v8::Value> maybeExportedValue = moduleNamespace->Get(GetContext(), js::JSValue(exportName));

            v8::Local<v8::Value> exportedValue;
            if(!maybeExportedValue.ToLocal(&exportedValue) || exportedValue->IsUndefined())
            {
                alt::ICore::Instance().LogError("INTERNAL ERROR: Failed to get exported value " + exportName + " from binding " + bindingName);
                return;
            }
            bindingExports.insert({ name, Persistent<v8::Value>(isolate, exportedValue) });
        }

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

        void InitializeBindings(Binding::Scope scope, Module& altModule)
        {
            std::vector<Binding*> bindings = Binding::GetBindingsForScope(scope);
            v8::Local<v8::Context> ctx = GetContext();

            ctx->Global()->Set(ctx, js::JSValue("alt"), altModule.GetNamespace(this));
            for(auto binding : bindings)
            {
                if(binding->GetName().ends_with("bootstrap.js")) continue;  // Skip bootstrap bindings, those are handled separately

                v8::Local<v8::Module> module = binding->GetCompiledModule(this);
                if(module.IsEmpty())
                {
                    alt::ICore::Instance().LogError("INTERNAL ERROR: Failed to compile binding module " + binding->GetName());
                    continue;
                }
                module->Evaluate(ctx);
                if(module->GetStatus() != v8::Module::Status::kEvaluated)
                {
                    alt::ICore::Instance().LogError("INTERNAL ERROR: Failed to evaluate binding module " + binding->GetName());
                    v8::Local<v8::Value> exception = module->GetException();
                    if(!exception.IsEmpty())
                    {
                        alt::ICore::Instance().LogError("INTERNAL ERROR: " + std::string(*v8::String::Utf8Value(isolate, exception)));
                    }
                    continue;
                }
            }
            ctx->Global()->Set(ctx, js::JSValue("alt"), v8::Undefined(isolate));
        }

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
