#pragma once

#include "interfaces/IResource.h"
#include "helpers/JS.h"
#include "helpers/IModuleHandler.h"

#include "v8.h"

class CJavaScriptResource : public js::IResource, public IModuleHandler
{
    std::unique_ptr<v8::MicrotaskQueue> microtaskQueue;
    bool started = false;

    static void StartResource(js::FunctionContext& ctx);

    v8::Local<v8::Module> CompileAndRun(const std::string& path, const std::string& source);

public:
    CJavaScriptResource(alt::IResource* resource, v8::Isolate* isolate) : IResource(resource, isolate) {}

    bool Start() override;
    bool Stop() override;

    void OnTick() override;

    void RunEventLoop() override;
};
