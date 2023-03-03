#pragma once

#include "module/IRuntime.h"
#include "CNodeResource.h"

class CNodeRuntime : public js::IRuntime<CNodeRuntime, CNodeResource>
{
public:
    bool Initialize() override
    {
        return true;
    }
};
