#include "Module.h"
#include "interfaces/IResource.h"

static js::Module compatibilityModule("alt", [](js::IResource* resource) -> v8::Local<v8::Object> { return resource->GetCompatibilityModuleNamespace(); });
