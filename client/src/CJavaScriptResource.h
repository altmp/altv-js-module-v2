#pragma once

#include "interfaces/IAltResource.h"
#include "helpers/JS.h"
#include "helpers/IModuleHandler.h"
#include "helpers/IExceptionHandler.h"

#include "v8.h"

class CJavaScriptResource : public js::IAltResource, public IModuleHandler, public IExceptionHandler
{
    std::unique_ptr<v8::MicrotaskQueue> microtaskQueue;
    bool started = false;
    std::shared_ptr<alt::INative::Context> nativeContext;

    static void StartResource(js::FunctionContext& ctx);

    v8::Local<v8::Module> CompileAndRun(const std::string& path, const std::string& source);

public:
    CJavaScriptResource(alt::IResource* resource, v8::Isolate* isolate) : IAltResource(resource, isolate) {}

    bool Start() override;
    bool Stop() override;

    void OnTick() override;

    void RunEventLoop() override;

    std::shared_ptr<alt::INative::Context> GetNativeContext()
    {
        return nativeContext;
    }
};
