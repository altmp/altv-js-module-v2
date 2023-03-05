#include "Class.h"
#include "module/IResource.h"
#include "cpp-sdk/ICore.h"

// clang-format off
extern js::Class sharedPlayerClass("Player", nullptr, [](js::ClassTemplate& templ)
{
    templ.StaticProperty("shared", 23);
});
