#include "Module.h"
#include "Namespace.h"

static void NetTimeGetter(js::PropertyContext& ctx)
{
    ctx.Return(alt::ICore::Instance().GetNetTime());
}

static void SyncedMetaGetter(js::DynamicPropertyContext<v8::Value>& ctx)
{
    ctx.Return(alt::ICore::Instance().GetSyncedMetaData(ctx.GetProperty()));
}

static void SyncedMetaSetter(js::DynamicPropertyContext<v8::Value>& ctx)
{
    alt::MValue value;
    if(!ctx.GetValue(value)) return;
    alt::ICore::Instance().SetSyncedMetaData(ctx.GetProperty(), value);
}

static void SyncedMetaDeleter(js::DynamicPropertyContext<v8::Boolean>& ctx)
{
    if(!alt::ICore::Instance().HasSyncedMetaData(ctx.GetProperty()))
    {
        ctx.Return(false);
        return;
    }

    alt::ICore::Instance().DeleteSyncedMetaData(ctx.GetProperty());
    ctx.Return(true);
}

static void SyncedMetaEnumerator(js::DynamicPropertyContext<v8::Array>& ctx)
{
    ctx.Return(alt::ICore::Instance().GetSyncedMetaDataKeys());
}

static void GetServerConfig(js::LazyPropertyContext& ctx)
{
    Config::Value::ValuePtr config = alt::ICore::Instance().GetServerConfig();
    v8::Local<v8::Value> configVal = js::ConfigValueToJS(config);
    if(!ctx.Check(!configVal.IsEmpty(), "Failed to convert config")) return;
    ctx.Return(configVal);
}

static void SetServerPassword(js::FunctionContext& ctx)
{
    if(!ctx.CheckArgCount(1)) return;

    std::string password;
    if(!ctx.GetArg(0, password)) return;

    alt::ICore::Instance().SetPassword(password);
}

static void HashServerPassword(js::FunctionContext& ctx)
{
    if(!ctx.CheckArgCount(1)) return;

    std::string password;
    if(!ctx.GetArg(0, password)) return;

    ctx.Return(alt::ICore::Instance().HashServerPassword(password));
}

static void StopServer(js::FunctionContext& ctx)
{
    alt::ICore::Instance().StopServer();
}

static void ToggleWorldProfiler(js::FunctionContext& ctx)
{
    if(!ctx.CheckArgCount(1)) return;

    bool state;
    if(!ctx.GetArg(0, state)) return;

    alt::ICore::Instance().SetWorldProfiler(state);
}

static void GetEntitiesInDimension(js::FunctionContext& ctx)
{
    if(!ctx.CheckArgCount(2)) return;

    uint32_t dimension;
    if(!ctx.GetArg(0, dimension)) return;

    uint64_t entityTypes;
    if(!ctx.GetArg(1, entityTypes)) return;

    std::vector<alt::IBaseObject*> entities = alt::ICore::Instance().GetEntitiesInDimension(dimension, entityTypes);
    ctx.Return(entities);
}

static void GetEntitiesInRange(js::FunctionContext& ctx)
{
    if(!ctx.CheckArgCount(4)) return;

    alt::Vector3f pos;
    if(!ctx.GetArg(0, pos)) return;

    int32_t range;
    if(!ctx.GetArg(1, range)) return;

    uint32_t dimension;
    if(!ctx.GetArg(2, dimension)) return;

    uint64_t entityTypes;
    if(!ctx.GetArg(3, entityTypes)) return;

    std::vector<alt::IBaseObject*> entities = alt::ICore::Instance().GetEntitiesInRange(pos, range, dimension, entityTypes);
    ctx.Return(entities);
}

static void GetClosestEntities(js::FunctionContext& ctx)
{
    if(!ctx.CheckArgCount(5)) return;

    alt::Vector3f pos;
    if(!ctx.GetArg(0, pos)) return;

    int32_t range;
    if(!ctx.GetArg(1, range)) return;

    uint32_t dimension;
    if(!ctx.GetArg(2, dimension)) return;

    uint32_t maxCount;
    if(!ctx.GetArg(3, maxCount)) return;

    uint64_t entityTypes;
    if(!ctx.GetArg(4, entityTypes)) return;

    std::vector<alt::IBaseObject*> entities = alt::ICore::Instance().GetClosestEntities(pos, range, dimension, maxCount, entityTypes);
    ctx.Return(entities);
}

// clang-format off
extern js::Class playerClass, vehicleClass, colShapeClass, checkpointClass, pedClass, networkObjectClass, voiceChannelClass;
extern js::Namespace eventsNamespace, pedModelInfoNamespace, vehicleModelInfoNamespace;
static js::Module altModule("alt", "alt-shared", { &playerClass, &vehicleClass, &colShapeClass, &checkpointClass, &pedClass, &networkObjectClass, &voiceChannelClass }, [](js::ModuleTemplate& module)
{
    module.StaticProperty("isClient", false);
    module.StaticProperty("isServer", true);
    module.StaticProperty("rootDir", alt::ICore::Instance().GetRootDirectory());
    module.StaticProperty("netTime", NetTimeGetter);

    module.StaticDynamicProperty("syncedMeta", SyncedMetaGetter, SyncedMetaSetter, SyncedMetaDeleter, SyncedMetaEnumerator);

    module.StaticLazyProperty("serverConfig", GetServerConfig);

    module.StaticFunction("setServerPassword", SetServerPassword);
    module.StaticFunction("hashServerPasword", HashServerPassword);
    module.StaticFunction("stopServer", StopServer);
    module.StaticFunction("toggleWorldProfiler", ToggleWorldProfiler);
    module.StaticFunction("getEntitiesInDimension", GetEntitiesInDimension);
    module.StaticFunction("getEntitiesInRange", GetEntitiesInRange);
    module.StaticFunction("getClosestEntities", GetClosestEntities);

    module.Namespace(eventsNamespace);
    module.Namespace(pedModelInfoNamespace);
    module.Namespace(vehicleModelInfoNamespace);

    // ColShapes namespaces
    module.Namespace("ColshapeSphere");
    module.Namespace("ColshapeCylinder");
    module.Namespace("ColshapeCircle");
    module.Namespace("ColshapeCuboid");
    module.Namespace("ColshapeRectangle");
    module.Namespace("ColshapePolygon");
});
