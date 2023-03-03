#pragma once

#include "v8.h"
#include "cpp-sdk/SDK.h"

namespace js
{
    class IResource : public alt::IResource::Impl
    {
    protected:
        alt::IResource* resource;
        v8::Isolate* isolate;

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
    };
}  // namespace js
