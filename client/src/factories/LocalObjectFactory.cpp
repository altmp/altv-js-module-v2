#include "FactoryHandler.h"
#include "interfaces/IResource.h"

// clang-format off
static js::FactoryHandler localObjectFactory(alt::IBaseObject::Type::LOCAL_OBJECT, [](js::Object& args) -> alt::IBaseObject* {
    bool isWeaponObject;
    if(!args.Get("weaponObject", isWeaponObject)) return nullptr;

    if(isWeaponObject)
    {
        alt::Vector3f pos;
        if(!args.Get("pos", pos)) return nullptr;

        alt::Vector3f rot;
        if(!args.Get("rot", rot)) return nullptr;

        uint32_t weaponHash;
        if(!args.GetAsHash("weapon", weaponHash)) return nullptr;

        uint32_t modelHash = args.GetAsHashOptional("model", weaponHash);
        float ammoCount = args.Get<float>("ammoCount", 100);
        bool createDefaultComponents = args.Get<bool>("createDefaultComponents", true);
        float scale = args.Get<float>("scale", 1);
        bool useStreaming = args.Get<bool>("useStreaming", false);
        uint32_t streamingDistance = args.Get<uint32_t>("streamingDistance", 0);

        return alt::ICore::Instance().CreateWeaponObject(pos, rot, weaponHash, modelHash, ammoCount, createDefaultComponents, scale, useStreaming, streamingDistance, args.GetResource()->GetResource());
    }
    else
    {
        uint32_t modelHash;
        if(!args.GetAsHash("model", modelHash)) return nullptr;

        alt::Vector3f pos;
        if(!args.Get("pos", pos)) return nullptr;

        alt::Vector3f rot;
        if(!args.Get("rot", rot)) return nullptr;

        bool noOffset = args.Get<bool>("noOffset", false);
        bool dynamic = args.Get<bool>("dynamic", false);
        bool useStreaming = args.Get<bool>("useStreaming", false);
        uint32_t streamingDistance = args.Get<uint32_t>("streamingDistance", 0);

        return alt::ICore::Instance().CreateLocalObject(modelHash, pos, rot, noOffset, dynamic, useStreaming, streamingDistance, args.GetResource()->GetResource());
    }
});
