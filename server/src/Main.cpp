#include "cpp-sdk/SDK.h"
#include "cpp-sdk/version/version.h"
#include "CNodeRuntime.h"
#include "Module.h"
#include "interfaces/IResource.h"
#include "Logger.h"

#include <iostream>

namespace server
{
    static void Initialize(v8::Local<v8::Object> exports, v8::Local<v8::Value>, v8::Local<v8::Context> context, void*)
    {
        if(!js::Module::Exists("alt"))
        {
            js::Logger::Error("INTERNAL ERROR: alt module not found");
            return;
        }

        js::Module& mod = js::Module::Get("alt");
        exports->SetPrototype(context, mod.GetNamespace(js::IResource::GetFromContext(context)));
    }
    NODE_MODULE_LINKED(alt, Initialize)
}  // namespace server

namespace shared
{
    static void InitializeShared(v8::Local<v8::Object> exports, v8::Local<v8::Value>, v8::Local<v8::Context> context, void*)
    {
        if(!js::Module::Exists("alt-shared"))
        {
            js::Logger::Error("INTERNAL ERROR: alt-shared module not found");
            return;
        }

        js::Module& mod = js::Module::Get("alt-shared");
        exports->SetPrototype(context, mod.GetNamespace(js::IResource::GetFromContext(context)));
    }
    NODE_MODULE_LINKED(altShared, InitializeShared)
}  // namespace shared

static void ModuleCommand(const std::vector<std::string>& args)
{
    if(args.size() == 0)
    {
        js::Logger::Colored("~y~Usage: ~w~js-module-v2 [options]");
        js::Logger::Colored("~y~Options:");
        js::Logger::Colored("  ~ly~--version ~w~- Version info");
    }
    else if(args[0] == "--version")
    {
        js::Logger::Colored("~g~JS Module v2:");
        js::Logger::Colored("~ly~module:", MODULE_VERSION);
        js::Logger::Colored("~ly~cpp-sdk:", ALT_SDK_VERSION);
        js::Logger::Colored("~ly~nodejs:", std::to_string(NODE_MAJOR_VERSION) + "." + std::to_string(NODE_MINOR_VERSION) + "." + std::to_string(NODE_PATCH_VERSION));
    }
}

EXPORT bool altMain(alt::ICore* core)
{
    alt::ICore::SetInstance(core);

    CNodeRuntime& runtime = CNodeRuntime::Instance();
    core->RegisterScriptRuntime("jsv2", &runtime);
    if(!runtime.Initialize()) return false;

    core->SubscribeCommand("js-module-v2", ModuleCommand);

    js::Logger::Colored("Loaded ~g~JS module v2");

    return true;
}

EXPORT const char* GetSDKHash()
{
    return ALT_SDK_VERSION;
}
