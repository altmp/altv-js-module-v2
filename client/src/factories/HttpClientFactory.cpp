#include "FactoryHandler.h"
#include "interfaces/IResource.h"

// clang-format off
static js::FactoryHandler httpClientFactory(alt::IBaseObject::Type::HTTP_CLIENT, [](js::Object& args) -> alt::IBaseObject* {
    alt::IResource* resource = args.GetResource()->GetResource();

    return alt::ICore::Instance().CreateHttpClient(resource);
});
