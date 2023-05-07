#pragma once

#include "interfaces/IResource.h"
#include "node.h"
#include "uv.h"

class CNodeResource : public js::IResource
{
    node::IsolateData* nodeData = nullptr;
    node::Environment* env = nullptr;
    uv_loop_t* uvLoop = nullptr;
    v8::Global<v8::Object> asyncResource;
    node::async_context asyncContext;
    bool envStarted = false;
    bool startError = false;

public:
    CNodeResource(alt::IResource* resource, v8::Isolate* isolate) : IResource(resource, isolate) {}

    void EnvStarted(v8::Local<v8::Value> exports);

    bool Start() override;
    bool Stop() override;

    void OnEvent(const alt::CEvent* ev) override;
    void OnTick() override;

    void RunEventLoop() override;
};
