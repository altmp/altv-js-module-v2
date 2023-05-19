#pragma once

#include "interfaces/IResource.h"
#include "helpers/JS.h"

#include "v8.h"

class CJavaScriptResource : public js::IResource
{
    std::unique_ptr<v8::MicrotaskQueue> microtaskQueue;

public:
    CJavaScriptResource(alt::IResource* resource, v8::Isolate* isolate) : IResource(resource, isolate) {}

    bool Start() override;
    bool Stop() override;

    void OnTick() override;

    void RunEventLoop() override;
};
