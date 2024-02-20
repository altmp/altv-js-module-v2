#include "Event.h"
#include "Class.h"
#include "interfaces/IAltResource.h"

// clang-format off
static js::Event anyResourceStartEvent(alt::CEvent::Type::RESOURCE_START, [](const alt::CEvent* ev, js::Event::EventArgs& args) {
    auto e = static_cast<const alt::CResourceStartEvent*>(ev);

    args.Set("resource", args.GetResource()->As<js::IAltResource>()->CreateResourceObject(e->GetResource()));
});

static js::Event anyResourceStopEvent(alt::CEvent::Type::RESOURCE_STOP, [](const alt::CEvent* ev, js::Event::EventArgs& args) {
    auto e = static_cast<const alt::CResourceStopEvent*>(ev);

    args.Set("resource", args.GetResource()->As<js::IAltResource>()->CreateResourceObject(e->GetResource()));
});

static js::Event resourceErrorEvent(alt::CEvent::Type::RESOURCE_ERROR, [](const alt::CEvent* ev, js::Event::EventArgs& args) {
    auto e = static_cast<const alt::CResourceErrorEvent*>(ev);

    args.Set("resource", args.GetResource()->As<js::IAltResource>()->CreateResourceObject(e->GetResource()));
});
