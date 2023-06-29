#include "FactoryHandler.h"

// clang-format off
static js::FactoryHandler pedFactory(alt::IBaseObject::Type::PED, [](js::Object& args) -> alt::IBaseObject* {
    uint32_t model;
    if(!args.GetAsHash("model", model)) return nullptr;
    alt::Vector3f pos;
    if(!args.Get("pos", pos)) return nullptr;
    float heading = args.Get<float>("heading");
    return alt::ICore::Instance().CreatePed(model, pos, { 0, 0, heading });
});
