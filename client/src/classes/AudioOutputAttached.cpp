#include "Class.h"

// clang-format
extern js::Class audioOutputClass;
extern js::Class audioOutputAttachedClass("AudioOutputAttached", &audioOutputClass, nullptr, [](js::ClassTemplate& tpl)
{
    tpl.BindToType(alt::IBaseObject::Type::AUDIO_OUTPUT_ATTACHED);

    tpl.Property<&alt::IAudioAttachedOutput::GetEntity, &alt::IAudioAttachedOutput::SetEntity>("entity");
});
