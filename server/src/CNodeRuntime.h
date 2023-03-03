#pragma once

#include "module/IRuntime.h"
#include "CNodeResource.h"
#include "node.h"
#include "uv.h"

#include <vector>

class CNodeRuntime : public js::IRuntime<CNodeRuntime, CNodeResource>
{
    static std::vector<std::string> GetNodeArgs();

    std::unique_ptr<node::MultiIsolatePlatform> platform;

public:
    bool Initialize() override;

    void OnTick() override;

    node::MultiIsolatePlatform* GetPlatform() const
    {
        return platform.get();
    }
};
