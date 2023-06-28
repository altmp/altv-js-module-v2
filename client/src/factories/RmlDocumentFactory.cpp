#include "FactoryHandler.h"
#include "interfaces/IResource.h"

// clang-format off
static js::FactoryHandler rmlDocumentFactory(alt::IBaseObject::Type::RML_DOCUMENT, [](js::Object& args) -> alt::IBaseObject* {
    std::string url;
    if(!args.Get("url", url)) return nullptr;

    js::IResource* resource = args.GetResource();
    js::SourceLocation origin = js::SourceLocation::GetCurrent(resource);

    return alt::ICore::Instance().CreateDocument(url, origin.file, resource->GetResource());
});
