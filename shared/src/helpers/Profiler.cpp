#include "Profiler.h"
#include "Logger.h"

#include <sstream>

void Profiler::DumpAllSamples()
{
    auto& samples = Samples();
    for(auto& sample : samples)
    {
        Profiler::SampleResult result = GetSampleResult(sample);
        js::Logger::Warn(result.ToString());
    }
}

void Profiler::DumpSample(const std::string& name)
{
    auto& samples = Samples();
    if(!samples.contains(name))
    {
        js::Logger::Warn("Sample", name, "was not found");
        return;
    }
    auto sample = samples.find(name);
    Profiler::SampleResult result = GetSampleResult(*sample);
    js::Logger::Warn(result.ToString());
}

void Profiler::ResetSamples()
{
    Samples().clear();
    LongestNameLength() = 0;
}

std::string Profiler::SampleResult::ToString()
{
    std::stringstream stream;
    stream << std::left << std::setw(Profiler::LongestNameLength() + 1) << name;
    stream << "| Total: " << total << "ns (" << (float)(total / 1000000) << "ms) ";
    stream << "| Average: " << average << "ns (" << (float)(average / 1000000) << "ms) ";
    stream << "| Min: " << min << "ns (" << (float)(min / 1000000) << "ms) ";
    stream << "| Max: " << max << "ns (" << (float)(max / 1000000) << "ms) ";
    stream << "| Samples: " << samplesCount;
    return stream.str();
}

Profiler::SampleResult Profiler::GetSampleResult(std::pair<const std::string, Durations>& sample)
{
    uint64_t total = 0;
    uint64_t max = std::numeric_limits<uint64_t>::min();
    uint64_t min = std::numeric_limits<uint64_t>::max();
    uint64_t avg = 0;

    for(auto& duration : sample.second)
    {
        if(duration > max) max = duration;
        if(duration < min) min = duration;
        total += duration;
    }
    avg = total / sample.second.size();

    return SampleResult{ sample.first, sample.second.size(), total, max, min, avg };
}
