#include "Class.h"
#include "interfaces/IResource.h"

extern js::Class resourceClass;

static void Current(js::LazyPropertyContext& ctx)
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

static void Get(js::FunctionContext& ctx)
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

static void Exists(js::FunctionContext& ctx)
{
    if(!ctx.CheckArgCount(1)) return;
    std::string resourceName;
    if(!ctx.GetArg(0, resourceName)) return;
    alt::IResource* resource = alt::ICore::Instance().GetResource(resourceName);
    ctx.Return(resource != nullptr);
}

static void TypeGetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldValue()) return;

    alt::IResource* resource = ctx.GetExtraInternalFieldValue<alt::IResource>();
    ctx.Return(resource->GetType());
}

static void PathGetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldValue()) return;

    alt::IResource* resource = ctx.GetExtraInternalFieldValue<alt::IResource>();
    ctx.Return(resource->GetPath());
}

static void NameGetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldValue()) return;

    alt::IResource* resource = ctx.GetExtraInternalFieldValue<alt::IResource>();
    ctx.Return(resource->GetName());
}

static void MainGetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldValue()) return;

    alt::IResource* resource = ctx.GetExtraInternalFieldValue<alt::IResource>();
    ctx.Return(resource->GetMain());
}

static void ExportsGetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldValue()) return;

    alt::IResource* resource = ctx.GetExtraInternalFieldValue<alt::IResource>();
    ctx.Return(js::MValueToJS(resource->GetExports()));
}

static void DependenciesGetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldValue()) return;

    alt::IResource* resource = ctx.GetExtraInternalFieldValue<alt::IResource>();
    // todo: change this when its a std::vector instead of alt::Array
    std::vector<std::string> dependencies;
    for(auto& dependency : resource->GetDependencies())
    {
        dependencies.push_back(dependency);
    }
    ctx.Return(dependencies);
}

static void DependantsGetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldValue()) return;

    alt::IResource* resource = ctx.GetExtraInternalFieldValue<alt::IResource>();
    // todo: change this when its a std::vector instead of alt::Array
    std::vector<std::string> dependants;
    for(auto& dependant : resource->GetDependants())
    {
        dependants.push_back(dependant);
    }
    ctx.Return(dependants);
}

// clang-format off
extern js::Class resourceClass("Resource", nullptr, [](js::ClassTemplate& tpl)
{
    tpl.StaticLazyProperty("current", Current);
    tpl.StaticFunction("get", Get);
    tpl.StaticFunction("exists", Exists);

    tpl.Property("type", TypeGetter);
    tpl.Property("path", PathGetter);
    tpl.Property("name", NameGetter);
    tpl.Property("main", MainGetter);
    tpl.Property("exports", ExportsGetter);
    tpl.Property("dependencies", DependenciesGetter);
    tpl.Property("dependants", DependantsGetter);
}, true);
