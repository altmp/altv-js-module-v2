#include "Module.h"
#include "Namespace.h"

static void Log(js::FunctionContext& ctx)
{
    std::string msg;
    if(!ctx.GetArg(0, msg)) return;

    alt::ICore::Instance().LogInfo(msg);
}

// clang-format off
extern js::Class sharedPlayerClass;
static js::Module sharedModule("alt-shared", { &sharedPlayerClass }, [](js::ModuleTemplate& module)
{
    module.StaticFunction("log", Log);

    #ifdef ALT_CLIENT_API
    bool isClient = true;
    #else
    bool isClient = false;
    #endif
    module.StaticProperty("isClient", isClient);
    module.StaticProperty("isServer", !isClient);

    module.Namespace("Timers");
    module.Namespace("Events");
});
