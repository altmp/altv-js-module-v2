#include "Namespace.h"
#include "interfaces/IResource.h"

static void GetMaxStreamingPeds(js::DynamicPropertyGetterContext& ctx)
{
    ctx.Return(alt::ICore::Instance().GetMaxStreamingPeds());
}

static void SetMaxStreamingPeds(js::DynamicPropertySetterContext& ctx)
{
    uint16_t limit;
    if (!ctx.GetValue(limit)) return;

    alt::ICore::Instance().SetMaxStreamingPeds(limit);
}

static void GetMaxStreamingObjects(js::DynamicPropertyGetterContext& ctx)
{
    ctx.Return(alt::ICore::Instance().GetMaxStreamingObjects());
}

static void SetMaxStreamingObjects(js::DynamicPropertySetterContext& ctx)
{
    uint16_t limit;
    if(!ctx.GetValue(limit)) return;

    alt::ICore::Instance().SetMaxStreamingObjects(limit);
}

static void GetMaxStreamingVehicles(js::DynamicPropertyGetterContext& ctx)
{
    ctx.Return(alt::ICore::Instance().GetMaxStreamingVehicles());
}

static void SetMaxStreamingVehicles(js::DynamicPropertySetterContext& ctx)
{
    uint16_t limit;
    if(!ctx.GetValue(limit)) return;

    alt::ICore::Instance().SetMaxStreamingVehicles(limit);
}


static void GetStreamerThreadCount(js::DynamicPropertyGetterContext& ctx)
{
    ctx.Return(alt::ICore::Instance().GetStreamerThreadCount());
}

static void SetStreamerThreadCount(js::DynamicPropertySetterContext& ctx)
{
    uint8_t count;
    if(!ctx.GetValue(count)) return;

    alt::ICore::Instance().SetStreamerThreadCount(count);
}

static void GetStreamingTickRate(js::DynamicPropertyGetterContext& ctx)
{
    ctx.Return(alt::ICore::Instance().GetStreamingTickRate());
}

static void SetStreamingTickRate(js::DynamicPropertySetterContext& ctx)
{
    uint32_t tickRate;
    if (!ctx.GetValue(tickRate)) return;

    alt::ICore::Instance().SetStreamingTickRate(tickRate);
}

static void GetStreamingDistance(js::DynamicPropertyGetterContext& ctx)
{
    ctx.Return(alt::ICore::Instance().GetStreamingDistance());
}

static void SetStreamingDistance(js::DynamicPropertySetterContext& ctx)
{
    uint32_t distance;
    if (!ctx.GetValue(distance)) return;

    alt::ICore::Instance().SetStreamingDistance(distance);
}


static void GetMigrationThreadCount(js::DynamicPropertyGetterContext& ctx)
{
    ctx.Return(alt::ICore::Instance().GetMigrationThreadCount());
}

static void SetMigrationThreadCount(js::DynamicPropertySetterContext& ctx)
{
    uint8_t count;
    if(!ctx.GetValue(count)) return;

    alt::ICore::Instance().SetMigrationThreadCount(count);
}

static void GetMigrationTickRate(js::DynamicPropertyGetterContext& ctx)
{
    ctx.Return(alt::ICore::Instance().GetMigrationTickRate());
}

static void SetMigrationTickRate(js::DynamicPropertySetterContext& ctx)
{
    uint32_t tickRate;
    if(!ctx.GetValue(tickRate)) return;

    alt::ICore::Instance().SetMigrationTickRate(tickRate);
}

static void GetMigrationDistance(js::DynamicPropertyGetterContext& ctx)
{
    ctx.Return(alt::ICore::Instance().GetMigrationDistance());
}

static void SetMigrationDistance(js::DynamicPropertySetterContext& ctx)
{
    uint32_t distance;
    if(!ctx.GetValue(distance)) return;

    alt::ICore::Instance().SetMigrationDistance(distance);
}

static void GetColShapeTickRate(js::DynamicPropertyGetterContext& ctx)
{
    ctx.Return(alt::ICore::Instance().GetColShapeTickRate());
}

static void SetColShapeTickRate(js::DynamicPropertySetterContext& ctx)
{
    uint32_t tickRate;
    if(!ctx.GetValue(tickRate)) return;

    alt::ICore::Instance().SetColShapeTickRate(tickRate);
}


static void GetSyncReceiveThreadCount(js::DynamicPropertyGetterContext& ctx)
{
    ctx.Return(alt::ICore::Instance().GetSyncReceiveThreadCount());
}

static void SetSyncReceiveThreadCount(js::DynamicPropertySetterContext& ctx)
{
    uint8_t count;
    if(!ctx.GetValue(count)) return;

    alt::ICore::Instance().SetSyncReceiveThreadCount(count);
}

static void GetSyncSendThreadCount(js::DynamicPropertyGetterContext& ctx)
{
    ctx.Return(alt::ICore::Instance().GetSyncSendThreadCount());
}

static void SetSyncSendThreadCount(js::DynamicPropertySetterContext& ctx)
{
    uint8_t count;
    if(!ctx.GetValue(count)) return;

    alt::ICore::Instance().SetSyncSendThreadCount(count);
}


// clang-format off
extern js::Namespace streamingNamespace("Streaming", [](js::NamespaceTemplate& tpl) {
    tpl.StaticDynamicProperty("maxStreamingPeds", GetMaxStreamingPeds, SetMaxStreamingPeds);
    tpl.StaticDynamicProperty("maxStreamingObjects", GetMaxStreamingObjects, SetMaxStreamingObjects);
    tpl.StaticDynamicProperty("maxStreamingVehicles", GetMaxStreamingVehicles, SetMaxStreamingVehicles);

    tpl.StaticDynamicProperty("streamerThreadCount", GetStreamerThreadCount, SetStreamerThreadCount);
    tpl.StaticDynamicProperty("streamingTickRate", GetStreamingTickRate, SetStreamingTickRate);
    tpl.StaticDynamicProperty("streamingDistance", GetStreamingDistance, SetStreamingDistance);

    tpl.StaticDynamicProperty("migrationThreadCount", GetMigrationThreadCount, SetMigrationThreadCount);
    tpl.StaticDynamicProperty("migrationTickRate", GetMigrationTickRate, SetMigrationTickRate);
    tpl.StaticDynamicProperty("migrationDistance", GetMigrationDistance, SetMigrationDistance);
    tpl.StaticDynamicProperty("colShapeTickRate", GetColShapeTickRate, SetColShapeTickRate);

    tpl.StaticDynamicProperty("syncReceiveThreadCount", GetSyncReceiveThreadCount, SetSyncReceiveThreadCount);
    tpl.StaticDynamicProperty("syncSendThreadCount", GetSyncSendThreadCount, SetSyncSendThreadCount);
});
