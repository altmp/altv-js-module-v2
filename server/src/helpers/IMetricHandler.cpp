#include "IMetricHandler.h"

alt::Metric* js::IMetricHandler::RegisterMetric(const std::string& name, alt::Metric::Type type)
{
    alt::Metric* metric = alt::ICore::Instance().RegisterMetric(name, type, GetMetricAttributes());
    metrics.insert(metric);
    return metric;
}

void js::IMetricHandler::UnregisterMetric(alt::Metric* metric)
{
    metrics.erase(metric);
    alt::ICore::Instance().UnregisterMetric(metric);
}
