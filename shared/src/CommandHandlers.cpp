#include "CommandHandlers.h"
#include "interfaces/IAltResource.h"
#include "Class.h"
#include "Logger.h"
#include "cpp-sdk/ICore.h"

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

void js::DebugHandlesCommand(const std::vector<std::string>&)
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

void js::DumpBindingCommand(const std::vector<std::string>& args)
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

void js::DumpAllBindingsCommand(const std::vector<std::string>&)
{
    Binding::DumpAll();
}

void js::ShowBuffersCommand(const std::vector<std::string>& args)
{
    if(!args.size())
    {
        Logger::Warn("Usage: showbuffers <resource name>");
        return;
    }

    alt::IResource* resource = alt::ICore::Instance().GetResource(args[0]);
    if(!resource)
    {
        Logger::Warn("Resource", args[0], "not found");
        return;
    }
    if(resource->GetType() != "jsv2")
    {
        Logger::Warn("Resource", args[0], "is not a JS v2 resource");
        return;
    }

    IResource* jsResource = dynamic_cast<IResource*>(resource->GetImpl());
    auto& ownedBuffers = jsResource->GetOwnedBuffers();
    if(ownedBuffers.empty()) Logger::Colored("~y~No owned buffers");
    else
    {
        Logger::Warn("Resource", resource->GetName(), "has", ownedBuffers.size(), "buffer instances, buffer locations:");
        for(auto& [buffer, location] : ownedBuffers)
        {
            Logger::Warn("Buffer with size", buffer->GetSize(), "|", location.file + ":" + std::to_string(location.line));
            delete buffer;
        }
    }
}
