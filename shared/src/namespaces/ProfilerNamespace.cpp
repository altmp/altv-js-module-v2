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
    ctx.Return(promise->Get());
}

// clang-format off
extern js::Namespace profilerNamespace("Profiler", [](js::NamespaceTemplate& tpl) {
    tpl.StaticProperty("heapStats", HeapStatsGetter);

    tpl.StaticFunction("takeHeapSnapshot", TakeHeapSnapshot);
});
