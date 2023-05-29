#include "Class.h"

// clang-format off
extern js::Class playerClass;
extern js::Class localPlayerClass("LocalPlayer", &playerClass, nullptr, [](js::ClassTemplate& tpl)
{
    tpl.BindToType(alt::IBaseObject::Type::LOCAL_PLAYER);
});
