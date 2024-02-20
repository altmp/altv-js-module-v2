#include "Module.h"
#include "Namespace.h"

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

static void HasBenefit(js::FunctionContext& ctx)
{
    if(!ctx.CheckArgCount(1)) return;

    alt::Benefit benefit;
    if(!ctx.GetArg(0, benefit)) return;

    ctx.Return(alt::ICore::Instance().HasBenefit(benefit));
}

// clang-format off
extern js::Class playerClass, vehicleClass, checkpointClass, pedClass, objectClass, voiceChannelClass, blipClass, virtualEntityClass, virtualEntityGroupClass, markerClass, metricClass, connectionInfoClass;
extern js::Namespace eventsNamespace, pedModelInfoNamespace, vehicleModelInfoNamespace, weaponModelInfoNamespace, streamingNamespace;
static js::Module altModule("@altv/server", "@altv/shared", { &playerClass, &vehicleClass, &checkpointClass, &pedClass, &objectClass, &voiceChannelClass, &blipClass, &virtualEntityClass, &virtualEntityGroupClass, &markerClass, &metricClass, &connectionInfoClass }, [](js::ModuleTemplate& module)
{
    module.StaticProperty("client", false);
    module.StaticProperty("server", true);
    module.StaticProperty("rootDir", alt::ICore::Instance().GetRootDirectory());

    module.StaticDynamicProperty("syncedMeta", SyncedMetaGetter, SyncedMetaSetter, SyncedMetaDeleter, SyncedMetaEnumerator);

    module.StaticLazyProperty("serverConfig", GetServerConfig);

    module.StaticFunction("setServerPassword", SetServerPassword);
    module.StaticFunction("hashServerPassword", HashServerPassword);
    module.StaticFunction("stopServer", StopServer);
    module.StaticFunction("toggleWorldProfiler", ToggleWorldProfiler);
    module.StaticFunction("getEntitiesInDimension", GetEntitiesInDimension);
    module.StaticFunction("getEntitiesInRange", GetEntitiesInRange);
    module.StaticFunction("getClosestEntities", GetClosestEntities);
    module.StaticFunction("setVoiceExternalPublic", SetVoiceExternalPublic);
    module.StaticFunction("setVoiceExternal", SetVoiceExternal);

    module.StaticFunction("hasBenefit", HasBenefit);

    module.Namespace("Security");
    module.Namespace(eventsNamespace);
    module.Namespace(pedModelInfoNamespace);
    module.Namespace(vehicleModelInfoNamespace);
    module.Namespace(weaponModelInfoNamespace);
    module.Namespace(streamingNamespace);
}, nullptr, js::Module::Option::EXPORT_AS_DEFAULT);
