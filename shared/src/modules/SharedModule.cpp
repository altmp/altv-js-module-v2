#include "Module.h"
#include "Namespace.h"
#include "interfaces/IResource.h"
#include "version/version.h"

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
    js::Function inspectFunc(resource->GetBindingExport<v8::Function>(js::BindingExport::LOG_INSPECT));

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

static void GetVoiceConnectionState(js::FunctionContext& ctx)
{
    ctx.Return(alt::ICore::Instance().GetVoiceConnectionState());
}

static void GetNetTime(js::FunctionContext& ctx)
{
    ctx.Return(alt::ICore::Instance().GetNetTime());
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

static void SyncedMetaGetter(js::DynamicPropertyGetterContext& ctx)
{
    ctx.Return(alt::ICore::Instance().GetSyncedMetaData(ctx.GetProperty()));
}

static void SyncedMetaEnumerator(js::DynamicPropertyEnumeratorContext& ctx)
{
    ctx.Return(alt::ICore::Instance().GetSyncedMetaDataKeys());
}

// clang-format off
extern js::Class baseObjectClass, worldObjectClass, entityClass, resourceClass, bufferClass;
// TODO (xLuxy): bind colshape classes except colShapeClass
extern js::Class colShapeClass, colShapeCircleClass, colShapeCuboidClass, colShapeCylinderClass, colShapePolyClass, colShapeRectClass, colShapeSphereClass;
extern js::Namespace enumsNamespace, sharedEventsNamespace, fileNamespace, profilerNamespace, symbolsNamespace;
static js::Module sharedModule("@altv/shared", "", { &baseObjectClass, &worldObjectClass, &entityClass, &colShapeClass, &resourceClass, &bufferClass }, [](js::ModuleTemplate& module)
{
    module.StaticProperty("defaultDimension", alt::DEFAULT_DIMENSION);
    module.StaticProperty("globalDimension", alt::GLOBAL_DIMENSION);

    module.StaticProperty("isDebug", alt::ICore::Instance().IsDebug());
    module.StaticProperty("version", alt::ICore::Instance().GetVersion());
    module.StaticProperty("sdkVersion", ALT_SDK_VERSION);
    module.StaticProperty("branch", alt::ICore::Instance().GetBranch());

    module.StaticFunction("log", Log<LogType::INFO>);
    module.StaticFunction("logWarning", Log<LogType::WARN>);
    module.StaticFunction("logError", Log<LogType::ERR>);
    module.StaticFunction("sha256", &SHA256);
    module.StaticFunction("getVoiceConnectionState", GetVoiceConnectionState);
    module.StaticFunction("getNetTime", GetNetTime);

    module.StaticDynamicProperty("meta", MetaGetter, MetaSetter, MetaDeleter, MetaEnumerator);
    module.StaticDynamicProperty("syncedMeta", SyncedMetaGetter, nullptr, nullptr, SyncedMetaEnumerator);

    module.Namespace("Timers");
    module.Namespace("Utils");
    module.Namespace("Commands");
    module.Namespace("RPC");
    module.Namespace(enumsNamespace);
    module.Namespace(fileNamespace);
    module.Namespace(profilerNamespace);
    module.Namespace(symbolsNamespace);
    // Blip namespaces
    module.Namespace("PointBlip");
    module.Namespace("AreaBlip");
    module.Namespace("RadiusBlip");
    // ColShape namespaces
    module.Namespace("ColShapeSphere");
    module.Namespace("ColShapeCylinder");
    module.Namespace("ColShapeCircle");
    module.Namespace("ColShapeCuboid");
    module.Namespace("ColShapeRectangle");
    module.Namespace("ColShapePolygon");

    module.StaticBindingExport("hash", js::BindingExport::HASH);
    module.StaticBindingExport("Vector3", js::BindingExport::VECTOR3_CLASS);
    module.StaticBindingExport("Vector2", js::BindingExport::VECTOR2_CLASS);
    module.StaticBindingExport("RGBA", js::BindingExport::RGBA_CLASS);
    module.StaticBindingExport("Quaternion", js::BindingExport::QUATERNION_CLASS);
}, [](js::IResource* resource) {
    #ifdef ALT_SERVER_API
    std::string name = "@altv/server";
    #else
    std::string name = "@altv/client";
    #endif
    return js::Module::Get(name).GetNamespace(resource);
}, js::Module::Option::EXPORT_AS_DEFAULT);
