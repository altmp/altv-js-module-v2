#pragma once

#include <unordered_map>
#include <chrono>
#include <vector>

class Profiler
{
public:
    using Durations = std::vector<std::chrono::high_resolution_clock::rep>;

    class Sample
    {
        std::string name;
        std::chrono::high_resolution_clock::time_point start;
        bool active = true;

    public:
        Sample(const std::string& _name) : name(_name), start(std::chrono::high_resolution_clock::now()) {}
        ~Sample()
        {
            End();
        }

        void End()
        {
            if(!active) return;
            active = false;
            std::chrono::high_resolution_clock::duration duration = std::chrono::high_resolution_clock::now() - start;
            Profiler::Samples()[name].push_back(duration.count());
            if(name.length() > LongestNameLength()) LongestNameLength() = name.length();
        }
    };

    static void DumpAllSamples();
    static void DumpSample(const std::string& name);
    static void ResetSamples();

private:
    struct SampleResult
    {
        std::string name;
        uint64_t samplesCount;
        uint64_t total;
        uint64_t max;
        uint64_t min;
        uint64_t average;

        std::string ToString();
    };
    static SampleResult GetSampleResult(std::pair<const std::string, Durations>& sample);

    // Map of all collected samples
    // Key = Name of sample
    // Value = Vector of all sample durations in nanoseconds
    static std::unordered_map<std::string, Durations>& Samples()
    {
        static std::unordered_map<std::string, Durations> samples{};
        return samples;
    }
    static uint32_t& LongestNameLength()
    {
        static uint32_t len{};
        return len;
    }
};
