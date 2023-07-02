#include "Event.h"

// clang-format off
static js::Event gameEntityCreateEvent(alt::CEvent::Type::GAME_ENTITY_CREATE, [](const alt::CEvent* ev, js::Event::EventArgs& args)
{
    auto e = static_cast<const alt::CGameEntityCreateEvent*>(ev);
    args.Set("entity", e->GetTarget());
});

static js::Event gameEntityDestroyEvent(alt::CEvent::Type::GAME_ENTITY_DESTROY, [](const alt::CEvent* ev, js::Event::EventArgs& args)
{
    auto e = static_cast<const alt::CGameEntityDestroyEvent*>(ev);
    args.Set("entity", e->GetTarget());
});

static js::Event taskChangeEvent(alt::CEvent::Type::TASK_CHANGE, [](const alt::CEvent* ev, js::Event::EventArgs& args)
{
    auto e = static_cast<const alt::CTaskChangeEvent*>(ev);
    args.Set("oldTask", e->GetOldTask());
    args.Set("newTask", e->GetNewTask());
});
