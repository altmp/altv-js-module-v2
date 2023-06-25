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

static void SHA256(js::FunctionContext& ctx)
{
    if(!ctx.CheckArgCount(1)) return;

    std::string str;
    if(!ctx.GetArg(0, str)) return;

    ctx.Return(alt::ICore::Instance().StringToSHA256(str));
}

static void MetaGetter(js::DynamicPropertyGetterContext& ctx)
{
    ctx.Return(alt::ICore::Instance().GetMetaData(ctx.GetProperty()));
}

static void MetaSetter(js::DynamicPropertySetterContext& ctx)
{
    alt::MValue value;
    if(!ctx.GetValue(value)) return;
    alt::ICore::Instance().SetMetaData(ctx.GetProperty(), value);
}

static void MetaDeleter(js::DynamicPropertyDeleterContext& ctx)
{
    if(!alt::ICore::Instance().HasMetaData(ctx.GetProperty()))
    {
        ctx.Return(false);
        return;
    }

    alt::ICore::Instance().DeleteMetaData(ctx.GetProperty());
    ctx.Return(true);
}

static void MetaEnumerator(js::DynamicPropertyEnumeratorContext& ctx)
{
    ctx.Return(alt::ICore::Instance().GetMetaDataKeys());
}

// clang-format off
extern js::Class baseObjectClass, worldObjectClass, entityClass, resourceClass;
extern js::Namespace enumsNamespace, sharedEventsNamespace, fileNamespace;
static js::Module sharedModule("@altv/shared", "", { &baseObjectClass, &worldObjectClass, &entityClass, &resourceClass }, [](js::ModuleTemplate& module)
{
    module.StaticProperty("isDebug", alt::ICore::Instance().IsDebug());
    module.StaticProperty("version", alt::ICore::Instance().GetVersion());
    module.StaticProperty("branch", alt::ICore::Instance().GetBranch());

    module.StaticFunction("log", Log<LogType::INFO>);
    module.StaticFunction("logWarning", Log<LogType::WARN>);
    module.StaticFunction("logError", Log<LogType::ERR>);
    module.StaticFunction("sha256", &SHA256);

    module.StaticDynamicProperty("meta", MetaGetter, MetaSetter, MetaDeleter, MetaEnumerator);

    module.Namespace("Timers");
    module.Namespace("Utils");
    module.Namespace("Factory");
    module.Namespace(enumsNamespace);
    module.Namespace("PointBlip");
    module.Namespace("AreaBlip");
    module.Namespace("RadiusBlip");
    module.Namespace(fileNamespace);

    module.StaticBindingExport("hash", "utils:hash");
    module.StaticBindingExport("Vector3", "classes:vector3");
    module.StaticBindingExport("Vector2", "classes:vector2");
    module.StaticBindingExport("RGBA", "classes:rgba");
    module.StaticBindingExport("Quaternion", "classes:quaternion");
});
