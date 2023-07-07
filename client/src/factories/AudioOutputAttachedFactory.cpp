#include "FactoryHandler.h"
#include "interfaces/IResource.h"

// clang-format off
static js::FactoryHandler audioOutputAttachedFactory(alt::IBaseObject::Type::AUDIO_OUTPUT_ATTACHED, [](js::Object& args) -> alt::IBaseObject* {
    alt::IWorldObject* entity;
    if(!args.Get("entity", entity)) return nullptr;

    uint32_t categoryHash = args.Get<uint32_t>("categoryHash", alt::ICore::Instance().Hash("radio"));

    return alt::ICore::Instance().CreateAttachedOutput(categoryHash, entity, args.GetResource()->GetResource());
});
