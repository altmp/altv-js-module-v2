#pragma once

#include "IRuntime.h"
#include "CNodeResource.h"

class CNodeRuntime : public js::IRuntime<CNodeRuntime, CNodeResource>
{
public:
    bool Initialize() override
    {
        return true;
    }
};
