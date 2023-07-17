#pragma once

#include "IResource.h"

#include <queue>

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

        using NextTickCallback = std::function<void()>;

    protected:
        alt::IResource* resource = nullptr;

        std::unordered_map<alt::IResource*, Persistent<v8::Object>> resourceObjects;

        std::queue<NextTickCallback> nextTickCallbacks;

        void Reset() override
        {
            IResource::Reset();
            resource = nullptr;
            resourceObjects.clear();
            nextTickCallbacks = {};
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
            if(context.IsEmpty()) return;
            IResource::Scope scope(this);

            IScriptObjectHandler::DestroyScriptObject(object);
        }

        void OnEvent(const alt::CEvent* ev) override
        {
            if(context.IsEmpty()) return;
            IResource::Scope scope(this);

            if(ev->GetType() == alt::CEvent::Type::RESOURCE_STOP) DestroyResourceObject(static_cast<const alt::CResourceStopEvent*>(ev)->GetResource());

            Event::SendEvent(ev, this);
        }

        void OnTick() override
        {
            while(!nextTickCallbacks.empty())
            {
                NextTickCallback& callback = nextTickCallbacks.front();
                callback();
                nextTickCallbacks.pop();
            }

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

        void PushNextTickCallback(NextTickCallback&& callback)
        {
            nextTickCallbacks.push(std::move(callback));
        }
    };
}  // namespace js
