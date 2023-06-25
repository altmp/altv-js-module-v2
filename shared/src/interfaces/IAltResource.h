#pragma once

#include "IResource.h"

namespace js
{
    class IAltResource : public alt::IResource::Impl, public IResource
    {
    public:
        class Function : public alt::IMValueFunction::Impl
        {
            IAltResource* resource;
            Persistent<v8::Function> function;

        public:
            Function(v8::Local<v8::Context> context, v8::Local<v8::Function> _function) : resource(GetFromContext<IAltResource>(context)), function(resource->GetIsolate(), _function) {}

            alt::MValue Call(alt::MValueArgs args) const override;

            static void ExternalFunctionCallback(const v8::FunctionCallbackInfo<v8::Value>& info);
        };

    protected:
        alt::IResource* resource = nullptr;

        std::unordered_map<alt::IResource*, Persistent<v8::Object>> resourceObjects;

        void Reset() override
        {
            IResource::Reset();
            resource = nullptr;
            resourceObjects.clear();
        }

    public:
        IAltResource(alt::IResource* _resource, v8::Isolate* _isolate) : IResource(_isolate), resource(_resource) {}

        void RunEventLoop() override
        {
            OnTick();
        }
        const std::string& GetName() const override
        {
            return resource->GetName();
        }
        const std::string& GetPath() const override
        {
            return resource->GetPath();
        }
        alt::IResource* GetResource() const override
        {
            return resource;
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
            js::Function onTick = GetBindingExport<v8::Function>("timers:tick");
            if(onTick.IsValid()) onTick.Call();
        }

        v8::Local<v8::Object> CreateResourceObject(alt::IResource* resource);
        void DestroyResourceObject(alt::IResource* resource)
        {
            if(!resourceObjects.contains(resource)) return;
            resourceObjects.at(resource).Get(isolate)->SetAlignedPointerInInternalField(1, nullptr);
            resourceObjects.erase(resource);
        }
    };
}  // namespace js
