#include "Event.h"

// clang-format off
static js::Event clientScriptEvent(alt::CEvent::Type::CLIENT_SCRIPT_EVENT, [](const alt::CEvent* ev, js::Event::EventArgs& args)
{
    auto e = static_cast<const alt::CClientScriptEvent*>(ev);
    args.Set("eventName", e->GetName());

    const alt::MValueArgs& eventArgs = e->GetArgs();
    js::Array argsArray(eventArgs.GetSize());
    js::MValueArgsToJS(eventArgs, argsArray);
    args.Set("args", argsArray);
});

static js::Event serverScriptEvent(alt::CEvent::Type::SERVER_SCRIPT_EVENT, [](const alt::CEvent* ev, js::Event::EventArgs& args)
{
    auto e = static_cast<const alt::CServerScriptEvent*>(ev);
    args.Set("eventName", e->GetName());

    const alt::MValueArgs& eventArgs = e->GetArgs();
    js::Array argsArray(eventArgs.GetSize());
    js::MValueArgsToJS(eventArgs, argsArray);
    args.Set("args", argsArray);
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
