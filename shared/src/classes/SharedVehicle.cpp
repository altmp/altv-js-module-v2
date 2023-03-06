#include "Class.h"
#include "cpp-sdk/ICore.h"

// clang-format off
extern js::Class sharedEntityClass;
extern js::Class sharedVehicleClass("Vehicle", &sharedEntityClass, nullptr, [](js::ClassTemplate& tpl)
{
});
