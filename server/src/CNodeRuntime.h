#pragma once

#include "IRuntime.h"
#include "CNodeResource.h"

namespace js
{
    class CNodeRuntime : public IRuntime<CNodeRuntime, CNodeResource>
    {
    public:
        bool Initialize() override
        {
            return true;
        }
    };
}  // namespace js
