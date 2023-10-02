#include "Class.h"
#include "interfaces/IAltResource.h"

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

static void ConfigGetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldValue()) return;

    alt::IResource* resource = ctx.GetExtraInternalFieldValue<alt::IResource>();
    v8::Local<v8::Value> config = js::ConfigValueToJS(resource->GetConfig());
    if(!ctx.Check(!config.IsEmpty(), "Failed to convert config")) return;
    ctx.Return(config);
}

static void RequiredPermissionsGetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldValue()) return;
    alt::IResource* resource = ctx.GetExtraInternalFieldValue<alt::IResource>();

    js::Array arr;
    for (auto& perm : resource->GetRequiredPermissions())
        arr.Push(alt::GetStringFromPermission(perm));

    ctx.Return(arr);
}

static void OptionalPermissionsGetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldValue()) return;
    alt::IResource* resource = ctx.GetExtraInternalFieldValue<alt::IResource>();

    js::Array arr;
    for (auto& perm : resource->GetOptionalPermissions())
        arr.Push(alt::GetStringFromPermission(perm));

    ctx.Return(arr);
}

static void Get(js::FunctionContext& ctx)
{
    if(!ctx.CheckArgCount(1)) return;
    js::IAltResource* resource = ctx.GetResource<js::IAltResource>();

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

// clang-format off
extern js::Class sharedResourceClass("SharedResource", [](js::ClassTemplate& tpl)
{
    tpl.Property("type", TypeGetter);
    tpl.Property("path", PathGetter);
    tpl.Property("name", NameGetter);
    tpl.Property("main", MainGetter);
    tpl.Property("exports", ExportsGetter);
    tpl.Property("dependencies", DependenciesGetter);
    tpl.Property("dependants", DependantsGetter);
    tpl.Property("isStarted", IsStartedGetter);
    tpl.Property("config", ConfigGetter);

    tpl.Property("requiredPermissions", RequiredPermissionsGetter);
    tpl.Property("optionalPermissions", OptionalPermissionsGetter);

    tpl.StaticFunction("get", Get);
    tpl.StaticFunction("exists", Exists);
}, true);
