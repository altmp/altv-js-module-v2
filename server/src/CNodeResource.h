#pragma once

#include "IResource.h"

namespace js
{
    class CNodeResource : public IResource
    {
    public:
        CNodeResource(alt::IResource* resource) : IResource(resource) {}
    };
}  // namespace js
