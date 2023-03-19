#include "Module.h"
#include "Namespace.h"
#include "interfaces/IResource.h"

enum class LogType
{
    INFO,
    WARN,
    ERR,
};

template<LogType Type>
static void Log(js::FunctionContext& ctx)
{
    js::IResource* resource = ctx.GetResource();
    js::Function inspectFunc(resource->GetBindingExport<v8::Function>("logging:inspectMultiple"));

    std::vector<v8::Local<v8::Value>> args;
    args.reserve(ctx.GetArgCount() + 1);

    js::Object options;
    options.Set("colors", Type == LogType::INFO);
    args.push_back(options.Get());
    for(int i = 0; i < ctx.GetArgCount(); i++)
    {
        v8::Local<v8::Value> val;
        if(!ctx.GetArg(i, val)) continue;
        args.push_back(val);
    }

    auto msg = inspectFunc.Call<std::string>(args);
    if(!msg) return;
    if constexpr(Type == LogType::INFO) alt::ICore::Instance().LogColored(msg.value(), resource->GetResource());
    else if constexpr(Type == LogType::WARN)
        alt::ICore::Instance().LogWarning(msg.value(), resource->GetResource());
    else if constexpr(Type == LogType::ERR)
        alt::ICore::Instance().LogError(msg.value(), resource->GetResource());
}

static void Hash(js::FunctionContext& ctx)
{
    if(!ctx.CheckArgCount(1)) return;

    std::string str;
    if(!ctx.GetArg(0, str)) return;

    ctx.Return(alt::ICore::Instance().Hash(str));
}

static void SHA256(js::FunctionContext& ctx)
{
    if(!ctx.CheckArgCount(1)) return;

    std::string str;
    if(!ctx.GetArg(0, str)) return;

    ctx.Return(alt::ICore::Instance().StringToSHA256(str));
}

// clang-format off
extern js::Class baseObjectClass, worldObjectClass, entityClass, resourceClass;
extern js::Namespace enumsNamespace, sharedEventsNamespace;
static js::Module sharedModule("alt-shared", "", { &baseObjectClass, &worldObjectClass, &entityClass, &resourceClass }, [](js::ModuleTemplate& module)
{
    module.StaticFunction("log", Log<LogType::INFO>);
    module.StaticFunction("logWarn", Log<LogType::WARN>);
    module.StaticFunction("logError", Log<LogType::ERR>);
    module.StaticFunction("hash", &Hash);
    module.StaticFunction("sha256", &SHA256);

    module.StaticProperty("isDebug", alt::ICore::Instance().IsDebug());
    // todo: global (synced) meta

    module.Namespace("Timers");
    module.Namespace("Utils");
    module.Namespace("Factory");
    module.Namespace(enumsNamespace);

    module.StaticBindingExport("Vector3", "classes:vector3");
    module.StaticBindingExport("Vector2", "classes:vector2");
    module.StaticBindingExport("RGBA", "classes:rgba");
});
