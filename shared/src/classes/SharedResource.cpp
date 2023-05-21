#include "Class.h"
#include "interfaces/IResource.h"

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
    std::vector<std::string> dependants;
    for(auto& dependant : resource->GetDependants())
    {
        dependants.push_back(dependant);
    }
    ctx.Return(dependants);
}

static void IsStartedGetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldValue()) return;

    alt::IResource* resource = ctx.GetExtraInternalFieldValue<alt::IResource>();
    ctx.Return(resource->IsStarted());
}

// clang-format off
extern js::Class sharedResourceClass("SharedResource", nullptr, [](js::ClassTemplate& tpl)
{
    tpl.Property("type", TypeGetter);
    tpl.Property("path", PathGetter);
    tpl.Property("name", NameGetter);
    tpl.Property("main", MainGetter);
    tpl.Property("exports", ExportsGetter);
    tpl.Property("dependencies", DependenciesGetter);
    tpl.Property("dependants", DependantsGetter);
    tpl.Property("isStarted", IsStartedGetter);
}, true);
