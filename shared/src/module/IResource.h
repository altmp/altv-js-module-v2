#pragma once

#include "v8.h"
#include "cpp-sdk/SDK.h"

#include "Bindings.h"

namespace js
{
    class IResource : public alt::IResource::Impl
    {
    protected:
        static constexpr int ContextInternalFieldIdx = 1;

        alt::IResource* resource;
        v8::Isolate* isolate;
        v8::Global<v8::Context> context;

        void Reset()
        {
            Binding::CleanupForResource(this);
            context.Reset();
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

        static IResource* GetFromContext(v8::Local<v8::Context> context)
        {
            return static_cast<IResource*>(context->GetAlignedPointerFromEmbedderData(ContextInternalFieldIdx));
        }
    };
}  // namespace js
