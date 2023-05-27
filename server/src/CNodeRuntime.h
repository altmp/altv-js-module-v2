#pragma once

#include "interfaces/IRuntime.h"
#include "CNodeResource.h"
#include "node.h"
#include "uv.h"

#include <vector>

class CNodeRuntime : public js::IRuntime<CNodeRuntime, CNodeResource>
{
    enum class Metric : uint8_t
    {
        HEAP_SIZE,
        HEAP_LIMIT,
        PHYSICAL_SIZE,
        PHYSICAL_LIMIT,
        GLOBAL_HANDLES_SIZE,
        GLOBAL_HANDLES_LIMIT,

        SIZE
    };

    static std::vector<std::string> GetNodeArgs();

    std::unique_ptr<node::MultiIsolatePlatform> platform;

    std::unordered_map<Metric, alt::Metric*> metrics;

    void RegisterMetrics();
    void UpdateMetrics();

public:
    bool Initialize() override;

    void OnTick() override;

    node::MultiIsolatePlatform* GetPlatform() const
    {
        return platform.get();
    }
};
