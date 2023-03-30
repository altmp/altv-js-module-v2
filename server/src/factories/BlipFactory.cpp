#include "FactoryHandler.h"

// clang-format off
static js::FactoryHandler blipFactory(alt::IBaseObject::Type::BLIP, [](js::Object& args) -> alt::IBaseObject* {
    alt::IBlip::BlipType blipType;
    if(!args.Get("blipType", blipType)) return nullptr;

    switch(blipType)
    {
        case alt::IBlip::BlipType::AREA:
        {
            alt::Vector3f pos;
            alt::Vector2f scale;

            if(!args.Get("pos", pos)) return nullptr;
            if(!args.Get("scale", scale)) return nullptr;

            alt::IBlip* blip = alt::ICore::Instance().CreateBlip(nullptr, blipType, pos);
            blip->SetScaleXY(scale);
            return blip;
        }
        case alt::IBlip::BlipType::RADIUS:
        {
            alt::Vector3f pos;
            float radius;

            if(!args.Get("pos", pos)) return nullptr;
            if(!args.Get("radius", radius)) return nullptr;

            alt::IBlip* blip = alt::ICore::Instance().CreateBlip(nullptr, blipType, pos);
            blip->SetScaleXY({ radius, radius });
            return blip;
        }
        case alt::IBlip::BlipType::DESTINATION:
        {
            if(args.Has("pos"))
            {
                alt::Vector3f pos;
                if(!args.Get("pos", pos)) return nullptr;
                return alt::ICore::Instance().CreateBlip(nullptr, blipType, pos);
            }
            else if(args.Has("entity"))
            {
                alt::IEntity* entity;
                if(!args.Get("entity", entity)) return nullptr;
                return alt::ICore::Instance().CreateBlip(nullptr, blipType, entity);
            }
            else break;
        }
    }

    js::Throw("Invalid Blip type");
    return nullptr;
});
