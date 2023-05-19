#include "CJavaScriptRuntime.h"
#include "libplatform/libplatform.h"

bool CJavaScriptRuntime::Initialize()
{
    v8::V8::SetFlagsFromString("--harmony-import-assertions --short-builtin-calls --no-lazy --no-flush-bytecode");
    platform = v8::platform::NewDefaultPlatform();
    v8::V8::InitializePlatform(platform.get());
    v8::V8::InitializeICU((alt::ICore::Instance().GetClientPath() + "/libs/icudtl_v8.dat").c_str());
    v8::V8::Initialize();

    v8::Isolate::CreateParams createParams;
    createParams.array_buffer_allocator = v8::ArrayBuffer::Allocator::NewDefaultAllocator();
    createParams.allow_atomics_wait = false;

    isolate = v8::Isolate::New(createParams);
    isolate->SetMicrotasksPolicy(v8::MicrotasksPolicy::kExplicit);
    isolate->SetCaptureStackTraceForUncaughtExceptions(true, 5);

    // todo: add handlers for messages etc.

    v8::Locker locker(isolate);
    v8::Isolate::Scope isolateScope(isolate);
    v8::HandleScope handleScope(isolate);

    return IRuntime::Initialize();
}

void CJavaScriptRuntime::OnTick()
{
    v8::Locker locker(isolate);
    v8::Isolate::Scope isolateScope(isolate);
    v8::HandleScope handleScope(isolate);

    v8::platform::PumpMessageLoop(platform.get(), isolate);
}

void CJavaScriptRuntime::OnDispose()
{
    while(isolate->IsInUse()) isolate->Exit();
    isolate->Dispose();
    v8::V8::Dispose();
    v8::V8::ShutdownPlatform();

    delete isolate->GetArrayBufferAllocator();
}
