#include "Class.h"
#include "cpp-sdk/ICore.h"

// clang-format off
extern js::Class baseObjectClass;
extern js::Class sharedWorldEntityClass("WorldEntity", &baseObjectClass, nullptr, [](js::ClassTemplate& tpl)
{
});
