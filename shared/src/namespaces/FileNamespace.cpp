#include "Namespace.h"
#include "interfaces/IResource.h"

static void Exists(js::FunctionContext& ctx)
{
    if(!ctx.CheckArgCount(1)) return;

    std::string fileName;
    if(!ctx.GetArg(0, fileName)) return;

    js::SourceLocation location = js::SourceLocation::GetCurrent(ctx.GetResource());
    alt::IPackage::PathInfo info = alt::ICore::Instance().Resolve(ctx.GetResource()->GetResource(), fileName, location.file);
    if(!ctx.Check(info.pkg, "Invalid file")) return;
    ctx.Return(alt::ICore::Instance().FileExists(info.prefix + info.fileName));
}

static void Read(js::FunctionContext& ctx)
{
    if(!ctx.CheckArgCount(1, 2)) return;

    std::string fileName;
    if(!ctx.GetArg(0, fileName)) return;

    const auto encoding = ctx.GetArg<std::string>(1, "utf-8");

    js::SourceLocation location = js::SourceLocation::GetCurrent(ctx.GetResource());

#ifdef ALT_CLIENT_API
    auto path = alt::ICore::Instance().Resolve(ctx.GetResource()->GetResource(), fileName, location.file);
    if (!ctx.Check(path.pkg, "invalid asset pack")) return;

    alt::IPackage::File* file = path.pkg->OpenFile(path.fileName);
    if (!ctx.Check(file, "file does not exist")) return;

    std::string data(path.pkg->GetFileSize(file), 0);
    path.pkg->ReadFile(file, data.data(), data.size());
    path.pkg->CloseFile(file);
#else
    std::string data = alt::ICore::Instance().FileRead(fileName);
#endif

    if(encoding == "utf-16")
    {
        ctx.Return(reinterpret_cast<uint16_t*>(data.data()));
    }
    else if(encoding == "binary")
    {
        const v8::Local<v8::ArrayBuffer> buffer = v8::ArrayBuffer::New(ctx.GetIsolate(), data.size());
        const auto contents = buffer->GetBackingStore();

        std::memcpy(contents->Data(), data.data(), data.size());

        ctx.Return(buffer);
    }
    else
    {
        ctx.Return(data);
    }
}

// clang-format off
extern js::Namespace fileNamespace("File", [](js::NamespaceTemplate& tpl) {
    tpl.StaticFunction("exists", Exists);
    tpl.StaticFunction("read", Read);
});
