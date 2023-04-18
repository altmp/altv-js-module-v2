#include "Event.h"
#include "Class.h"
#include "interfaces/IResource.h"

// clang-format off
static js::Event resourceStartEvent(alt::CEvent::Type::RESOURCE_START, [](const alt::CEvent* ev, js::Event::EventArgs& args) {
    auto e = static_cast<const alt::CResourceStartEvent*>(ev);

    args.Set("resource", args.GetResource()->CreateResourceObject(e->GetResource()));
});

static js::Event resourceStopEvent(alt::CEvent::Type::RESOURCE_STOP, [](const alt::CEvent* ev, js::Event::EventArgs& args) {
    auto e = static_cast<const alt::CResourceStopEvent*>(ev);

    args.Set("resource", args.GetResource()->CreateResourceObject(e->GetResource()));
});

static js::Event resourceErrorEvent(alt::CEvent::Type::RESOURCE_ERROR, [](const alt::CEvent* ev, js::Event::EventArgs& args) {
    auto e = static_cast<const alt::CResourceErrorEvent*>(ev);

    args.Set("resource", args.GetResource()->CreateResourceObject(e->GetResource()));
});
