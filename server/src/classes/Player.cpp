#include "Class.h"
#include "module/IResource.h"
#include "cpp-sdk/ICore.h"

// clang-format off
extern js::Class sharedPlayerClass;
extern js::Class playerClass("Player", &sharedPlayerClass, nullptr, [](js::ClassTemplate& templ)
{
    templ.StaticProperty("server", 45);
});
