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

EXPORT bool altMain(alt::ICore* core)
{
    printf("Printing shit out!\n");
    alt::ICore::SetInstance(core);

    CNodeRuntime& runtime = CNodeRuntime::Instance();
    core->RegisterScriptRuntime("jsv2", &runtime);
    if(!runtime.Initialize()) return false;

    js::Logger::Colored("Loaded ~g~JS module v2");

    return true;
}

EXPORT const char* GetSDKHash()
{
    return ALT_SDK_VERSION;
}
