#include "FactoryHandler.h"

// clang-format off
static js::FactoryHandler vehicleFactory(alt::IBaseObject::Type::VEHICLE, [](js::Object& args) -> alt::IBaseObject* {
    uint32_t model;
    if(!args.GetAsHash("model", model)) return nullptr;
    alt::Vector3f pos;
    if(!args.Get("pos", pos)) return nullptr;
    alt::Vector3f rot = args.Get<alt::Vector3f>("rot");
    uint32_t streamingDistance = args.Get<uint32_t>("streamingDistance", 0);

    return alt::ICore::Instance().CreateVehicle(model, pos, rot, streamingDistance);
});
