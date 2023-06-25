#include "Namespace.h"
#include "interfaces/IResource.h"

static void Exists(js::FunctionContext& ctx)
{
    if(!ctx.CheckArgCount(1)) return;

    std::string path;
    if(!ctx.GetArg(0, path)) return;

    js::SourceLocation location = js::SourceLocation::GetCurrent(ctx.GetResource());
    alt::IPackage::PathInfo info = alt::ICore::Instance().Resolve(ctx.GetResource()->GetResource(), path, location.file);
    if(!ctx.Check(info.pkg, "Invalid file")) return;
    ctx.Return(alt::ICore::Instance().FileExists(info.prefix + info.fileName));
}

static void Read(js::FunctionContext& ctx)
{
    if(!ctx.CheckArgCount(1)) return;

    std::string path;
    if(!ctx.GetArg(0, path)) return;

    js::SourceLocation location = js::SourceLocation::GetCurrent(ctx.GetResource());
    alt::IPackage::PathInfo info = alt::ICore::Instance().Resolve(ctx.GetResource()->GetResource(), path, location.file);
    if(!ctx.Check(info.pkg, "Invalid file")) return;
    ctx.Return(alt::ICore::Instance().FileRead(info.prefix + info.fileName));
}

// clang-format off
extern js::Namespace fileNamespace("File", [](js::NamespaceTemplate& tpl) {
    tpl.StaticFunction("exists", Exists);
    tpl.StaticFunction("read", Read);
});
