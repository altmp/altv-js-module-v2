#include "cpp-sdk/version/version.h"
#include "cpp-sdk/SDK.h"

#include "CommandHandlers.h"
#include "CJavaScriptRuntime.h"

EXPORT alt::IScriptRuntime* CreateScriptRuntime(alt::ICore* core)
{
    alt::ICore::SetInstance(core);

    CJavaScriptRuntime& runtime = CJavaScriptRuntime::Instance();
    if(!runtime.Initialize()) return nullptr;

    core->SubscribeCommand("debughandles", js::DebugHandlesCommand);
    core->SubscribeCommand("dumpbinding", js::DumpBindingCommand);
    core->SubscribeCommand("dumpallbindings", js::DumpAllBindingsCommand);

    return &runtime;
}

EXPORT const char* GetType()
{
    return "jsv2";
}

EXPORT const char* GetSDKHash()
{
    return ALT_SDK_VERSION;
}
