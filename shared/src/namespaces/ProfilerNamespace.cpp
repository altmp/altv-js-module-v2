#include "Namespace.h"
#include "interfaces/IAltResource.h"

#include <sstream>

static void HeapStatsGetter(js::PropertyContext& ctx)
{
    js::Object obj;
    v8::HeapStatistics heapStats;
    ctx.GetIsolate()->GetHeapStatistics(&heapStats);

    obj.Set("heapSizeLimit", heapStats.heap_size_limit());
    obj.Set("totalHeapSize", heapStats.total_heap_size());
    obj.Set("usedHeapSize", heapStats.used_heap_size());
    obj.Set("mallocedMemory", heapStats.malloced_memory());
    obj.Set("peakMallocedMemory", heapStats.peak_malloced_memory());
    obj.Set("nativeContexts", heapStats.number_of_native_contexts());
    obj.Set("detachedContexts", heapStats.number_of_detached_contexts());
    obj.Set("totalGlobalHandleSize", heapStats.total_global_handles_size());
    obj.Set("usedGlobalHandleSize", heapStats.used_global_handles_size());

    ctx.Return(obj);
}

static void TakeHeapSnapshot(js::FunctionContext& ctx)
{
    const v8::HeapSnapshot* snapshot = ctx.GetIsolate()->GetHeapProfiler()->TakeHeapSnapshot();
    js::Promise* promise = ctx.GetResource()->CreatePromise();
    js::StringOutputStream* stream = js::StringOutputStream::Create(ctx.GetResource(),
                                                                    [=](const std::string& resultStr)
                                                                    {
                                                                        promise->Resolve(resultStr);
                                                                        delete promise;
                                                                    });
    snapshot->Serialize(stream, v8::HeapSnapshot::SerializationFormat::kJSON);
    ctx.Return(promise);
}

class MeasureMemoryDelegate : public v8::MeasureMemoryDelegate
{
public:
    using Callback = std::function<void(size_t size, size_t externalBytes)>;

private:
    js::IResource* resource;
    Callback callback;

public:
    MeasureMemoryDelegate(js::IResource* _resource, Callback&& _callback) : resource(_resource), callback(_callback) {}

    bool ShouldMeasure(v8::Local<v8::Context> context) override
    {
        return js::IResource::GetFromContext(context) == resource;
    }

    void MeasurementComplete(const std::vector<std::pair<v8::Local<v8::Context>, size_t>>& context_sizes_in_bytes, size_t unattributed_size_in_bytes) override
    {
        size_t size = context_sizes_in_bytes[0].second;
        resource->PushNextTickCallback([=]() { this->callback(size, unattributed_size_in_bytes); });
    }
};

static void GetMemoryProfile(js::FunctionContext& ctx)
{
    js::IResource* resource = ctx.GetResource();
    js::Promise* promise = resource->CreatePromise();
    // clang-format off
    std::unique_ptr<MeasureMemoryDelegate> delegate = std::make_unique<MeasureMemoryDelegate>(
        resource,
        [promise](size_t size, size_t externalBytes)
        {
            js::Object obj;
            obj.Set("size", size);
            obj.Set("externalBytes", externalBytes);
            promise->Resolve(obj);
            delete promise;
        });
    // clang-format on
    ctx.GetIsolate()->MeasureMemory(std::move(delegate), v8::MeasureMemoryExecution::kDefault);

    ctx.Return(promise);
}

// clang-format off
extern js::Namespace profilerNamespace("Profiler", [](js::NamespaceTemplate& tpl) {
    tpl.StaticProperty("heapStats", HeapStatsGetter);

    tpl.StaticFunction("takeHeapSnapshot", TakeHeapSnapshot);
    tpl.StaticFunction("getMemoryProfile", GetMemoryProfile);
});
