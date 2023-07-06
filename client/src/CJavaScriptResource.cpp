#include "CJavaScriptResource.h"
#include "CJavaScriptRuntime.h"
#include "helpers/Filesystem.h"

void CJavaScriptResource::StartResource(js::FunctionContext& ctx)
{
    CJavaScriptResource* resource = ctx.GetResource<CJavaScriptResource>();
    v8::Local<v8::Context> context = ctx.GetContext();

    alt::IResource* altResource = resource->GetResource();
    const std::string& main = resource->GetResource()->GetMain();
    if(!ctx.Check(js::DoesFileExist(altResource->GetPackage(), main), "Failed to read main file")) return;

    std::vector<uint8_t> fileBuffer = js::ReadFile(altResource->GetPackage(), main);
    std::string source{ (char*)fileBuffer.data(), fileBuffer.size() };

    v8::Local<v8::Module> mod = resource->CompileAndRun(main, source);
    if(!ctx.Check(!mod.IsEmpty(), "Failed to compile main file")) return;

    alt::MValueDict exportsDict = std::dynamic_pointer_cast<alt::IMValueDict>(js::JSToMValue(mod->GetModuleNamespace()));
    resource->GetResource()->SetExports(exportsDict);
    resource->started = true;
}

v8::Local<v8::Module> CJavaScriptResource::CompileAndRun(const std::string& path, const std::string& source)
{
    v8::MaybeLocal<v8::Module> maybeMod = CompileModule(path, source);
    if(maybeMod.IsEmpty())
    {
        js::Logger::Error("[JS] Failed to compile file", path);
        return v8::Local<v8::Module>();
    }
    v8::Local<v8::Module> mod = maybeMod.ToLocalChecked();

    if(!path.starts_with("internal:")) modules.insert({ path, { mod, Module::Type::File } });

    if(!InstantiateModule(GetContext(), mod))
    {
        js::Logger::Error("[JS] Failed to instantiate file", path);
        return v8::Local<v8::Module>();
    }
    v8::MaybeLocal<v8::Value> maybeResult = EvaluateModule(GetContext(), mod);
    if(maybeResult.IsEmpty() || maybeResult.ToLocalChecked().As<v8::Promise>()->State() == v8::Promise::PromiseState::kRejected)
    {
        js::Logger::Error("[JS] Failed to start file", path);
        if(mod->GetStatus() == v8::Module::kErrored) js::Logger::Error("[JS]", *v8::String::Utf8Value(isolate, mod->GetException()));
        return v8::Local<v8::Module>();
    }
    js::Promise promise = maybeResult.ToLocalChecked().As<v8::Promise>();
    promise.Await();

    return mod;
}

bool CJavaScriptResource::Start()
{
    v8::Locker locker(isolate);
    v8::Isolate::Scope isolateScope(isolate);
    v8::HandleScope handleScope(isolate);

    GetResource()->EnableNatives();
    auto nativeScope = GetResource()->PushNativesScope();
    nativeContext = alt::ICore::Instance().CreateNativesContext();

    microtaskQueue = v8::MicrotaskQueue::New(isolate, v8::MicrotasksPolicy::kExplicit);
    v8::Local<v8::Context> _context = v8::Context::New(isolate, nullptr, v8::MaybeLocal<v8::ObjectTemplate>(), v8::Local<v8::Value>(), nullptr, microtaskQueue.get());
    context.Reset(isolate, _context);

    v8::Context::Scope scope(_context);
    IResource::Initialize();
    IResource::InitializeBindings(js::Binding::Scope::CLIENT, js::Module::Get("@altv/client"));

    const js::Binding& bootstrapper = js::Binding::Get("client/bootstrap.js");
    if(!bootstrapper.IsValid()) return false;

    js::TemporaryGlobalExtension startResourceExtension(GetContext(), "__startResource", StartResource);
    js::TemporaryGlobalExtension altModuleExtension(GetContext(), "__altModule", js::Module::Get("@altv/client").GetNamespace(this));
    v8::Local<v8::Module> mod = CompileAndRun("internal:" + bootstrapper.GetName(), bootstrapper.GetSource());
    if(mod.IsEmpty())
    {
        js::Logger::Error("[JS] Failed to start bootstrapper");
        js::Binding::DumpAll();
        return false;
    }

    return true;
}

bool CJavaScriptResource::Stop()
{
    if(context.IsEmpty()) return false;

    IResource::Scope scope(this);
    auto nativeScope = GetResource()->PushNativesScope();

    microtaskQueue.reset();

    IExceptionHandler::Reset();
    IModuleHandler::Reset();
    IResource::Reset();

    return true;
}

void CJavaScriptResource::OnTick()
{
    if(context.IsEmpty()) return;

    IResource::Scope scope(this);
    auto nativeScope = GetResource()->PushNativesScope();

    microtaskQueue->PerformCheckpoint(isolate);

    IAltResource::OnTick();
}

void CJavaScriptResource::RunEventLoop()
{
    CJavaScriptRuntime::Instance().OnTick();
    IAltResource::RunEventLoop();
}
