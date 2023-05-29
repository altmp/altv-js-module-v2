#include "Module.h"

// clang-format off
extern js::Class playerClass, localPlayerClass;
extern js::Namespace eventsNamespace;
static js::Module altModule("@altv/client", "@altv/shared", { &playerClass, &localPlayerClass }, [](js::ModuleTemplate& module)
{
    module.StaticProperty("isClient", true);
    module.StaticProperty("isServer", false);

    module.Namespace(eventsNamespace);
});
