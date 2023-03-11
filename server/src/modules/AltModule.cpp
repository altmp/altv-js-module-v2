#include "Module.h"
#include "Namespace.h"

// clang-format off
extern js::Class playerClass, vehicleClass;
extern js::Namespace eventsNamespace;
static js::Module altModule("alt", "alt-shared", { &playerClass, &vehicleClass }, [](js::ModuleTemplate& module)
{
    module.StaticProperty("isClient", false);
    module.StaticProperty("isServer", true);

    module.Namespace(eventsNamespace);
});
