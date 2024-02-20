#include "Class.h"
#include "interfaces/IResource.h"

static void Show(js::FunctionContext& ctx)
{
    if(!ctx.CheckThis()) return;
    if(!ctx.CheckArgCount(0, 2)) return;
    alt::IRmlDocument* document = ctx.GetThisObject<alt::IRmlDocument>();

    bool isModal = ctx.GetArg<bool>(0, false);

    bool focused = ctx.GetArg<bool>(1, true);

    document->Show(isModal, focused);
}

static void CreateElement(js::FunctionContext& ctx)
{
    if(!ctx.CheckThis()) return;
    if(!ctx.CheckArgCount(1)) return;
    alt::IRmlDocument* document = ctx.GetThisObject<alt::IRmlDocument>();

    std::string tag;
    if(!ctx.GetArg(0, tag)) return;

    alt::IRmlElement* element = document->CreateElement(tag);
    if(!ctx.Check(element != nullptr, "Failed to create element")) return;

    ctx.Return(element);
}

static void CreateTextNode(js::FunctionContext& ctx)
{
    if(!ctx.CheckThis()) return;
    if(!ctx.CheckArgCount(1)) return;
    alt::IRmlDocument* document = ctx.GetThisObject<alt::IRmlDocument>();

    std::string text;
    if(!ctx.GetArg(0, text)) return;

    alt::IRmlElement* node = document->CreateTextNode(text);
    if(!ctx.Check(node != nullptr, "Failed to create text node")) return;

    ctx.Return(node);
}

// clang-format off
extern js::Class rmlElementClass;
extern js::Class rmlDocumentClass("RmlDocument", &rmlElementClass, nullptr, [](js::ClassTemplate& tpl)
{
    tpl.BindToType(alt::IBaseObject::Type::RML_DOCUMENT);

    tpl.Property<&alt::IRmlDocument::GetTitle, &alt::IRmlDocument::SetTitle>("title");
    tpl.Property<&alt::IRmlDocument::GetSourceUrl>("sourceUrl");
    tpl.Property<&alt::IRmlDocument::IsVisible>("visible");
    tpl.Property<&alt::IRmlDocument::IsModal>("modal");
    tpl.Property<&alt::IRmlDocument::GetBody>("body");

    tpl.Method("show", Show);
    tpl.Method<&alt::IRmlDocument::Hide>("hide");
    tpl.Method<&alt::IRmlDocument::Update>("update");
    tpl.Method("createElement", CreateElement);
    tpl.Method("createTextNode", CreateTextNode);

    tpl.GetByID<alt::IBaseObject::Type::RML_DOCUMENT>();
});
