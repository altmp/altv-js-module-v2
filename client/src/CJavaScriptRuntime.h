#pragma once

#include "interfaces/IRuntime.h"
#include "CJavaScriptResource.h"

#include "v8.h"

class CJavaScriptRuntime : public js::IRuntime<CJavaScriptRuntime, CJavaScriptResource>
{
    std::unique_ptr<v8::Platform> platform;
    v8::Isolate* isolate;

public:
    bool Initialize() override;

    void OnTick() override;
    void OnDispose() override;
};
