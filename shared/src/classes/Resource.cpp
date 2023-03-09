#include "Class.h"
#include "interfaces/IResource.h"

extern js::Class resourceClass;

void Current(js::LazyPropertyContext& ctx)
{
    alt::IResource* resource = ctx.GetResource()->GetResource();
    if(!resource)
    {
        ctx.Return(nullptr);
        return;
    }
    v8::Local<v8::Object> resourceObj = resourceClass.Create(ctx.GetContext(), resource);
    ctx.Return(resourceObj);
}

void Get(js::FunctionContext& ctx)
{
    if(!ctx.CheckArgCount(1)) return;
    std::string resourceName;
    if(!ctx.GetArg(0, resourceName)) return;
    alt::IResource* resource = alt::ICore::Instance().GetResource(resourceName);
    if(!resource)
    {
        ctx.Return(nullptr);
        return;
    }
    v8::Local<v8::Object> resourceObj = resourceClass.Create(ctx.GetContext(), resource);
    ctx.Return(resourceObj);
}

void Exists(js::FunctionContext& ctx)
{
    if(!ctx.CheckArgCount(1)) return;
    std::string resourceName;
    if(!ctx.GetArg(0, resourceName)) return;
    alt::IResource* resource = alt::ICore::Instance().GetResource(resourceName);
    ctx.Return(resource != nullptr);
}

void PathGetter(js::PropertyContext& ctx)
{
    alt::IResource* resource = ctx.GetExtraInternalFieldValue<alt::IResource>();
    if(!ctx.Check(resource != nullptr, "Invalid resource")) return;
    ctx.Return(resource->GetPath());
}

void NameGetter(js::PropertyContext& ctx)
{
    alt::IResource* resource = ctx.GetExtraInternalFieldValue<alt::IResource>();
    if(!ctx.Check(resource != nullptr, "Invalid resource")) return;
    ctx.Return(resource->GetName());
}

void MainGetter(js::PropertyContext& ctx)
{
    alt::IResource* resource = ctx.GetExtraInternalFieldValue<alt::IResource>();
    if(!ctx.Check(resource != nullptr, "Invalid resource")) return;
    ctx.Return(resource->GetMain());
}

// clang-format off
extern js::Class resourceClass("Resource", nullptr, [](js::ClassTemplate& tpl)
{
    tpl.StaticLazyProperty("current", Current);
    tpl.StaticFunction("get", Get);
    tpl.StaticFunction("exists", Exists);

    tpl.Property("path", PathGetter);
    tpl.Property("name", NameGetter);
    tpl.Property("main", MainGetter);
}, true);
