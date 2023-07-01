#include "FactoryHandler.h"

// clang-format off
static js::FactoryHandler blipFactory(alt::IBaseObject::Type::BLIP, [](js::Object& args) -> alt::IBaseObject* {
    alt::IBlip::BlipType blipType;
    if(!args.Get("blipType", blipType)) return nullptr;
    bool global;
    if(!args.Get("global", global)) return nullptr;
    std::vector<alt::IPlayer*> targets = args.Get<std::vector<alt::IPlayer*>>("targets");

    switch(blipType)
    {
        case alt::IBlip::BlipType::AREA:
        {
            alt::Vector3f pos;
            alt::Vector2f scale;

            if(!args.Get("pos", pos)) return nullptr;
            if(!args.Get("scale", scale)) return nullptr;

            alt::IBlip* blip = alt::ICore::Instance().CreateBlip(global, blipType, pos, targets);
            blip->SetScaleXY(scale);
            return blip;
        }
        case alt::IBlip::BlipType::RADIUS:
        {
            alt::Vector3f pos;
            float radius;

            if(!args.Get("pos", pos)) return nullptr;
            if(!args.Get("radius", radius)) return nullptr;

            alt::IBlip* blip = alt::ICore::Instance().CreateBlip(global, blipType, pos, targets);
            blip->SetScaleXY({ radius, radius });
            return blip;
        }
        case alt::IBlip::BlipType::DESTINATION:
        {
            if(args.Has("pos"))
            {
                alt::Vector3f pos;
                if(!args.Get("pos", pos)) return nullptr;
                return alt::ICore::Instance().CreateBlip(global, blipType, pos, targets);
            }
            else if(args.Has("entity"))
            {
                alt::IEntity* entity;
                if(!args.Get("entity", entity)) return nullptr;
                return alt::ICore::Instance().CreateBlip(global, blipType, entity, targets);
            }
            else break;
        }
    }

    js::Throw("Invalid Blip type");
    return nullptr;
});
