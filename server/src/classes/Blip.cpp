#include "Class.h"
#include "interfaces/IResource.h"
#include "cpp-sdk/ICore.h"

// clang-format off
extern js::Class sharedBlipClass;
extern js::Class blipClass("Blip", &sharedBlipClass, nullptr, [](js::ClassTemplate& tpl)
{
    tpl.BindToType(alt::IBaseObject::Type::BLIP);

    tpl.Property<&alt::IBlip::IsGlobal, &alt::IBlip::SetGlobal>("global");
    tpl.Property<&alt::IBlip::GetTargets>("targets");

    tpl.Method<&alt::IBlip::AddTargetPlayer>("addTarget");
    tpl.Method<&alt::IBlip::RemoveTargetPlayer>("removeTarget");

    tpl.Property<&alt::IBlip::AttachedTo, &alt::IBlip::AttachTo>("attachedTo");

    tpl.GetByID<alt::IBaseObject::Type::BLIP>();
});
