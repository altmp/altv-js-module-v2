#include "Module.h"

extern js::Module sharedCppBindingsModule;
// !!! Make sure to keep the name as cppBindings
extern js::Module cppBindingsModule("cppBindings", "sharedCppBindings", [](js::ModuleTemplate& module) {});
