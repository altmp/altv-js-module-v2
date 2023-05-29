#pragma once

#include "interfaces/IRuntime.h"
#include "CJavaScriptResource.h"

#include "v8.h"

class CJavaScriptRuntime : public js::IRuntime<CJavaScriptRuntime, CJavaScriptResource>
{
    std::unique_ptr<v8::Platform> platform;
    v8::Isolate* isolate;

    static void OnFatalError(const char* location, const char* message);
    static void OnHeapOOM(const char* location, bool isHeap);
    static size_t OnNearHeapLimit(void*, size_t current, size_t initial);
    static void OnPromiseRejected(v8::PromiseRejectMessage message);
    static v8::MaybeLocal<v8::Promise> ImportModuleDynamically(
      v8::Local<v8::Context> context, v8::Local<v8::Data> hostDefinedOptions, v8::Local<v8::Value> resourceName, v8::Local<v8::String> specifier, v8::Local<v8::FixedArray> importAssertions);
    static void InitializeImportMetaObject(v8::Local<v8::Context> context, v8::Local<v8::Module>, v8::Local<v8::Object> meta);
    static void MessageListener(v8::Local<v8::Message> message, v8::Local<v8::Value> error);
    void SetupIsolateHandlers();

public:
    bool Initialize() override;

    void OnTick() override;
    void OnDispose() override;
};
