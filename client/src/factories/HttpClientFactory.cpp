#include "FactoryHandler.h"

// clang-format off
static js::FactoryHandler httpClientFactory(alt::IBaseObject::Type::HTTP_CLIENT, [](js::Object& args) -> alt::IBaseObject* {
    return alt::ICore::Instance().CreateHttpClient();
});
