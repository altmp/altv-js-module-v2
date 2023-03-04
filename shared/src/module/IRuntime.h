#pragma once

#include "v8.h"
#include "cpp-sdk/SDK.h"

#include "Module.h"

namespace js
{
    template<class Runtime, class Resource>
    class IRuntime : public alt::IScriptRuntime
    {
    protected:
        v8::Isolate* isolate = nullptr;

    public:
        using ResourceType = Resource;

        IRuntime() = default;
        IRuntime(const IRuntime&) = delete;
        virtual ~IRuntime() = default;

        virtual bool Initialize()
        {
            Module::Initialize(isolate);
            return true;
        }

        alt::IResource::Impl* CreateImpl(alt::IResource* resource) override
        {
            return new Resource{ resource, isolate };
        }
        void DestroyImpl(alt::IResource::Impl* impl) override
        {
            Resource* res = static_cast<Resource*>(impl);
            delete res;
        }

        v8::Isolate* GetIsolate() const
        {
            return isolate;
        }

        static Runtime& Instance()
        {
            static Runtime instance;
            return instance;
        }
    };
}  // namespace js
