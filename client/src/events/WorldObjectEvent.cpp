#include "Event.h"

// clang-format off
static js::Event worldObjectPositionChangeEvent(alt::CEvent::Type::WORLD_OBJECT_POSITION_CHANGE, [](const alt::CEvent* ev, js::Event::EventArgs& args)
{
    auto e = static_cast<const alt::CWorldObjectPositionChangeEvent*>(ev);
    args.Set("object", e->GetWorldObject());
    args.Set("oldPos", e->GetOldPosition());
});

static js::Event worldObjectStreamInEvent(alt::CEvent::Type::WORLD_OBJECT_STREAM_IN, [](const alt::CEvent* ev, js::Event::EventArgs& args)
{
    auto e = static_cast<const alt::CWorldObjectStreamInEvent*>(ev);
    args.Set("object", e->GetWorldObject());
});

static js::Event worldObjectStreamOutEvent(alt::CEvent::Type::WORLD_OBJECT_STREAM_OUT, [](const alt::CEvent* ev, js::Event::EventArgs& args)
{
    auto e = static_cast<const alt::CWorldObjectStreamOutEvent*>(ev);
    args.Set("object", e->GetWorldObject());
});
