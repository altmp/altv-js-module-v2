#include "CommandHandlers.h"
#include "interfaces/IAltResource.h"
#include "Class.h"
#include "Logger.h"
#include "helpers/Profiler.h"
#include "cpp-sdk/ICore.h"

#include <filesystem>
#include <chrono>
#include <fstream>

class HandleVisitor : public v8::PersistentHandleVisitor
{
    js::IResource* resource;
    std::unordered_map<js::Class*, uint32_t> handles;

public:
    HandleVisitor(js::IResource* _resource) : resource(_resource) {}

    void VisitPersistentHandle(v8::Persistent<v8::Value>* value, uint16_t classId) override
    {
        v8::Local<v8::Value> val = value->Get(resource->GetIsolate());
        js::Class* class_ = js::Class::GetByClassId(classId);
        if(!class_) return;
        handles[class_]++;
    }

    void Dump()
    {
        js::Logger::Colored << "~g~" << resource->GetName() << ":" << js::Logger::Endl;
        if(handles.empty())
        {
            js::Logger::Colored("~y~No handles");
            return;
        }
        for(auto& [class_, count] : handles)
        {
            js::Logger::Colored << "~y~" << class_->GetName() << ": ~w~" << count << " handles" << js::Logger::Endl;
        }
    }
};

void js::DebugHandlesCommand(js::CommandArgs&)
{
    auto resources = alt::ICore::Instance().GetAllResources();
    for(alt::IResource* altResource : resources)
    {
        if(altResource->GetType() != "jsv2") continue;
        js::IAltResource* resource = static_cast<js::IAltResource*>(altResource->GetImpl());

        v8::Isolate* isolate = resource->GetIsolate();
        v8::Locker locker(isolate);
        v8::HandleScope scope(isolate);
        v8::Isolate::Scope isolateScope(isolate);

        HandleVisitor visitor(resource);
        resource->GetIsolate()->VisitHandlesWithClassIds(&visitor);
        visitor.Dump();
    }
}

void js::DumpBindingCommand(js::CommandArgs& args)
{
    if(!args.size())
    {
        Logger::Warn("Usage: dumpbinding <binding name>");
        return;
    }
    js::Binding& binding = js::Binding::Get(args[0]);
    if(!binding.IsValid())
    {
        Logger::Warn("Binding", args[0], "not found");
        return;
    }
    binding.Dump();
}

void js::DumpAllBindingsCommand(js::CommandArgs&)
{
    Binding::DumpAll();
}

void js::DumpSampleCommand(js::CommandArgs& args)
{
    if(!args.size())
    {
        Logger::Warn("Usage: dumpsample <sample name>");
        return;
    }
    Profiler::DumpSample(args[0]);
}

void js::DumpAllSamplesCommand(js::CommandArgs&)
{
    Profiler::DumpAllSamples();
}

void js::ResetSamplesCommand(js::CommandArgs&)
{
    Profiler::ResetSamples();
}

void js::DumpBuffersCommand(js::CommandArgs&)
{
    auto resources = alt::ICore::Instance().GetAllResources();
    for(alt::IResource* altResource : resources)
    {
        if(altResource->GetType() != "jsv2") continue;
        js::IAltResource* resource = static_cast<js::IAltResource*>(altResource->GetImpl());

        v8::Isolate* isolate = resource->GetIsolate();
        v8::Locker locker(isolate);
        v8::HandleScope scope(isolate);
        v8::Isolate::Scope isolateScope(isolate);

        HandleVisitor visitor(resource);
        resource->GetIsolate()->VisitWeakHandles(&visitor);
        visitor.Dump();
    }
}

void js::DumpHeapCommand(js::CommandArgs&)
{
    auto resources = alt::ICore::Instance().GetAllResources();
    IAltResource* resource = nullptr;
    for (alt::IResource* altResource : resources)
    {
        if (altResource->GetType() != "jsv2") continue;
        resource = static_cast<js::IAltResource*>(altResource->GetImpl());
    }
    if (!resource) return;

    v8::Isolate* isolate = resource->GetIsolate();
    v8::Locker locker(isolate);
    v8::HandleScope scope(isolate);
    v8::Isolate::Scope isolateScope(isolate);

    const auto callback = [](const std::string& heapJson)
    {
        std::filesystem::path mainDir;
#ifdef ALT_SERVER_API
        mainDir = alt::ICore::Instance().GetRootDirectory();
#else
        mainDir = alt::ICore::Instance().GetClientPath();
#endif
        if (!std::filesystem::exists(mainDir / "heapdumps")) std::filesystem::create_directory(mainDir / "heapdumps");

        const auto now = std::chrono::system_clock::now();
        time_t time = std::chrono::system_clock::to_time_t(now);

        // todo: This is UNIX time for some reason, fix it to display local time
        char timestamp[20];
        std::strftime(timestamp, sizeof(timestamp), "%d-%m-%Y_%H-%M-%S", std::localtime(&time));
        std::string fileName = std::string(timestamp) + '_' + std::to_string(now.time_since_epoch().count()) + ".heapsnapshot";

        std::ofstream file(mainDir / "heapdumps" / fileName);
        file.write(heapJson.data(), heapJson.size());
        file.close();
        Logger::Info("Wrote heapdump result into heapdumps/" + fileName);
    };

    StringOutputStream* stream = StringOutputStream::Create(resource, callback);
    const v8::HeapSnapshot* snapshot = isolate->GetHeapProfiler()->TakeHeapSnapshot();
    snapshot->Serialize(stream, v8::HeapSnapshot::kJSON);
}
