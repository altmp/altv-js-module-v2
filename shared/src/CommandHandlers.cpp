#include "CommandHandlers.h"
#include "interfaces/IResource.h"
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
        js::IResource* resource = static_cast<js::IResource*>(altResource->GetImpl());

        v8::Isolate* isolate = resource->GetIsolate();
        v8::Locker locker(isolate);
        v8::HandleScope scope(isolate);
        v8::Isolate::Scope isolateScope(isolate);

        HandleVisitor visitor(resource);
        resource->GetIsolate()->VisitHandlesWithClassIds(&visitor);
        visitor.Dump();
    }
}
