#include "CNodeResource.h"
#include "CNodeRuntime.h"
#include "Bindings.h"
#include "Event.h"

void CNodeResource::LoadConfig()
{
    Config::Value::ValuePtr config = resource->GetConfig();
    if(!config->IsDict()) return;

    Config::Value::ValuePtr jsConfig = config["js-module-v2"];
    if(!jsConfig->IsDict()) return;

    bool compatibilityEnabled = jsConfig["compatibilityEnabled"]->AsBool(false);
    ToggleCompatibilityMode(compatibilityEnabled);
}

std::unordered_map<std::string, std::string> CNodeResource::GetMetricAttributes()
{
    return { { "resource", GetResource()->GetName() } };
}

static void ResourceStarted(js::FunctionContext& ctx)
{
    v8::Local<v8::Value> exports;
    if(!ctx.GetArg(0, exports)) return;
    ctx.GetResource<CNodeResource>()->EnvStarted(exports);
}

void CNodeResource::EnvStarted(v8::Local<v8::Value> exports)
{
    if(exports->IsNullOrUndefined())
    {
        startError = true;
        return;
    }
    envStarted = true;
    alt::MValueDict exportsDict = std::dynamic_pointer_cast<alt::IMValueDict>(js::JSToMValue(exports));
    GetResource()->SetExports(exportsDict);
}

bool CNodeResource::Start()
{
    v8::Locker locker(isolate);
    v8::Isolate::Scope isolateScope(isolate);
    v8::HandleScope handleScope(isolate);

    v8::Local<v8::ObjectTemplate> global = v8::ObjectTemplate::New(isolate);
    v8::Local<v8::Context> _context = node::NewContext(isolate, global);
    v8::Context::Scope scope(_context);
    context.Reset(isolate, _context);

    LoadConfig();
    IResource::Initialize();

    uvLoop = new uv_loop_t;
    uv_loop_init(uvLoop);

    nodeData = node::CreateIsolateData(isolate, uvLoop, CNodeRuntime::Instance().GetPlatform());
    if(!nodeData) return false;
    std::vector<std::string> argv = { "altv-resource" };
    node::EnvironmentFlags::Flags flags = (node::EnvironmentFlags::Flags)(node::EnvironmentFlags::kOwnsProcessState & node::EnvironmentFlags::kNoCreateInspector);
    env = node::CreateEnvironment(nodeData, _context, argv, argv, flags);

    IResource::InitializeBindings(js::Binding::Scope::SERVER, js::Module::Get("@altv/server"));

    const js::Binding& bootstrapper = js::Binding::Get("server/bootstrap.js");
    if(!bootstrapper.IsValid()) return false;

    js::TemporaryGlobalExtension altModuleExtension(_context, "__altModule", js::Module::Get("@altv/server").GetNamespace(this));
    js::TemporaryGlobalExtension cppBindingsExtension(_context, "__cppBindings", js::Module::Get("cppBindings").GetNamespace(this));
    js::TemporaryGlobalExtension altServerModuleExtension(_context, "__resourceStarted", ResourceStarted);
    node::LoadEnvironment(env, bootstrapper.GetSource());

    asyncResource.Reset(isolate, v8::Object::New(isolate));
    asyncContext = node::EmitAsyncInit(isolate, asyncResource.Get(isolate), "CNodeResource");

    while(!envStarted && !startError)
    {
        CNodeRuntime::Instance().OnTick();
        OnTick();
    }

    if (IsCompatibilityModeEnabled())
    {
        auto resourceName = resource->GetName();
        js::Logger::Colored << "~y~[JS] Compatibility mode is enabled for resource " << resourceName << js::Logger::Endl;
    }

    return true;
}

bool CNodeResource::Stop()
{
    js::Logger::Colored << "~y~[JS] Stopping resource " << resource->GetName() << js::Logger::Endl;
    IResource::Scope scope(this);

    js::Logger::Colored << "~y~[JS] Emitting process exit event" << js::Logger::Endl;
    node::EmitAsyncDestroy(isolate, asyncContext);
    js::Logger::Colored << "~y~[JS] Resetting asyncResource" << js::Logger::Endl;
    asyncResource.Reset();

    js::Logger::Colored << "~y~[JS] Emitting process exit event" << js::Logger::Endl;
    node::EmitProcessBeforeExit(env);
    node::EmitProcessExit(env);

    js::Logger::Colored << "~y~[JS] Stopping environment" << js::Logger::Endl;
    node::Stop(env);

    js::Logger::Colored << "~y~[JS] Freeing environment" << js::Logger::Endl;
    node::FreeEnvironment(env);
    js::Logger::Colored << "~y~[JS] Freeing isolate data" << js::Logger::Endl;
    node::FreeIsolateData(nodeData);

    js::Logger::Colored << "~y~[JS] Closing uv loop" << js::Logger::Endl;
    uv_loop_close(uvLoop);
    delete uvLoop;

    js::Logger::Colored << "~y~[JS] Resetting resource" << js::Logger::Endl;
    IResource::Reset();
    js::Logger::Colored << "~y~[JS] Cleaning up metrics" << js::Logger::Endl;
    IMetricHandler::CleanupMetrics();

    js::Logger::Colored << "~y~[JS] Resource stopped" << js::Logger::Endl;
    return true;
}

void CNodeResource::OnTick()
{
    IResource::Scope scope(this);
    node::CallbackScope callbackScope(isolate, asyncResource.Get(isolate), asyncContext);

    uv_run(uvLoop, UV_RUN_NOWAIT);
    IAltResource::OnTick();
}

void CNodeResource::RunEventLoop()
{
    CNodeRuntime::Instance().OnTick();
    IAltResource::RunEventLoop();
}
