#include "FactoryHandler.h"
#include "interfaces/IResource.h"

// clang-format off
static js::FactoryHandler weaponObjectFactory(alt::IBaseObject::Type::OBJECT, [](js::Object& args) -> alt::IBaseObject* {
    alt::Vector3f pos;
    if(!args.Get("pos", pos)) return nullptr;

    alt::Vector3f rot;
    if(!args.Get("rot", rot)) return nullptr;

    uint32_t weaponHash = 0;
    if(args.GetType("weaponHash") == js::Type::NUMBER)      weaponHash = args.Get<uint32_t>("weaponHash");
    else if(args.GetType("weaponHash") == js::Type::STRING) weaponHash = alt::ICore::Instance().Hash(args.Get<std::string>("weaponHash"));

    uint32_t modelHash = 0;
    if(args.GetType("modelHash") == js::Type::NUMBER)      weaponHash = args.Get<uint32_t>("modelHash");
    else if(args.GetType("modelHash") == js::Type::STRING) weaponHash = alt::ICore::Instance().Hash(args.Get<std::string>("modelHash"));

    float numAmmo = args.Get<float>("numAmmo", 100);
    bool createDefaultComponents = args.Get<bool>("createDefaultComponents", true);
    float scale = args.Get<float>("scale", 1);
    bool useStreaming = args.Get<bool>("useStreaming", false);
    uint32_t streamingDistance = args.Get<uint32_t>("streamingDistance", 0);

    return alt::ICore::Instance().CreateWeaponObject(pos, rot, weaponHash, modelHash, numAmmo, createDefaultComponents, scale, useStreaming, streamingDistance, args.GetResource()->GetResource());
});
