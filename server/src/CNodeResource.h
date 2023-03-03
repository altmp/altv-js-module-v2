#pragma once

#include "module/IResource.h"

class CNodeResource : public js::IResource
{
public:
    CNodeResource(alt::IResource* resource) : IResource(resource) {}
};
