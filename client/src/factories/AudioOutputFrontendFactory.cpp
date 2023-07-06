#include "FactoryHandler.h"
#include "interfaces/IResource.h"

// clang-format off
static js::FactoryHandler audioOutputFrontendFactory(alt::IBaseObject::Type::AUDIO_OUTPUT_FRONTEND, [](js::Object& args) -> alt::IBaseObject* {
    uint32_t categoryHash = args.Get<uint32_t>("categoryHash", alt::ICore::Instance().Hash("radio"));

    return alt::ICore::Instance().CreateFrontendOutput(categoryHash, args.GetResource()->GetResource());
});
