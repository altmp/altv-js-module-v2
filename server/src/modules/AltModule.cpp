#include "Module.h"

static js::Module altModule("alt", "alt-shared", [](v8pp::module& module) { module.const_("test2", 66); });
