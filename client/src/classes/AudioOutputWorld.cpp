#include "Class.h"

// clang-format off
extern js::Class audioOutputClass;
extern js::Class audioOutputWorldClass("AudioOutputWorld", &audioOutputClass, nullptr, [](js::ClassTemplate& tpl)
{
    tpl.BindToType(alt::IBaseObject::Type::AUDIO_OUTPUT_WORLD);

    tpl.Property<&alt::IAudioWorldOutput::GetPosition, &alt::IAudioWorldOutput::SetPosition>("pos");
});
