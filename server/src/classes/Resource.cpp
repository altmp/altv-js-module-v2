#include "Class.h"
#include "interfaces/IAltResource.h"

static void ClientTypeGetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldValue()) return;

    alt::IResource* resource = ctx.GetExtraInternalFieldValue<alt::IResource>();
    ctx.Return(resource->GetClientType());
}

static void ClientMainGetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldValue()) return;

    alt::IResource* resource = ctx.GetExtraInternalFieldValue<alt::IResource>();
    ctx.Return(resource->GetClientMain());
}

static void ClientFilesGetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldValue()) return;

    alt::IResource* resource = ctx.GetExtraInternalFieldValue<alt::IResource>();
    ctx.Return(resource->GetClientFiles());
}

static void GetMatchedFiles(js::FunctionContext& ctx)
{
    if(!ctx.CheckArgCount(1, 32)) return;

    std::vector<std::string> patterns;
    patterns.reserve(ctx.GetArgCount());
    for(int i = 0; i < ctx.GetArgCount(); ++i)
    {
        std::string pattern;
        if(!ctx.GetArg(i, pattern)) return;
        patterns.push_back(pattern);
    }

    alt::IResource* resource = ctx.GetExtraInternalFieldValue<alt::IResource>();
    ctx.Return(resource->GetMatchedFiles(patterns));
}

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
    tpl.Property("clientType", ClientTypeGetter);
    tpl.Property("clientMain", ClientMainGetter);
    tpl.Property("clientFiles", ClientFilesGetter);

    tpl.Method("getMatchedFiles", GetMatchedFiles);

    tpl.StaticProperty("current", Current);
    tpl.StaticProperty("all", All);

    tpl.StaticFunction("start", Start);
    tpl.StaticFunction("stop", Stop);
    tpl.StaticFunction("restart", Restart);
}, true);
