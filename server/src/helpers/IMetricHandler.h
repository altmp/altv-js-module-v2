#pragma once

#include "cpp-sdk/ICore.h"

#include <set>
#include <unordered_map>

namespace js
{
    class IMetricHandler
    {
        std::set<alt::Metric*> metrics;

    protected:
        virtual std::unordered_map<std::string, std::string> GetMetricAttributes() = 0;

        void CleanupMetrics()
        {
            for(auto metric : metrics) UnregisterMetric(metric);
        }

    public:
        alt::Metric* RegisterMetric(const std::string& name, alt::Metric::Type type);
        void UnregisterMetric(alt::Metric* metric);
    };
}  // namespace js
