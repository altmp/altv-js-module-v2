#include "version/version.h"
#include "SDK.h"
#include "CNodeRuntime.h"

EXPORT bool altMain(alt::ICore* core)
{
    alt::ICore::SetInstance(core);

    js::CNodeRuntime& runtime = js::CNodeRuntime::Instance();
    core->RegisterScriptRuntime("js", &runtime);
    if(!runtime.Initialize()) return false;

    core->LogColored("Loaded ~g~JS module v2");

    return true;
}

EXPORT const char* GetSDKHash()
{
    return ALT_SDK_VERSION;
}
