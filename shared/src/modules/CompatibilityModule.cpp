#include "Module.h"
#include "interfaces/IResource.h"

// clang-format off
static js::Module compatibilityModule("alt", [](js::IResource* resource) -> v8::Local<v8::Object> { return resource->GetCompatibilityModuleNamespace(); }, true);
static js::Module compatibilityModule2("alt-shared", [](js::IResource* resource) -> v8::Local<v8::Object> { return resource->GetCompatibilityModuleNamespace(); }, true);
