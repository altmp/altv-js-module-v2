#include "Namespace.h"
#include "interfaces/IResource.h"

static void GetMaxStreamingPeds(js::PropertyContext& ctx)
{
    ctx.Return(alt::ICore::Instance().GetMaxStreamingPeds());
}

static void SetMaxStreamingPeds(js::PropertyContext& ctx)
{
    uint16_t limit;
    if (!ctx.GetValue(limit)) return;

    alt::ICore::Instance().SetMaxStreamingPeds(limit);
}

static void GetMaxStreamingObjects(js::PropertyContext& ctx)
{
    ctx.Return(alt::ICore::Instance().GetMaxStreamingObjects());
}

static void SetMaxStreamingObjects(js::PropertyContext& ctx)
{
    uint16_t limit;
    if(!ctx.GetValue(limit)) return;

    alt::ICore::Instance().SetMaxStreamingObjects(limit);
}

static void GetMaxStreamingVehicles(js::PropertyContext& ctx)
{
    ctx.Return(alt::ICore::Instance().GetMaxStreamingVehicles());
}

static void SetMaxStreamingVehicles(js::PropertyContext& ctx)
{
    uint16_t limit;
    if(!ctx.GetValue(limit)) return;

    alt::ICore::Instance().SetMaxStreamingVehicles(limit);
}


static void GetStreamerThreadCount(js::PropertyContext& ctx)
{
    ctx.Return(alt::ICore::Instance().GetStreamerThreadCount());
}

static void SetStreamerThreadCount(js::PropertyContext& ctx)
{
    uint8_t count;
    if(!ctx.GetValue(count)) return;

    alt::ICore::Instance().SetStreamerThreadCount(count);
}

static void GetStreamingTickRate(js::PropertyContext& ctx)
{
    ctx.Return(alt::ICore::Instance().GetStreamingTickRate());
}

static void SetStreamingTickRate(js::PropertyContext& ctx)
{
    uint32_t tickRate;
    if (!ctx.GetValue(tickRate)) return;

    alt::ICore::Instance().SetStreamingTickRate(tickRate);
}

static void GetStreamingDistance(js::PropertyContext& ctx)
{
    ctx.Return(alt::ICore::Instance().GetStreamingDistance());
}

static void SetStreamingDistance(js::PropertyContext& ctx)
{
    uint32_t distance;
    if (!ctx.GetValue(distance)) return;

    alt::ICore::Instance().SetStreamingDistance(distance);
}


static void GetMigrationThreadCount(js::PropertyContext& ctx)
{
    ctx.Return(alt::ICore::Instance().GetMigrationThreadCount());
}

static void SetMigrationThreadCount(js::PropertyContext& ctx)
{
    uint8_t count;
    if(!ctx.GetValue(count)) return;

    alt::ICore::Instance().SetMigrationThreadCount(count);
}

static void GetMigrationTickRate(js::PropertyContext& ctx)
{
    ctx.Return(alt::ICore::Instance().GetMigrationTickRate());
}

static void SetMigrationTickRate(js::PropertyContext& ctx)
{
    uint32_t tickRate;
    if(!ctx.GetValue(tickRate)) return;

    alt::ICore::Instance().SetMigrationTickRate(tickRate);
}

static void GetMigrationDistance(js::PropertyContext& ctx)
{
    ctx.Return(alt::ICore::Instance().GetMigrationDistance());
}

static void SetMigrationDistance(js::PropertyContext& ctx)
{
    uint32_t distance;
    if(!ctx.GetValue(distance)) return;

    alt::ICore::Instance().SetMigrationDistance(distance);
}

static void GetColShapeTickRate(js::PropertyContext& ctx)
{
    ctx.Return(alt::ICore::Instance().GetColShapeTickRate());
}

static void SetColShapeTickRate(js::PropertyContext& ctx)
{
    uint32_t tickRate;
    if(!ctx.GetValue(tickRate)) return;

    alt::ICore::Instance().SetColShapeTickRate(tickRate);
}


static void GetSyncReceiveThreadCount(js::PropertyContext& ctx)
{
    ctx.Return(alt::ICore::Instance().GetSyncReceiveThreadCount());
}

static void SetSyncReceiveThreadCount(js::PropertyContext& ctx)
{
    uint8_t count;
    if(!ctx.GetValue(count)) return;

    alt::ICore::Instance().SetSyncReceiveThreadCount(count);
}

static void GetSyncSendThreadCount(js::PropertyContext& ctx)
{
    ctx.Return(alt::ICore::Instance().GetSyncSendThreadCount());
}

static void SetSyncSendThreadCount(js::PropertyContext& ctx)
{
    uint8_t count;
    if(!ctx.GetValue(count)) return;

    alt::ICore::Instance().SetSyncSendThreadCount(count);
}


// clang-format off
extern js::Namespace streamingNamespace("Streaming", [](js::NamespaceTemplate& tpl) {
    tpl.StaticProperty("maxStreamingPeds", GetMaxStreamingPeds, SetMaxStreamingPeds);
    tpl.StaticProperty("maxStreamingObjects", GetMaxStreamingObjects, SetMaxStreamingObjects);
    tpl.StaticProperty("maxStreamingVehicles", GetMaxStreamingVehicles, SetMaxStreamingVehicles);

    tpl.StaticProperty("streamerThreadCount", GetStreamerThreadCount, SetStreamerThreadCount);
    tpl.StaticProperty("streamingTickRate", GetStreamingTickRate, SetStreamingTickRate);
    tpl.StaticProperty("streamingDistance", GetStreamingDistance, SetStreamingDistance);

    tpl.StaticProperty("migrationThreadCount", GetMigrationThreadCount, SetMigrationThreadCount);
    tpl.StaticProperty("migrationTickRate", GetMigrationTickRate, SetMigrationTickRate);
    tpl.StaticProperty("migrationDistance", GetMigrationDistance, SetMigrationDistance);
    tpl.StaticProperty("colShapeTickRate", GetColShapeTickRate, SetColShapeTickRate);

    tpl.StaticProperty("syncReceiveThreadCount", GetSyncReceiveThreadCount, SetSyncReceiveThreadCount);
    tpl.StaticProperty("syncSendThreadCount", GetSyncSendThreadCount, SetSyncSendThreadCount);
});
