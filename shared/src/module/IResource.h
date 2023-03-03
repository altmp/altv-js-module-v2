#pragma once

#include "v8.h"
#include "SDK.h"

namespace js
{
    class IResource : public alt::IResource::Impl
    {
    protected:
        alt::IResource* resource;

    public:
        IResource(alt::IResource* resource) : resource(resource) {}
        virtual ~IResource() = default;

        alt::IResource* GetResource() const
        {
            return resource;
        }
    };
}  // namespace js
