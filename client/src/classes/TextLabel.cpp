#include "Class.h"

// clang-format off
extern js::Class worldObjectClass;
extern js::Class textLabelClass("TextLabel", &worldObjectClass, nullptr, [](js::ClassTemplate& tpl)
{
    tpl.BindToType(alt::IBaseObject::Type::TEXT_LABEL);

    tpl.Property<&alt::ITextLabel::IsStreamedIn>("streamedIn");

    tpl.Property<&alt::ITextLabel::IsGlobal>("global");
    tpl.Property<&alt::ITextLabel::GetTarget>("target");
    tpl.Property<&alt::ITextLabel::IsVisible, &alt::ITextLabel::SetVisible>("visible");
    tpl.Property<&alt::ITextLabel::GetColor, &alt::ITextLabel::SetColor>("color");
    tpl.Property<&alt::ITextLabel::GetScale, &alt::ITextLabel::SetScale>("scale");
    tpl.Property<&alt::ITextLabel::GetRotation, &alt::ITextLabel::SetRotation>("rot");
    tpl.Property<&alt::ITextLabel::IsFacingCamera, &alt::ITextLabel::SetFaceCamera>("faceCamera");

    tpl.Property<&alt::ITextLabel::GetOutlineColor, &alt::ITextLabel::SetOutlineColor>("outlineColor");
    tpl.Property<&alt::ITextLabel::GetOutlineWidth, &alt::ITextLabel::SetOutlineWidth>("outlineWidth");
    tpl.Property<&alt::ITextLabel::GetFontSize, &alt::ITextLabel::SetFontSize>("fontSize");
    tpl.Property<&alt::ITextLabel::GetAlign, &alt::ITextLabel::SetAlign>("textAlign");

    tpl.Property<&alt::ITextLabel::GetText, &alt::ITextLabel::SetText>("text");
    tpl.Property<&alt::ITextLabel::GetFont, &alt::ITextLabel::SetFont>("font");

    tpl.Property<&alt::ITextLabel::GetStreamingDistance>("streamingDistance");

    tpl.GetByID<alt::IBaseObject::Type::TEXT_LABEL>();
    // tpl.GetByRemoteID<alt::IBaseObject::Type::TEXT_LABEL>();
});
