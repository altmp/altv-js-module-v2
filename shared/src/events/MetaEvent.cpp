#include "Event.h"

// clang-format off
static js::Event metaChangeEvent(alt::CEvent::Type::META_CHANGE, [](const alt::CEvent* ev, js::Event::EventArgs& args)
{
    auto e = static_cast<const alt::CMetaChangeEvent*>(ev);

    args.Set("entity", e->GetTarget());
    args.Set("key", e->GetKey());
    args.Set("oldValue", e->GetOldVal());
    args.Set("newValue", e->GetVal());
});

static js::Event localMetaChangeEvent(alt::CEvent::Type::LOCAL_SYNCED_META_CHANGE, [](const alt::CEvent* ev, js::Event::EventArgs& args)
{
    auto e = static_cast<const alt::CLocalMetaDataChangeEvent*>(ev);

    args.Set("player", e->GetTarget());
    args.Set("key", e->GetKey());
    args.Set("oldValue", e->GetOldVal());
    args.Set("newValue", e->GetVal());
});

static js::Event syncedMetaChangeEvent(alt::CEvent::Type::SYNCED_META_CHANGE, [](const alt::CEvent* ev, js::Event::EventArgs& args)
{
    auto e = static_cast<const alt::CSyncedMetaDataChangeEvent*>(ev);

    args.Set("entity", e->GetTarget());
    args.Set("key", e->GetKey());
    args.Set("oldValue", e->GetOldVal());
    args.Set("newValue", e->GetVal());
});

static js::Event streamSyncedMetaChangeEvent(alt::CEvent::Type::STREAM_SYNCED_META_CHANGE, [](const alt::CEvent* ev, js::Event::EventArgs& args)
{
    auto e = static_cast<const alt::CStreamSyncedMetaDataChangeEvent*>(ev);

    args.Set("entity", e->GetTarget());
    args.Set("key", e->GetKey());
    args.Set("oldValue", e->GetOldVal());
    args.Set("newValue", e->GetVal());
});

static js::Event globalMetaChangeEvent(alt::CEvent::Type::GLOBAL_META_CHANGE, [](const alt::CEvent* ev, js::Event::EventArgs& args)
{
    auto e = static_cast<const alt::CGlobalMetaDataChangeEvent*>(ev);

    args.Set("key", e->GetKey());
    args.Set("oldValue", e->GetOldVal());
    args.Set("newValue", e->GetVal());
});

static js::Event globalSyncedMetaChangeEvent(alt::CEvent::Type::GLOBAL_SYNCED_META_CHANGE, [](const alt::CEvent* ev, js::Event::EventArgs& args)
{
    auto e = static_cast<const alt::CGlobalMetaDataChangeEvent*>(ev);

    args.Set("key", e->GetKey());
    args.Set("oldValue", e->GetOldVal());
    args.Set("newValue", e->GetVal());
});
