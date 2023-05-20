#include "Module.h"

// clang-format off
static js::Module altModule("@altv/client", "@altv/shared", { }, [](js::ModuleTemplate& module)
{
    module.StaticProperty("isClient", true);
    module.StaticProperty("isServer", false);
});
