#include "CNodeRuntime.h"

bool CNodeRuntime::Initialize()
{
    std::vector<std::string> args = GetNodeArgs();
    std::unique_ptr<node::InitializationResult> result =
      node::InitializeOncePerProcess(args, { node::ProcessInitializationFlags::kNoInitializeV8, node::ProcessInitializationFlags::kNoInitializeNodeV8Platform });
    if(result->errors().size() > 0)
    {
        for(const std::string& error : result->errors())
        {
            // Log::Error << "Error while initializing node: " << error << Log::Endl;
        }
        return false;
    }

    platform = node::MultiIsolatePlatform::Create(4);
    if(!platform) return false;
    v8::V8::InitializePlatform(platform.get());
    v8::V8::Initialize();

    isolate = node::NewIsolate(node::CreateArrayBufferAllocator(), uv_default_loop(), platform.get());
    if(!isolate) return false;

    {
        v8::Locker locker(isolate);
        v8::Isolate::Scope isolateScope(isolate);
        v8::HandleScope handleScope(isolate);

        // V8Class::LoadAll(isolate);
    }

    return true;
}

void CNodeRuntime::OnTick()
{
    v8::Locker locker(isolate);
    v8::Isolate::Scope isolateScope(isolate);
    v8::SealHandleScope seal(isolate);

    platform->DrainTasks(isolate);
}

std::vector<std::string> CNodeRuntime::GetNodeArgs()
{
    // https://nodejs.org/docs/latest-v18.x/api/cli.html#options
    std::vector<std::string> args = { "alt-server", "--trace-warnings" };

    Config::Value::ValuePtr moduleConfig = alt::ICore::Instance().GetServerConfig()["js-module-v2"];
    if(!moduleConfig->IsDict()) return args;

    // https://nodejs.org/api/cli.html#--inspecthostport
    Config::Value::ValuePtr inspector = moduleConfig["inspector"];
    if(!inspector->IsNone())
    {
        std::string inspectorHost = inspector["host"]->AsString("127.0.0.1");
        int inspectorPort = inspector["port"]->AsNumber(9229);
        args.push_back("--inspect=" + inspectorHost + ":" + std::to_string(inspectorPort));
    }

    // https://nodejs.org/api/cli.html#--enable-source-maps
    Config::Value::ValuePtr enableSourceMaps = moduleConfig["source-maps"];
    if(enableSourceMaps->AsBool(false)) args.push_back("--enable-source-maps");

    // https://nodejs.org/api/cli.html#--heap-prof
    Config::Value::ValuePtr enableHeapProfiler = moduleConfig["heap-profiler"];
    if(enableHeapProfiler->AsBool(false)) args.push_back("--heap-prof");

    // https://nodejs.org/api/cli.html#--experimental-global-webcrypto
    Config::Value::ValuePtr enableGlobalWebcrypto = moduleConfig["global-webcrypto"];
    if(enableGlobalWebcrypto->AsBool(false)) args.push_back("--experimental-global-webcrypto");

    // https://nodejs.org/api/cli.html#--experimental-network-imports
    Config::Value::ValuePtr enableNetworkImports = moduleConfig["network-imports"];
    if(enableNetworkImports->AsBool(false)) args.push_back("--experimental-network-imports");

    Config::Value::ValuePtr extraCliArgs = moduleConfig["extra-cli-args"];
    for(auto arg : extraCliArgs->AsList())
    {
        args.push_back(arg->AsString());
    }

    return args;
}
