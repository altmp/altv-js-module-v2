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
    if(!ctx.CheckArgCount(1)) return;

    bool disableMigration;
    if(!ctx.GetArg(0, disableMigration)) return;

    alt::IEntity* entity = ctx.GetThisObject<alt::IEntity>();
    entity->SetNetworkOwner(nullptr, disableMigration);
}

static void SyncedMetaSetter(js::DynamicPropertyContext<v8::Value>& ctx)
{
    if(!ctx.CheckParent()) return;
    alt::IEntity* obj = ctx.GetParent<alt::IEntity>();
    alt::MValue value;

    if(!ctx.GetValue(value)) return;
    obj->SetSyncedMetaData(ctx.GetProperty(), value);
}

static void SyncedMetaDeleter(js::DynamicPropertyContext<v8::Boolean>& ctx)
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

static void StreamSyncedMetaSetter(js::DynamicPropertyContext<v8::Value>& ctx)
{
    if(!ctx.CheckParent()) return;
    alt::IEntity* obj = ctx.GetParent<alt::IEntity>();
    alt::MValue value;

    if(!ctx.GetValue(value)) return;
    obj->SetStreamSyncedMetaData(ctx.GetProperty(), value);
}

static void StreamSyncedMetaDeleter(js::DynamicPropertyContext<v8::Boolean>& ctx)
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
    tpl.Method<alt::IEntity, void, alt::IPlayer*, bool, &alt::IEntity::SetNetworkOwner>("setNetOwner");
    tpl.Method("resetNetOwner", ResetNetOwner);

    tpl.Method<alt::IEntity, void, alt::IEntity*, int16_t, int16_t, alt::Position, alt::Rotation, bool, bool, &alt::IEntity::AttachToEntity>("attachTo");
    tpl.Method<alt::IEntity, void, alt::IEntity*, const std::string&, const std::string&, alt::Position, alt::Rotation, bool, bool, &alt::IEntity::AttachToEntity>("attachTo");
    tpl.Method<alt::IEntity, void, &alt::IEntity::Detach>("detach");

    tpl.Property<alt::IEntity, bool, &alt::IEntity::GetVisible, &alt::IEntity::SetVisible>("visible");
    tpl.Property<alt::IEntity, bool, &alt::IEntity::GetStreamed, &alt::IEntity::SetStreamed>("streamed");
    tpl.Property<alt::IEntity, bool, &alt::IEntity::IsFrozen, &alt::IEntity::SetFrozen>("frozen");
    tpl.Property<alt::IEntity, bool, &alt::IEntity::HasCollision, &alt::IEntity::SetCollision>("collision");

    tpl.DynamicProperty("syncedMeta", nullptr, SyncedMetaSetter, SyncedMetaDeleter, nullptr);
    tpl.DynamicProperty("streamSyncedMeta", nullptr, StreamSyncedMetaSetter, StreamSyncedMetaDeleter, nullptr);

    tpl.StaticFunction("getByID", &GetByID);
});
