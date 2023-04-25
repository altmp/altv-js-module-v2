#include "FactoryHandler.h"

// clang-format off
static js::FactoryHandler virtualEntityFactory(alt::IBaseObject::Type::VIRTUAL_ENTITY, [](js::Object& args) -> alt::IBaseObject* {
    alt::IVirtualEntityGroup* group;
    if(!args.Get("group", group)) return nullptr;
    alt::Vector3f pos;
    if(!args.Get("pos", pos)) return nullptr;
    uint32_t streamingRange;
    if(!args.Get("streamingRange", streamingRange)) return nullptr;
    std::unordered_map<std::string, alt::MValue> data;
    js::Object dataObj = args.Get<js::Object>("data");
    for(auto& key : dataObj.GetKeys())
    {
        alt::MValue value = dataObj.Get<alt::MValue>(key);
        if(value.IsEmpty()) continue;
        data.insert({ key, value });
    }
    return alt::ICore::Instance().CreateVirtualEntity(group, pos, streamingRange, data);
});
