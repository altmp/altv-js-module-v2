#pragma once

#include "module/IResource.h"
#include "node.h"
#include "uv.h"

class CNodeResource : public js::IResource
{
    node::IsolateData* nodeData = nullptr;
    node::Environment* env = nullptr;
    uv_loop_t* uvLoop = nullptr;
    v8::Global<v8::Object> asyncResource;
    node::async_context asyncContext;
    v8::Global<v8::Context> context;

public:
    CNodeResource(alt::IResource* resource, v8::Isolate* isolate) : IResource(resource, isolate) {}

    bool Start() override;
    bool Stop() override;

    void OnEvent(const alt::CEvent* ev) override;
    void OnTick() override;

    v8::Local<v8::Context> GetContext() const
    {
        return context.Get(isolate);
    }
};
