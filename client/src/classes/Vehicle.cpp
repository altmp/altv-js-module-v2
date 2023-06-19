#include "Class.h"

// clang-format off
extern js::Class sharedVehicleClass;
extern js::Class vehicleClass("Vehicle", &sharedVehicleClass, nullptr, [](js::ClassTemplate& tpl)
{
    tpl.BindToType(alt::IBaseObject::Type::VEHICLE);

    tpl.GetByID<alt::IBaseObject::Type::VEHICLE>();
});
