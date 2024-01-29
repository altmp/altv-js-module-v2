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
            if(context.IsEmpty()) return;
            IResource::Scope scope(this);

            IScriptObjectHandler::GetOrCreateScriptObject(GetContext(), object);
        }

#if ALT_CLIENT_API
        // NOTE(xLuxy): This is a workaround for alt:V not calling BaseObject for RmlElements
        static void RemoveRmlChildrens(alt::IRmlElement* element, IResource* resource)
        {
            for (size_t i = 0; i < element->GetChildCount(); i++)
            {
                const auto children = element->GetChild(i);

                RemoveRmlChildrens(children, resource);
                resource->DestroyScriptObject(children);

                alt::ICore::Instance().DestroyBaseObject(children);
            }
        }
#endif

        void OnRemoveBaseObject(alt::IBaseObject* object) override
        {
            if(context.IsEmpty()) return;
            IResource::Scope scope(this);

#if ALT_CLIENT_API
            // TODO(xLuxy): alt:V currently doesn't create BaseObject for RmlElements
            if (object->GetType() == alt::IBaseObject::Type::RML_DOCUMENT)
            {
                RemoveRmlChildrens(dynamic_cast<alt::IRmlElement*>(object), GetCurrentResource());
            }
#endif

            IScriptObjectHandler::DestroyScriptObject(object);
        }

        void OnEvent(const alt::CEvent* ev) override
        {
            if(context.IsEmpty()) return;
            IResource::Scope scope(this);

            if (ev->GetType() == alt::CEvent::Type::RESOURCE_STOP) DestroyResourceObject(static_cast<const alt::CResourceStopEvent*>(ev)->GetResource());

            Event::SendEvent(ev, this);
        }

        void OnTick() override
        {
            IResource::ProcessNextTickCallbacks();
            js::Function onTick = GetBindingExport<v8::Function>(BindingExport::TICK);
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
