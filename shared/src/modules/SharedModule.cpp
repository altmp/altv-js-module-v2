#include "Module.h"

int test = 23;
static js::Module sharedModule("alt-shared", [](v8pp::module& module) { module.var("test", test); });
