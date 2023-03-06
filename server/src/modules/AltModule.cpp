#include "Module.h"
#include "Namespace.h"

// clang-format off
extern js::Class playerClass, vehicleClass;
static js::Module altModule("alt", "alt-shared", { &playerClass, &vehicleClass }, [](js::ModuleTemplate& module)
{
});
