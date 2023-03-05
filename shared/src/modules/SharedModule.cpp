#include "Module.h"

// clang-format off
extern js::Class sharedPlayerClass;
static js::Module sharedModule("alt-shared", { &sharedPlayerClass }, [](js::ModuleTemplate& module)
{
    module.StaticProperty("test", 42);
});
