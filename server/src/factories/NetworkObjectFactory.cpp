#include "FactoryHandler.h"
#include "Logger.h"

// clang-format off
static js::FactoryHandler networkObjectFactory(alt::IBaseObject::Type::NETWORK_OBJECT, [](js::Object& args) -> alt::IBaseObject* {
    uint32_t model = 0;
    if(args.GetType("model") == js::Type::NUMBER)      model = args.Get<uint32_t>("model");
    else if(args.GetType("model") == js::Type::STRING) model = alt::ICore::Instance().Hash(args.Get<std::string>("model"));
    alt::Vector3f pos;
    if(!args.Get("pos", pos)) return nullptr;
    alt::Vector3f rot = args.Get<alt::Vector3f>("rot");
    return alt::ICore::Instance().CreateObject(model, pos, rot);
});
