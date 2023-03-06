#include "CNodeResource.h"
#include "CNodeRuntime.h"
#include "Bindings.h"
#include "Event.h"

bool CNodeResource::Start()
{
    v8::Locker locker(isolate);
    v8::Isolate::Scope isolateScope(isolate);
    v8::HandleScope handleScope(isolate);

    v8::Local<v8::ObjectTemplate> global = v8::ObjectTemplate::New(isolate);
    v8::Local<v8::Context> _context = node::NewContext(isolate, global);
    v8::Context::Scope scope(_context);
    _context->SetAlignedPointerInEmbedderData(ContextInternalFieldIdx, this);
    context.Reset(isolate, _context);

    IResource::Initialize();
    IResource::InitializeBindings(js::Binding::Scope::SERVER, js::Module::Get("alt"));

    uvLoop = new uv_loop_t;
    uv_loop_init(uvLoop);

    nodeData = node::CreateIsolateData(isolate, uvLoop, CNodeRuntime::Instance().GetPlatform());
    if(!nodeData) return false;
    std::vector<std::string> argv = { "altv-resource" };
    node::EnvironmentFlags::Flags flags = (node::EnvironmentFlags::Flags)(node::EnvironmentFlags::kOwnsProcessState & node::EnvironmentFlags::kNoCreateInspector);
    env = node::CreateEnvironment(nodeData, _context, argv, argv, flags);

    const js::Binding& bootstrapper = js::Binding::Get("server/bootstrap.js");
    if(!bootstrapper.IsValid()) return false;
    node::LoadEnvironment(env, bootstrapper.GetSource().c_str());

    asyncResource.Reset(isolate, v8::Object::New(isolate));
    asyncContext = node::EmitAsyncInit(isolate, asyncResource.Get(isolate), "CNodeResource");

    IResource::Started();

    return true;
}

bool CNodeResource::Stop()
{
    v8::Locker locker(isolate);
    v8::Isolate::Scope isolateScope(isolate);
    v8::HandleScope handleScope(isolate);

    {
        v8::Context::Scope scope(GetContext());
        IResource::Stopped();

        node::EmitAsyncDestroy(isolate, asyncContext);
        asyncResource.Reset();
    }

    node::EmitProcessBeforeExit(env);
    node::EmitProcessExit(env);

    node::Stop(env);

    node::FreeEnvironment(env);
    node::FreeIsolateData(nodeData);

    uv_loop_close(uvLoop);
    delete uvLoop;

    IResource::Reset();

    return true;
}

void CNodeResource::OnEvent(const alt::CEvent* ev) {}

void CNodeResource::OnTick()
{
    v8::Locker locker(isolate);
    v8::Isolate::Scope isolateScope(isolate);
    v8::HandleScope handleScope(isolate);
    v8::Context::Scope scope(GetContext());
    node::CallbackScope callbackScope(isolate, asyncResource.Get(isolate), asyncContext);

    uv_run(uvLoop, UV_RUN_NOWAIT);
    IResource::OnTick();
}
