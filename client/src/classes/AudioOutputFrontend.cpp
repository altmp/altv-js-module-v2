#include "Class.h"

// clang-format off
extern js::Class audioOutputClass;
extern js::Class audioOutputFrontendClass("AudioOutputFrontend", &audioOutputClass, nullptr, [](js::ClassTemplate& tpl)
{
    tpl.BindToType(alt::IBaseObject::Type::AUDIO_OUTPUT_FRONTEND);
});
