#include "Class.h"

static void ResetNetOwner(js::FunctionContext& ctx)
{
    if(!ctx.CheckThis()) return;
    if(!ctx.CheckArgCount(1)) return;

    bool disableMigration;
    if(!ctx.GetArg(0, disableMigration)) return;

    alt::IEntity* entity = ctx.GetThisObject<alt::IEntity>();
    entity->SetNetworkOwner(nullptr, disableMigration);
}

static void AttachTo(js::FunctionContext& ctx)
{
    if(!ctx.CheckThis()) return;
    if(!ctx.CheckArgCount(7)) return;
    alt::IEntity* entity = ctx.GetThisObject<alt::IEntity>();

    alt::IEntity* target;
    if(!ctx.GetArg(0, target)) return;

    if(!ctx.CheckArgType(1, { js::Type::NUMBER, js::Type::STRING })) return;

    if(ctx.GetArgType(1) == js::Type::NUMBER)
    {
        uint16_t otherBoneId;
        if(!ctx.GetArg(1, otherBoneId)) return;

        uint16_t myBoneId;
        if(!ctx.GetArg(2, myBoneId)) return;

        alt::Position pos;
        if(!ctx.GetArg(3, pos)) return;

        alt::Rotation rot;
        if(!ctx.GetArg(4, rot)) return;

        bool collision;
        if(!ctx.GetArg(5, collision)) return;

        bool noFixedRot;
        if(!ctx.GetArg(6, noFixedRot)) return;

        entity->AttachToEntity(target, otherBoneId, myBoneId, pos, rot, collision, noFixedRot);
    }
    else
    {
        std::string otherBoneName;
        if(!ctx.GetArg(1, otherBoneName)) return;

        std::string myBoneName;
        if(!ctx.GetArg(2, myBoneName)) return;

        alt::Position pos;
        if(!ctx.GetArg(3, pos)) return;

        alt::Rotation rot;
        if(!ctx.GetArg(4, rot)) return;

        bool collision;
        if(!ctx.GetArg(5, collision)) return;

        bool noFixedRot;
        if(!ctx.GetArg(6, noFixedRot)) return;

        entity->AttachToEntity(target, otherBoneName, myBoneName, pos, rot, collision, noFixedRot);
    }
}

static void SyncedMetaSetter(js::DynamicPropertySetterContext& ctx)
{
    if(!ctx.CheckParent()) return;
    alt::IEntity* obj = ctx.GetParent<alt::IEntity>();
    alt::MValue value;

    if(!ctx.GetValue(value)) return;
    obj->SetSyncedMetaData(ctx.GetProperty(), value);
}

static void SyncedMetaDeleter(js::DynamicPropertyDeleterContext& ctx)
{
    if(!ctx.CheckParent()) return;
    alt::IEntity* obj = ctx.GetParent<alt::IEntity>();
    if(!obj->HasSyncedMetaData(ctx.GetProperty()))
    {
        ctx.Return(false);
        return;
    }

    obj->DeleteSyncedMetaData(ctx.GetProperty());
    ctx.Return(true);
}

static void StreamSyncedMetaSetter(js::DynamicPropertySetterContext& ctx)
{
    if(!ctx.CheckParent()) return;
    alt::IEntity* obj = ctx.GetParent<alt::IEntity>();
    alt::MValue value;

    if(!ctx.GetValue(value)) return;
    obj->SetStreamSyncedMetaData(ctx.GetProperty(), value);
}

static void StreamSyncedMetaDeleter(js::DynamicPropertyDeleterContext& ctx)
{
    if(!ctx.CheckParent()) return;
    alt::IEntity* obj = ctx.GetParent<alt::IEntity>();
    if(!obj->HasStreamSyncedMetaData(ctx.GetProperty()))
    {
        ctx.Return(false);
        return;
    }

    obj->DeleteStreamSyncedMetaData(ctx.GetProperty());
    ctx.Return(true);
}

static void SetMultipleSyncedMetaData(js::FunctionContext& ctx)
{
    if (!ctx.CheckThis()) return;
    if (!ctx.CheckArgCount(1)) return;

    alt::IEntity* entity = ctx.GetThisObject<alt::IEntity>();
    if(!entity) return;

    js::Object dict;
    if(!ctx.GetArg(0, dict)) return;

    std::unordered_map<std::string, alt::MValue> values;
    for (auto key : dict.GetKeys())
    {
        alt::MValue val;
        if(!dict.Get(key, val)) continue;
        values[key] = val;
    }

    entity->SetMultipleSyncedMetaData(values);
}

static void SetMultipleStreamSyncedMetaData(js::FunctionContext& ctx)
{
    if (!ctx.CheckThis()) return;
    if (!ctx.CheckArgCount(1)) return;

    alt::IEntity* entity = ctx.GetThisObject<alt::IEntity>();

    js::Object dict;
    if(!ctx.GetArg(0, dict)) return;

    std::unordered_map<std::string, alt::MValue> values;
    for (auto key : dict.GetKeys())
    {
        alt::MValue val;
        if(!dict.Get(key, val)) continue;
        values[key] = val;
    }

    entity->SetMultipleStreamSyncedMetaData(values);
}

// clang-format off
extern js::Class sharedEntityClass;
extern js::Class entityClass("Entity", &sharedEntityClass, nullptr, [](js::ClassTemplate& tpl)
{
    tpl.Method<&alt::IEntity::SetNetworkOwner>("setNetOwner");
    tpl.Method("resetNetOwner", ResetNetOwner);

    tpl.Method("attachTo", &AttachTo);
    tpl.Method<&alt::IEntity::Detach>("detach");

    tpl.Property<&alt::IEntity::GetVisible, &alt::IEntity::SetVisible>("visible");
    tpl.Property<&alt::IEntity::GetStreamed, &alt::IEntity::SetStreamed>("streamed");
    tpl.Property<&alt::IEntity::HasCollision, &alt::IEntity::SetCollision>("collision");
    tpl.Property<&alt::IEntity::GetStreamingDistance, &alt::IEntity::SetStreamingDistance>("streamingDistance");
    tpl.Property<&alt::IEntity::GetTimestamp>("timestamp");

    tpl.DynamicProperty("syncedMeta", nullptr, SyncedMetaSetter, SyncedMetaDeleter, nullptr);
    tpl.DynamicProperty("streamSyncedMeta", nullptr, StreamSyncedMetaSetter, StreamSyncedMetaDeleter, nullptr);

    tpl.Method("setMultipleSyncedMetaData", SetMultipleSyncedMetaData);
    tpl.Method("setMultipleStreamSyncedMetaData", SetMultipleStreamSyncedMetaData);
});
