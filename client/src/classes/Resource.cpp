#include "Class.h"
#include "interfaces/IAltResource.h"

static void Current(js::PropertyContext& ctx)
{
    js::IAltResource* resource = ctx.GetResource<js::IAltResource>();
    if(!resource || !resource->GetResource())
    {
        ctx.Return(nullptr);
        return;
    }
    v8::Local<v8::Object> resourceObj = resource->CreateResourceObject(resource->GetResource());
    ctx.Return(resourceObj);
}

static void All(js::PropertyContext& ctx)
{
    js::IAltResource* resource = ctx.GetResource<js::IAltResource>();

    std::vector<alt::IResource*> resources = alt::ICore::Instance().GetAllResources();
    js::Array arr(resources.size());
    for(auto res : resources) arr.Push(resource->CreateResourceObject(res));
    ctx.Return(arr);
}

// clang-format off
extern js::Class sharedResourceClass;
extern js::Class resourceClass("Resource", &sharedResourceClass, nullptr, [](js::ClassTemplate& tpl)
{
    tpl.StaticProperty("current", Current);
    tpl.StaticProperty("all", All);
}, true);
