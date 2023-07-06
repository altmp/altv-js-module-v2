#include "Class.h"

// clang-format
extern js::Class audioOutputClass;
extern js::Class audioOutputAttachedClass("AudioOutputAttached", [](js::ClassTemplate& tpl)
{
    tpl.BindToType(alt::IBaseObject::Type::AUDIO_OUTPUT_ATTACHED);

    tpl.Property<&alt::IAudioAttachedOutput::GetEntity, &alt::IAudioAttachedOutput::SetEntity>("entity");
});
