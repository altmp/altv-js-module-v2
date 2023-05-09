#include "FactoryHandler.h"

// clang-format off
static js::FactoryHandler virtualEntityGroupFactory(alt::IBaseObject::Type::VIRTUAL_ENTITY_GROUP, [](js::Object& args) -> alt::IBaseObject* {
    uint32_t maxStreamedEntityCount;
    if(!args.Get("maxStreamedEntityCount", maxStreamedEntityCount)) return nullptr;
    return alt::ICore::Instance().CreateVirtualEntityGroup(maxStreamedEntityCount);
});
