#include "cpp-sdk/SDK.h"
#include "cpp-sdk/version/version.h"
#include "CNodeRuntime.h"

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
