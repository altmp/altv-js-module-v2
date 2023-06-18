#include "FactoryHandler.h"
#include "interfaces/IResource.h"

// clang-format off
static js::FactoryHandler blipFactory(alt::IBaseObject::Type::BLIP, [](js::Object& args) -> alt::IBaseObject* {
    alt::IResource* resource = args.GetResource()->GetResource();

    alt::IBlip::BlipType blipType;
    if(!args.Get("blipType", blipType)) return nullptr;

    switch(blipType)
    {
        case alt::IBlip::BlipType::AREA:
        {
            alt::Vector3f pos;
            alt::Vector2f size;

            if(!args.Get("pos", pos)) return nullptr;
            if(!args.Get("size", size)) return nullptr;

            alt::IBlip* blip = alt::ICore::Instance().CreateBlip(pos, size[0], size[1], resource);
            return blip;
        }
        case alt::IBlip::BlipType::RADIUS:
        {
            alt::Vector3f pos;
            float radius;

            if(!args.Get("pos", pos)) return nullptr;
            if(!args.Get("radius", radius)) return nullptr;

            alt::IBlip* blip = alt::ICore::Instance().CreateBlip(pos, radius, resource);
            return blip;
        }
        case alt::IBlip::BlipType::DESTINATION:
        {
            if(args.Has("pos"))
            {
                alt::Vector3f pos;
                if(!args.Get("pos", pos)) return nullptr;
                return alt::ICore::Instance().CreateBlip(blipType, pos, resource);
            }
            else if(args.Has("entity"))
            {
                uint32_t entityID = 0;
                if(args.GetType("entity") == js::Type::BASE_OBJECT) entityID = args.Get<alt::IEntity*>("entity")->GetScriptID();
                else if(args.GetType("entity") == js::Type::NUMBER) entityID = args.Get<uint32_t>("entity");
                else return nullptr;
                return alt::ICore::Instance().CreateBlip(blipType, entityID, resource);
            }
            else break;
        }
    }

    js::Throw("Invalid Blip type");
    return nullptr;
});
