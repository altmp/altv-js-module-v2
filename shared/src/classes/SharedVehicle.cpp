#include "Class.h"
#include "cpp-sdk/ICore.h"

// clang-format off
extern js::Class entityClass;
extern js::Class sharedVehicleClass("Vehicle", &entityClass, nullptr, [](js::ClassTemplate& tpl)
{
});
