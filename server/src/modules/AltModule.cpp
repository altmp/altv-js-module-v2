#include "Module.h"
#include "Namespace.h"

static void GetNetTime(js::FunctionContext& ctx)
{
    ctx.Return(alt::ICore::Instance().GetNetTime());
}

static void SyncedMetaGetter(js::DynamicPropertyGetterContext& ctx)
{
    ctx.Return(alt::ICore::Instance().GetSyncedMetaData(ctx.GetProperty()));
}

static void SyncedMetaSetter(js::DynamicPropertySetterContext& ctx)
{
    alt::MValue value;
    if(!ctx.GetValue(value)) return;
    alt::ICore::Instance().SetSyncedMetaData(ctx.GetProperty(), value);
}

static void SyncedMetaDeleter(js::DynamicPropertyDeleterContext& ctx)
{
    if(!alt::ICore::Instance().HasSyncedMetaData(ctx.GetProperty()))
    {
        ctx.Return(false);
        return;
    }

    alt::ICore::Instance().DeleteSyncedMetaData(ctx.GetProperty());
    ctx.Return(true);
}

static void SyncedMetaEnumerator(js::DynamicPropertyEnumeratorContext& ctx)
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

static void SetVoiceExternalPublic(js::FunctionContext& ctx)
{
    if(!ctx.CheckArgCount(2)) return;

    std::string ip;
    if(!ctx.GetArg(0, ip)) return;

    uint16_t port;
    if(!ctx.GetArg(1, port)) return;

    alt::ICore::Instance().SetVoiceExternalPublic(ip, port);
}

static void SetVoiceExternal(js::FunctionContext& ctx)
{
    if(!ctx.CheckArgCount(2)) return;

    std::string ip;
    if(!ctx.GetArg(0, ip)) return;

    uint16_t port;
    if(!ctx.GetArg(1, port)) return;

    alt::ICore::Instance().SetVoiceExternal(ip, port);
}

static void GetMaxStreamingPeds(js::FunctionContext& ctx)
{
    ctx.Return(alt::ICore::Instance().GetMaxStreamingPeds());
}

static void GetMaxStreamingObjects(js::FunctionContext& ctx)
{
    ctx.Return(alt::ICore::Instance().GetMaxStreamingObjects());
}

static void GetMaxStreamingVehicles(js::FunctionContext& ctx)
{
    ctx.Return(alt::ICore::Instance().GetMaxStreamingVehicles());
}

static void SetMaxStreamingPeds(js::FunctionContext& ctx)
{
    if(!ctx.CheckArgCount(1)) return;

    uint16_t limit;
    if(!ctx.GetArg(0, limit)) return;

    alt::ICore::Instance().SetMaxStreamingPeds(limit);
}

static void SetMaxStreamingObjects(js::FunctionContext& ctx)
{
    if(!ctx.CheckArgCount(1)) return;

    uint16_t limit;
    if(!ctx.GetArg(0, limit)) return;

    alt::ICore::Instance().SetMaxStreamingObjects(limit);
}

static void SetMaxStreamingVehicles(js::FunctionContext& ctx)
{
    if(!ctx.CheckArgCount(1)) return;

    uint16_t limit;
    if(!ctx.GetArg(0, limit)) return;

    alt::ICore::Instance().SetMaxStreamingVehicles(limit);
}

static void GetStreamerThreadCount(js::FunctionContext& ctx)
{
    ctx.Return(alt::ICore::Instance().GetStreamerThreadCount());
}

static void SetStreamerThreadCount(js::FunctionContext& ctx)
{
    if(!ctx.CheckArgCount(1)) return;

    uint8_t count;
    if(!ctx.GetArg(0, count)) return;

    alt::ICore::Instance().SetStreamerThreadCount(count);
}

static void GetMigrationThreadCount(js::FunctionContext& ctx)
{
    ctx.Return(alt::ICore::Instance().GetMigrationThreadCount());
}

static void GetSyncSendThreadCount(js::FunctionContext& ctx)
{
    ctx.Return(alt::ICore::Instance().GetSyncSendThreadCount());
}

static void GetSyncReceiveThreadCount(js::FunctionContext& ctx)
{
    ctx.Return(alt::ICore::Instance().GetSyncReceiveThreadCount());
}

static void SetMigrationThreadCount(js::FunctionContext& ctx)
{
    if(!ctx.CheckArgCount(1)) return;

    uint8_t count;
    if(!ctx.GetArg(0, count)) return;

    alt::ICore::Instance().SetMigrationThreadCount(count);
}

static void SetSyncSendThreadCount(js::FunctionContext& ctx)
{
    if(!ctx.CheckArgCount(1)) return;

    uint8_t count;
    if(!ctx.GetArg(0, count)) return;

    alt::ICore::Instance().SetSyncSendThreadCount(count);
}

static void SetSyncReceiveThreadCount(js::FunctionContext& ctx)
{
    if(!ctx.CheckArgCount(1)) return;

    uint8_t count;
    if(!ctx.GetArg(0, count)) return;

    alt::ICore::Instance().SetSyncReceiveThreadCount(count);
}

static void GetStreamingTickRate(js::FunctionContext& ctx)
{
    ctx.Return(alt::ICore::Instance().GetStreamingTickRate());
}

static void GetMigrationTickRate(js::FunctionContext& ctx)
{
    ctx.Return(alt::ICore::Instance().GetMigrationTickRate());
}

static void GetColShapeTickRate(js::FunctionContext& ctx)
{
    ctx.Return(alt::ICore::Instance().GetColShapeTickRate());
}

static void SetStreamingTickRate(js::FunctionContext& ctx)
{
    if (!ctx.CheckArgCount(1)) return;

    uint32_t tickRate;
    if (!ctx.GetArg(0, tickRate)) return;

    alt::ICore::Instance().SetStreamingTickRate(tickRate);
}

static void SetMigrationTickRate(js::FunctionContext& ctx)
{
    if(!ctx.CheckArgCount(1)) return;

    uint32_t tickRate;
    if(!ctx.GetArg(0, tickRate)) return;

    alt::ICore::Instance().SetMigrationTickRate(tickRate);
}

static void SetColShapeTickRate(js::FunctionContext& ctx)
{
    if(!ctx.CheckArgCount(1)) return;

    uint32_t tickRate;
    if(!ctx.GetArg(0, tickRate)) return;

    alt::ICore::Instance().SetColShapeTickRate(tickRate);
}

static void GetStreamingDistance(js::FunctionContext& ctx)
{
    ctx.Return(alt::ICore::Instance().GetStreamingDistance());
}

static void GetMigrationDistance(js::FunctionContext& ctx)
{
    ctx.Return(alt::ICore::Instance().GetMigrationDistance());
}

static void SetMigrationDistance(js::FunctionContext& ctx)
{
    if(!ctx.CheckArgCount(1)) return;

    uint32_t distance;
    if(!ctx.GetArg(0, distance)) return;

    alt::ICore::Instance().SetMigrationDistance(distance);
}

static void SetStreamingDistance(js::FunctionContext& ctx)
{
    if (!ctx.CheckArgCount(1)) return;

    uint32_t distance;
    if (!ctx.GetArg(0, distance)) return;

    alt::ICore::Instance().SetStreamingDistance(distance);
}

// clang-format off
extern js::Class playerClass, vehicleClass, checkpointClass, pedClass, objectClass, voiceChannelClass, blipClass, virtualEntityClass, virtualEntityGroupClass, metricClass;
extern js::Namespace eventsNamespace, pedModelInfoNamespace, vehicleModelInfoNamespace, weaponModelInfoNamespace;
static js::Module altModule("@altv/server", "@altv/shared", { &playerClass, &vehicleClass, &checkpointClass, &pedClass, &objectClass, &voiceChannelClass, &blipClass, &virtualEntityClass, &virtualEntityGroupClass, &metricClass }, [](js::ModuleTemplate& module)
{
    module.StaticProperty("isClient", false);
    module.StaticProperty("isServer", true);
    module.StaticProperty("rootDir", alt::ICore::Instance().GetRootDirectory());
    module.StaticProperty("defaultDimension", alt::DEFAULT_DIMENSION);
    module.StaticProperty("globalDimension", alt::GLOBAL_DIMENSION);

    module.StaticDynamicProperty("syncedMeta", SyncedMetaGetter, SyncedMetaSetter, SyncedMetaDeleter, SyncedMetaEnumerator);

    module.StaticLazyProperty("serverConfig", GetServerConfig);

    module.StaticFunction("getNetTime", GetNetTime);
    module.StaticFunction("setServerPassword", SetServerPassword);
    module.StaticFunction("hashServerPassword", HashServerPassword);
    module.StaticFunction("stopServer", StopServer);
    module.StaticFunction("toggleWorldProfiler", ToggleWorldProfiler);
    module.StaticFunction("getEntitiesInDimension", GetEntitiesInDimension);
    module.StaticFunction("getEntitiesInRange", GetEntitiesInRange);
    module.StaticFunction("getClosestEntities", GetClosestEntities);
    module.StaticFunction("setVoiceExternalPublic", SetVoiceExternalPublic);
    module.StaticFunction("setVoiceExternal", SetVoiceExternal);

    module.StaticFunction("getMaxStreamingPeds", GetMaxStreamingPeds);
    module.StaticFunction("getMaxStreamingObjects", GetMaxStreamingObjects);
    module.StaticFunction("getMaxStreamingVehicles", GetMaxStreamingVehicles);
    module.StaticFunction("setMaxStreamingPeds", SetMaxStreamingPeds);
    module.StaticFunction("setMaxStreamingObjects", SetMaxStreamingObjects);
    module.StaticFunction("setMaxStreamingVehicles", SetMaxStreamingVehicles);
    module.StaticFunction("getStreamerThreadCount", GetStreamerThreadCount);
    module.StaticFunction("setStreamerThreadCount", SetStreamerThreadCount);

    module.StaticFunction("getMigrationThreadCount", GetMigrationThreadCount);
    module.StaticFunction("getSyncSendThreadCount", GetSyncSendThreadCount);
    module.StaticFunction("getSyncReceiveThreadCount", GetSyncReceiveThreadCount);
    module.StaticFunction("setMigrationThreadCount", SetMigrationThreadCount);
    module.StaticFunction("setSyncSendThreadCount", SetSyncSendThreadCount);
    module.StaticFunction("setSyncReceiveThreadCount", SetSyncReceiveThreadCount);
    module.StaticFunction("getStreamingTickRate", GetStreamingTickRate);
    module.StaticFunction("getMigrationTickRate", GetMigrationTickRate);
    module.StaticFunction("getColShapeTickRate", GetColShapeTickRate);
    module.StaticFunction("setStreamingTickRate", SetStreamingTickRate);
    module.StaticFunction("setMigrationTickRate", SetMigrationTickRate);
    module.StaticFunction("setColShapeTickRate", SetColShapeTickRate);
    module.StaticFunction("getStreamingDistance", GetStreamingDistance);
    module.StaticFunction("getMigrationDistance", GetMigrationDistance);
    module.StaticFunction("setStreamingDistance", SetStreamingDistance);
    module.StaticFunction("setMigrationDistance", SetMigrationDistance);

    module.Namespace(eventsNamespace);
    module.Namespace(pedModelInfoNamespace);
    module.Namespace(vehicleModelInfoNamespace);
    module.Namespace(weaponModelInfoNamespace);
});
