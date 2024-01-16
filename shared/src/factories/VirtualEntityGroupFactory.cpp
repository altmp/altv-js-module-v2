#include "FactoryHandler.h"

// clang-format off
static js::FactoryHandler virtualEntityGroupFactory(alt::IBaseObject::Type::VIRTUAL_ENTITY_GROUP, [](js::Object& args) -> alt::IBaseObject* {
    uint32_t maxEntitiesInStream;
    if(!args.Get("maxEntitiesInStream", maxEntitiesInStream)) return nullptr;

    return alt::ICore::Instance().CreateVirtualEntityGroup(maxEntitiesInStream);
});
