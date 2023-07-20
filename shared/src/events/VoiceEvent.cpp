#include "Event.h"
#include "cpp-sdk/SDK.h"

// clang-format off
static js::Event voiceConnectionEvent(alt::CEvent::Type::VOICE_CONNECTION_EVENT, [](const alt::CEvent* ev, js::Event::EventArgs& args)
{
    auto e = static_cast<const alt::CVoiceConnectionEvent*>(ev);

    args.Set("state", e->GetState());
});

