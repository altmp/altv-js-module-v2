#include "FactoryHandler.h"

// clang-format off
static js::FactoryHandler virtualEntityFactory(alt::IBaseObject::Type::VIRTUAL_ENTITY, [](js::Object& args) -> alt::IBaseObject* {
    alt::IVirtualEntityGroup* group;
    if(!args.Get("group", group)) return nullptr;

    alt::Vector3f pos;
    if(!args.Get("pos", pos)) return nullptr;

    uint32_t streamingDistance;
    if(!args.Get("streamingDistance", streamingDistance)) return nullptr;

    js::Object dataObj = args.Get<js::Object>("data");

    return alt::ICore::Instance().CreateVirtualEntity(group, pos, streamingDistance, dataObj.ToMap<alt::MValue>());
});
