#include "Class.h"
#include "cpp-sdk/ICore.h"

// clang-format off
extern js::Class sharedWorldEntityClass;
extern js::Class sharedEntityClass("Entity", &sharedWorldEntityClass, nullptr, [](js::ClassTemplate& tpl)
{
});
