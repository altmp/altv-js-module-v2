#include "Class.h"
#include "cpp-sdk/ICore.h"

static void GetSyncInfo(js::FunctionContext& ctx)
{
    if(!ctx.CheckThis()) return;
    if(!ctx.CheckArgCount(1)) return;
    alt::IEntity* entity = ctx.GetThisObject<alt::IEntity>();

    const auto syncInfo = entity->GetSyncInfo();

    js::Object obj;
    obj.Set("active", syncInfo.active);
    obj.Set("receivedTick", syncInfo.receivedTick);
    obj.Set("fullyReceivedTick", syncInfo.fullyReceivedTick);
    obj.Set("sendTick", syncInfo.sendTick);
    obj.Set("ackedSendTick", syncInfo.ackedSendTick);
    obj.Set("propertyCount", syncInfo.propertyCount);
    obj.Set("componentCount", syncInfo.componentCount);

    js::Array componentPropertyIndex(syncInfo.componentCount);
    uint32_t lastPropertyIdx = 0;
    for(uint32_t i = 0; i < syncInfo.componentCount; i++)
    {
        const uint32_t endIdx = i == syncInfo.componentCount - 1 ? syncInfo.propertyCount : syncInfo.componentPropertyIndex[i];

        js::Array propertiesUpdateTick(static_cast<int>(endIdx - lastPropertyIdx));
        for (uint32_t j = lastPropertyIdx; j < endIdx; j++)
        {
            propertiesUpdateTick.Set(j - lastPropertyIdx, syncInfo.propertiesUpdateTick[j]);
        }

        componentPropertyIndex.Set(i, propertiesUpdateTick);
        lastPropertyIdx = endIdx;
    }

    obj.Set("propertyUpdateTicks", componentPropertyIndex);
    ctx.Return(obj);
}

static void GetByScriptID(js::FunctionContext& ctx)
{
    if(!ctx.CheckArgCount(1)) return;

    uint32_t scriptId;
    if(!ctx.GetArg(0, scriptId)) return;

    if (auto obj = alt::ICore::Instance().GetWorldObjectByScriptID(scriptId))
        return ctx.Return(obj);

    ctx.Return(nullptr);
}

// clang-format off
extern js::Class sharedEntityClass;
extern js::Class entityClass("Entity", &sharedEntityClass, nullptr, [](js::ClassTemplate& tpl)
{
    tpl.Property<&alt::IEntity::GetScriptID>("scriptID");

    tpl.Method("getSyncInfo", GetSyncInfo);

    tpl.StaticFunction("getByScriptID", &GetByScriptID);
});
