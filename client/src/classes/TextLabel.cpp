#include "Class.h"

static void GetByID(js::FunctionContext& ctx)
{
    if(!ctx.CheckArgCount(1)) return;

    uint32_t id;
    if(!ctx.GetArg(0, id)) return;

    alt::IBaseObject* entity = alt::ICore::Instance().GetBaseObjectByID(alt::IBaseObject::Type::TEXT_LABEL, id);
    ctx.Return(entity);
}

// clang-format off
extern js::Class worldObjectClass;
extern js::Class textLabelClass("TextLabel", &worldObjectClass, nullptr, [](js::ClassTemplate& tpl)
{
    tpl.BindToType(alt::IBaseObject::Type::TEXT_LABEL);

    tpl.Property<&alt::ITextLabel::IsStreamedIn>("isStreamedIn");

    tpl.Property<&alt::ITextLabel::IsGlobal>("isGlobal");
    tpl.Property<&alt::ITextLabel::GetTarget>("target");
    tpl.Property<&alt::ITextLabel::IsVisible, &alt::ITextLabel::SetVisible>("visible");
    tpl.Property<&alt::ITextLabel::GetColor, &alt::ITextLabel::SetColor>("color");
    tpl.Property<&alt::ITextLabel::GetScale, &alt::ITextLabel::SetScale>("scale");
    tpl.Property<&alt::ITextLabel::GetRotation, &alt::ITextLabel::SetRotation>("rot");
    tpl.Property<&alt::ITextLabel::IsFacingCamera, &alt::ITextLabel::SetFaceCamera>("faceCamera");

    tpl.Property<&alt::ITextLabel::GetStreamingDistance>("streamingDistance");

    tpl.StaticFunction("getByID", GetByID);
});
