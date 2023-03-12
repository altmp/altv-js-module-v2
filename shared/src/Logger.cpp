#include "Logger.h"
#include "interfaces/IResource.h"

js::Logger& js::Logger::operator<<(const js::Logger::EndlStruct&)
{
    alt::IResource* altResource = nullptr;
    v8::Isolate* isolate = v8::Isolate::GetCurrent();
    if(isolate != nullptr)
    {
        v8::HandleScope scope(isolate);
        v8::Local<v8::Context> context = isolate->GetEnteredOrMicrotaskContext();
        if(!context.IsEmpty())
        {
            js::IResource* resource = js::IResource::GetFromContext(context);
            if(resource) altResource = resource->GetResource();
        }
    }

    if(type == Type::INFO) alt::ICore::Instance().LogInfo(stream.str(), altResource);
    else if(type == Type::COLORED)
        alt::ICore::Instance().LogColored(stream.str(), altResource);
    else if(type == Type::WARN)
        alt::ICore::Instance().LogWarning(stream.str(), altResource);
    else if(type == Type::ERR)
        alt::ICore::Instance().LogError(stream.str(), altResource);
    stream.str("");
    return *this;
}
