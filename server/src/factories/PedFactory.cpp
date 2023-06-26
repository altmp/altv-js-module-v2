#include "FactoryHandler.h"

// clang-format off
static js::FactoryHandler pedFactory(alt::IBaseObject::Type::PED, [](js::Object& args) -> alt::IBaseObject* {
    uint32_t model = 0;
    if(args.GetType("model") == js::Type::NUMBER)      model = args.Get<uint32_t>("model");
    else if(args.GetType("model") == js::Type::STRING) model = alt::ICore::Instance().Hash(args.Get<std::string>("model"));
    alt::Vector3f pos;
    if(!args.Get("pos", pos)) return nullptr;
    float heading = args.Get<float>("heading");
    return alt::ICore::Instance().CreatePed(model, pos, { 0, 0, heading });
});
