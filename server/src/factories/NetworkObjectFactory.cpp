#include "FactoryHandler.h"
#include "Logger.h"

// clang-format off
static js::FactoryHandler networkObjectFactory(alt::IBaseObject::Type::NETWORK_OBJECT, [](js::Object& args) -> alt::IBaseObject* {
    uint32_t model;
    if(!args.GetAsHash("model", model)) return nullptr;
    alt::Vector3f pos;
    if(!args.Get("pos", pos)) return nullptr;
    alt::Vector3f rot = args.Get<alt::Vector3f>("rot");
    uint8_t alpha = args.Get<uint8_t>("alpha", 255);
    uint8_t textureVariation = args.Get<uint8_t>("textureVariation", 0);
    uint16_t lodDistance = args.Get<uint16_t>("lodDistance", 100);
    return alt::ICore::Instance().CreateNetworkObject(model, pos, rot, alpha, textureVariation, lodDistance);
});
