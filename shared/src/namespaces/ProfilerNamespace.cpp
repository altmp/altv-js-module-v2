#include "Namespace.h"
#include "interfaces/IAltResource.h"

#include <sstream>

static void TakeHeapSnapshot(js::FunctionContext& ctx)
{
    const v8::HeapSnapshot* snapshot = ctx.GetIsolate()->GetHeapProfiler()->TakeHeapSnapshot();
    js::Promise* promise = new js::Promise;
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
    tpl.StaticFunction("takeHeapSnapshot", TakeHeapSnapshot);
});
