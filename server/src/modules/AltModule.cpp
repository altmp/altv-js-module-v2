#include "Module.h"

// clang-format off
extern js::Class playerClass;
static js::Module altModule("alt", "alt-shared", { &playerClass }, [](js::ModuleTemplate& module)
{
    module.StaticProperty("test2", 66);
});
