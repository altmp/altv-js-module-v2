#include "CJavaScriptResource.h"
#include "CJavaScriptRuntime.h"

bool CJavaScriptResource::Start()
{
    v8::Locker locker(isolate);
    v8::Isolate::Scope isolateScope(isolate);
    v8::HandleScope handleScope(isolate);

    microtaskQueue = v8::MicrotaskQueue::New(isolate, v8::MicrotasksPolicy::kExplicit);
    v8::Local<v8::Context> _context = v8::Context::New(isolate, nullptr, v8::MaybeLocal<v8::ObjectTemplate>(), v8::Local<v8::Value>(), nullptr, microtaskQueue.get());
    context.Reset(isolate, _context);

    v8::Context::Scope scope(_context);
    IResource::Initialize();
    IResource::InitializeBindings(js::Binding::Scope::CLIENT, js::Module::Get("alt"));

    const js::Binding& bootstrapper = js::Binding::Get("client/bootstrap.js");
    if(!bootstrapper.IsValid()) return false;

    // todo: load bootstrapper

    return true;
}

bool CJavaScriptResource::Stop()
{
    if(context.IsEmpty()) return;

    v8::Locker locker(isolate);
    v8::Isolate::Scope isolateScope(isolate);
    v8::HandleScope handleScope(isolate);

    microtaskQueue.reset();

    IResource::Reset();
}

void CJavaScriptResource::OnTick()
{
    if(context.IsEmpty()) return;

    v8::Locker locker(isolate);
    v8::Isolate::Scope isolateScope(isolate);
    v8::HandleScope handleScope(isolate);
    v8::Context::Scope scope(GetContext());

    microtaskQueue->PerformCheckpoint(isolate);

    IResource::OnTick();
}

void CJavaScriptResource::RunEventLoop()
{
    CJavaScriptRuntime::Instance().OnTick();
    IResource::RunEventLoop();
}
