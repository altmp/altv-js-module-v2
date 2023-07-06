#pragma once

#include "interfaces/IAltResource.h"
#include "node.h"
#include "uv.h"
#include "helpers/IMetricHandler.h"

class CNodeResource : public js::IAltResource, public js::IMetricHandler
{
    node::IsolateData* nodeData = nullptr;
    node::Environment* env = nullptr;
    uv_loop_t* uvLoop = nullptr;
    v8::Global<v8::Object> asyncResource;
    node::async_context asyncContext;
    bool envStarted = false;
    bool startError = false;

    virtual std::unordered_map<std::string, std::string> GetMetricAttributes() override;

public:
    CNodeResource(alt::IResource* resource, v8::Isolate* isolate) : IAltResource(resource, isolate) {}

    void EnvStarted(v8::Local<v8::Value> exports);

    bool Start() override;
    bool Stop() override;

    void OnTick() override;

    void RunEventLoop() override;
};
