#include "cpp-sdk/SDK.h"
#include "cpp-sdk/version/version.h"
#include "CNodeRuntime.h"
#include "Module.h"
#include <iostream>

static void Initialize(v8::Local<v8::Object> exports, v8::Local<v8::Value>, v8::Local<v8::Context> context, void*)
{
    if(!js::Module::Exists("alt"))
    {
        // todo: log error
        return;
    }

    js::Module& mod = js::Module::Get("alt");
    exports->SetPrototype(context, mod.GetNamespace(context));
}
NODE_MODULE_LINKED(alt, Initialize)

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
