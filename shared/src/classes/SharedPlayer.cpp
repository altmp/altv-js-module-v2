#include "Class.h"
#include "cpp-sdk/ICore.h"

// clang-format off
extern js::Class sharedPlayerClass("Player", nullptr, [](js::ClassTemplate& tpl)
{
    tpl.StaticProperty("shared", 23);
});
