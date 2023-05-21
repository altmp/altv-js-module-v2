#include "Class.h"
#include "interfaces/IResource.h"

static void Current(js::PropertyContext& ctx)
{
    js::IResource* resource = ctx.GetResource();
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
    js::IResource* resource = ctx.GetResource();

    std::vector<alt::IResource*> resources = alt::ICore::Instance().GetAllResources();
    js::Array arr(resources.size());
    for(auto res : resources) arr.Push(resource->CreateResourceObject(res));
    ctx.Return(arr);
}

static void Get(js::FunctionContext& ctx)
{
    if(!ctx.CheckArgCount(1)) return;
    js::IResource* resource = ctx.GetResource();

    std::string resourceName;
    if(!ctx.GetArg(0, resourceName)) return;

    alt::IResource* res = alt::ICore::Instance().GetResource(resourceName);
    if(!res)
    {
        ctx.Return(nullptr);
        return;
    }
    v8::Local<v8::Object> resourceObj = resource->CreateResourceObject(res);
    ctx.Return(resourceObj);
}

static void Exists(js::FunctionContext& ctx)
{
    if(!ctx.CheckArgCount(1)) return;

    std::string resourceName;
    if(!ctx.GetArg(0, resourceName)) return;

    alt::IResource* resource = alt::ICore::Instance().GetResource(resourceName);
    ctx.Return(resource != nullptr);
}

static void Start(js::FunctionContext& ctx)
{
    if(!ctx.CheckArgCount(1)) return;

    std::string resourceName;
    if(!ctx.GetArg(0, resourceName)) return;

    alt::ICore::Instance().StartResource(resourceName);
}

static void Stop(js::FunctionContext& ctx)
{
    if(!ctx.CheckArgCount(1)) return;

    std::string resourceName;
    if(!ctx.GetArg(0, resourceName)) return;

    alt::ICore::Instance().StopResource(resourceName);
}

static void Restart(js::FunctionContext& ctx)
{
    if(!ctx.CheckArgCount(1)) return;

    std::string resourceName;
    if(!ctx.GetArg(0, resourceName)) return;

    alt::ICore::Instance().RestartResource(resourceName);
}

// clang-format off
extern js::Class sharedResourceClass;
extern js::Class resourceClass("Resource", &sharedResourceClass, nullptr, [](js::ClassTemplate& tpl)
{
    tpl.StaticProperty("current", Current);
    tpl.StaticProperty("all", All);

    tpl.StaticFunction("get", Get);
    tpl.StaticFunction("exists", Exists);
    tpl.StaticFunction("start", Start);
    tpl.StaticFunction("stop", Stop);
    tpl.StaticFunction("restart", Restart);

    // todo: add missing properties
}, true);
