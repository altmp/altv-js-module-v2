#include "Module.h"
#include "Namespace.h"

// clang-format off
extern js::Class playerClass, vehicleClass, baseObjectClass;
static js::Module altModule("alt", "alt-shared", { &playerClass, &vehicleClass, &baseObjectClass }, [](js::ModuleTemplate& module)
{
    module.StaticProperty("isClient", false);
    module.StaticProperty("isServer", true);
});
