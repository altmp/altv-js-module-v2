#include "Class.h"
#include "cpp-sdk/ICore.h"

static void GetByID(js::FunctionContext& ctx)
{
    if(!ctx.CheckArgCount(1)) return;

    uint16_t id;
    if(!ctx.GetArg(0, id)) return;
    ctx.Return((alt::IBaseObject*)alt::ICore::Instance().GetEntityByID(id));
}

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
        int16_t otherBoneIndex;
        if(!ctx.GetArg(1, otherBoneIndex)) return;

        int16_t myBoneIndex;
        if(!ctx.GetArg(2, myBoneIndex)) return;

        alt::Position pos;
        if(!ctx.GetArg(3, pos)) return;

        alt::Rotation rot;
        if(!ctx.GetArg(4, rot)) return;

        bool collision;
        if(!ctx.GetArg(5, collision)) return;

        bool noFixedRot;
        if(!ctx.GetArg(6, noFixedRot)) return;

        entity->AttachToEntity(target, otherBoneIndex, myBoneIndex, pos, rot, collision, noFixedRot);
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
    tpl.Property<&alt::IEntity::IsFrozen, &alt::IEntity::SetFrozen>("frozen");
    tpl.Property<&alt::IEntity::HasCollision, &alt::IEntity::SetCollision>("collision");

    tpl.DynamicProperty("syncedMeta", nullptr, SyncedMetaSetter, SyncedMetaDeleter, nullptr);
    tpl.DynamicProperty("streamSyncedMeta", nullptr, StreamSyncedMetaSetter, StreamSyncedMetaDeleter, nullptr);

    tpl.StaticFunction("getByID", &GetByID);
});
