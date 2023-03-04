#include "cpp-sdk/SDK.h"
#include "cpp-sdk/version/version.h"
#include "CNodeRuntime.h"
#include "Module.h"
#include <iostream>

static void Initialize(v8::Local<v8::Object> exports, v8::Local<v8::Value>, v8::Local<v8::Context> context, void*)
{
    if(!js::Module::Exists("alt"))
    {
        alt::ICore::Instance().LogError("INTERNAL ERROR: alt module not found");
        return;
    }

    js::Module& mod = js::Module::Get("alt");
    exports->SetPrototype(context, mod.GetNamespace(context));
}
NODE_MODULE_LINKED(alt, Initialize)

static void InitializeShared(v8::Local<v8::Object> exports, v8::Local<v8::Value>, v8::Local<v8::Context> context, void*)
{
    if(!js::Module::Exists("alt-shared"))
    {
        alt::ICore::Instance().LogError("INTERNAL ERROR: alt-shared module not found");
        return;
    }

    js::Module& mod = js::Module::Get("alt-shared");
    exports->SetPrototype(context, mod.GetNamespace(context));
}
NODE_MODULE_LINKED(altShared, InitializeShared)

EXPORT bool altMain(alt::ICore* core)
{
    alt::ICore::SetInstance(core);

    CNodeRuntime& runtime = CNodeRuntime::Instance();
    core->RegisterScriptRuntime("js", &runtime);
    if(!runtime.Initialize()) return false;

    core->LogColored("Loaded ~g~JS module v2");

    return true;
}

EXPORT const char* GetSDKHash()
{
    return ALT_SDK_VERSION;
}
