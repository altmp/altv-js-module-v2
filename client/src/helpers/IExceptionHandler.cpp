#include "IExceptionHandler.h"
#include "interfaces/IResource.h"
#include "Logger.h"

void IExceptionHandler::OnPromiseRejectedWithoutHandler(v8::PromiseRejectMessage& message)
{
    js::IResource* resource = js::IResource::GetCurrent();
    v8::Isolate* isolate = resource->GetIsolate();
    promiseRejections.push_back(PromiseRejection{ js::Persistent<v8::Promise>(isolate, message.GetPromise()),
                                                  js::Persistent<v8::Value>(isolate, message.GetValue()),
                                                  js::SourceLocation::GetCurrent(resource),
                                                  js::StackTrace::GetCurrent(isolate, resource) });
}

void IExceptionHandler::OnPromiseHandlerAdded(v8::PromiseRejectMessage& message)
{
    v8::Isolate* isolate = v8::Isolate::GetCurrent();

    auto newEnd = std::remove_if(promiseRejections.begin(), promiseRejections.end(), [&](PromiseRejection& rejection) { return rejection.promise.Get(isolate) == message.GetPromise(); });
    promiseRejections.erase(newEnd, promiseRejections.end());
}

void IExceptionHandler::OnPromiseRejectAfterResolve(v8::PromiseRejectMessage& message)
{
    js::IResource* resource = js::IResource::GetCurrent();
    const std::string& resourceName = resource->GetName();
    v8::Isolate* isolate = resource->GetIsolate();
    std::string rejectionMsg = *v8::String::Utf8Value(isolate, message.GetValue()->ToString(resource->GetContext()).ToLocalChecked());

    js::Logger::Error("[JS] Promise rejected after already being resolved in resource '" + resourceName + "'");
    if(!rejectionMsg.empty()) js::Logger::Error("[JS]", rejectionMsg);
}

void IExceptionHandler::OnPromiseResolveAfterResolve(v8::PromiseRejectMessage& message)
{
    js::IResource* resource = js::IResource::GetCurrent();
    const std::string& resourceName = resource->GetName();
    v8::Isolate* isolate = resource->GetIsolate();
    std::string rejectionMsg = *v8::String::Utf8Value(isolate, message.GetValue()->ToString(resource->GetContext()).ToLocalChecked());

    js::Logger::Error("[JS] Promise resolved after already being resolved in resource '" + resourceName + "'");
    if(!rejectionMsg.empty()) js::Logger::Error("[JS]", rejectionMsg);
}

void IExceptionHandler::ProcessExceptions()
{
    js::IResource* resource = js::IResource::GetCurrent();
    const std::string& resourceName = resource->GetName();
    v8::Isolate* isolate = resource->GetIsolate();

    for(PromiseRejection& rejection : promiseRejections)
    {
        std::string rejectionMsg = *v8::String::Utf8Value(isolate, rejection.value.Get(isolate)->ToString(resource->GetContext()).ToLocalChecked());
        js::Logger::Error("[JS] Unhandled promise rejection in resource '" + resourceName + "' in file '" + rejection.location.file + "' at line " + std::to_string(rejection.location.line));
        if(!rejectionMsg.empty()) js::Logger::Error("[JS]", rejectionMsg);
        if(!rejection.stackTrace.IsEmpty()) js::Logger::Error("[JS]", rejection.stackTrace.ToString());
    }
    promiseRejections.clear();
}

void IExceptionHandler::Reset()
{
    promiseRejections.clear();
}

void IExceptionHandler::OnPromiseRejected(v8::PromiseRejectMessage& message)
{
    switch(message.GetEvent())
    {
        case v8::kPromiseRejectWithNoHandler: OnPromiseRejectedWithoutHandler(message); break;
        case v8::kPromiseHandlerAddedAfterReject: OnPromiseHandlerAdded(message); break;
        case v8::kPromiseRejectAfterResolved: OnPromiseRejectAfterResolve(message); break;
        case v8::kPromiseResolveAfterResolved: OnPromiseResolveAfterResolve(message); break;
        default: break;
    }
}
