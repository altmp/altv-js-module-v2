#include "Namespace.h"
#include "interfaces/IAltResource.h"
#include "v8-profiler.h"

#include <sstream>

class StringOutputStream : public v8::OutputStream
{
    std::stringstream stream;
    std::function<void(const std::string&)> callback;
    js::IAltResource* resource;

public:
    StringOutputStream(js::IAltResource* _resource, std::function<void(const std::string&)>&& _callback) : resource(_resource), callback(_callback) {}

    virtual void EndOfStream() override
    {
        resource->PushNextTickCallback([this]() { this->callback(this->stream.str()); });
    }
    virtual WriteResult WriteAsciiChunk(char* data, int size) override
    {
        stream << data;
        return WriteResult::kContinue;
    }
};

static void TakeHeapSnapshot(js::FunctionContext& ctx)
{
    const v8::HeapSnapshot* snapshot = ctx.GetIsolate()->GetHeapProfiler()->TakeHeapSnapshot();
    js::Promise* promise = new js::Promise;
    StringOutputStream* stream = new StringOutputStream(ctx.GetResource<js::IAltResource>(),
                                                        [=](const std::string& resultStr)
                                                        {
                                                            promise->Resolve(resultStr);
                                                            delete promise;
                                                            delete stream;
                                                        });
    snapshot->Serialize(stream, v8::HeapSnapshot::SerializationFormat::kJSON);
    ctx.Return(promise->Get());
}

// clang-format off
extern js::Namespace profilerNamespace("Profiler", [](js::NamespaceTemplate& tpl) {
    tpl.StaticFunction("takeHeapSnapshot", TakeHeapSnapshot);
});
