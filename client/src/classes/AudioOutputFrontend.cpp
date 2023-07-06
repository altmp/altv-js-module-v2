#include "Class.h"

// clang-format off
extern js::Class audioOutputClass;
extern js::Class audioOutputFrontendClass("AudioOutputFrontend", [](js::ClassTemplate& tpl)
{
    tpl.BindToType(alt::IBaseObject::Type::AUDIO_OUTPUT_FRONTEND);
});
