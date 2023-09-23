#include "CJavaScriptResource.h"
#include "CJavaScriptRuntime.h"
#include "helpers/Filesystem.h"

v8::Local<v8::Module> CJavaScriptResource::CompileAndRun(const std::string& path, const std::string& source)
{
    js::TryCatch tryCatch(isolate);

    v8::MaybeLocal<v8::Module> maybeMod = CompileModule(path, source);
    if(maybeMod.IsEmpty())
    {
        js::Logger::Error("[JS] Failed to compile file", path);
        tryCatch.Check(true, true);
        return v8::Local<v8::Module>();
    }
    v8::Local<v8::Module> mod = maybeMod.ToLocalChecked();

    if(!path.starts_with("internal:")) modules.insert({ path, { mod, Module::Type::File } });

    if(!InstantiateModule(GetContext(), mod) || tryCatch.HasCaught())
    {
        js::Logger::Error("[JS] Failed to instantiate file", path);
        if(mod->GetStatus() == v8::Module::kErrored) js::Logger::Error("[JS]", *v8::String::Utf8Value(isolate, mod->GetException()));
        tryCatch.Check(true, true);
        return v8::Local<v8::Module>();
    }
    v8::MaybeLocal<v8::Value> maybeResult = EvaluateModule(GetContext(), mod);
    if(maybeResult.IsEmpty() || maybeResult.ToLocalChecked().As<v8::Promise>()->State() == v8::Promise::PromiseState::kRejected)
    {
        js::Logger::Error("[JS] Failed to start file", path);
        if(mod->GetStatus() == v8::Module::kErrored)
        {
            js::Object exceptionObj = mod->GetException().As<v8::Object>();
            js::Logger::Error("[JS]", exceptionObj.Get<std::string>("message"));
            std::string stack = exceptionObj.Get<std::string>("stack");
            if(!stack.empty()) js::Logger::Error(stack);
        }
        tryCatch.Check(true, true);
        return v8::Local<v8::Module>();
    }
    js::Promise promise = maybeResult.ToLocalChecked().As<v8::Promise>();
    promise.Await();

    return mod;
}

void CJavaScriptResource::LoadConfig()
{
    Config::Value::ValuePtr config = resource->GetConfig();
    if(!config->IsDict()) return;

    Config::Value::ValuePtr jsConfig = config["js-module-v2"];
    if(!jsConfig->IsDict()) return;

    bool compatibilityEnabled = jsConfig["compatibilityEnabled"]->AsBool(false);
    ToggleCompatibilityMode(compatibilityEnabled);
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

    // Read main file
    alt::IResource* altResource = GetResource();
    std::string main = altResource->GetMain();
    if(!js::DoesFileExist(altResource->GetPackage(), main)) return false;
    std::vector<uint8_t> fileBuffer = js::ReadFile(altResource->GetPackage(), main);
    std::string source{ (char*)fileBuffer.data(), fileBuffer.size() };

    // Run it
    v8::Local<v8::Module> mod = CompileAndRun(main, source);
    if(mod.IsEmpty()) return false;

    alt::MValueDict exportsDict = std::dynamic_pointer_cast<alt::IMValueDict>(js::JSToMValue(mod->GetModuleNamespace()));
    GetResource()->SetExports(exportsDict);

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

void CJavaScriptResource::OnEvent(const alt::CEvent* ev)
{
    if(context.IsEmpty()) return;

    auto nativeScope = GetResource()->PushNativesScope();
    IAltResource::OnEvent(ev);
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
