#include "Class.h"
#include "interfaces/IResource.h"

static void ChildrenGetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckThis()) return;
    alt::IRmlElement* element = ctx.GetThisObject<alt::IRmlElement>();

    size_t size = element->GetChildCount();
    js::Array arr(size);
    for(size_t i = 0; i < size; i++)
    {
        const auto children = element->GetChild(i);
        // TODO(xLuxy): alt:V currently doesn't create BaseObject for RmlElements
        ctx.GetResource()->GetOrCreateScriptObject(ctx.GetContext(), children);

        arr.Set(i, children);
    }

    ctx.Return(arr);
}

static void StyleGetter(js::DynamicPropertyGetterContext& ctx)
{
    if(!ctx.CheckParent()) return;
    alt::IRmlElement* obj = ctx.GetParent<alt::IRmlElement>();

    ctx.Return(obj->GetProperty(ctx.GetProperty()));
}

static void StyleSetter(js::DynamicPropertySetterContext& ctx)
{
    if(!ctx.CheckParent()) return;
    alt::IRmlElement* obj = ctx.GetParent<alt::IRmlElement>();

    std::string value;
    if(!ctx.GetValue(value)) return;

    obj->SetProperty(ctx.GetProperty(), value);
}

static void StyleDeleter(js::DynamicPropertyDeleterContext& ctx)
{
    if(!ctx.CheckParent()) return;
    alt::IRmlElement* obj = ctx.GetParent<alt::IRmlElement>();

    if(!obj->HasProperty(ctx.GetProperty()))
    {
        ctx.Return(false);
        return;
    }

    obj->RemoveProperty(ctx.GetProperty());
    ctx.Return(true);
}

// clang-format off
extern js::Class baseObjectClass;
extern js::Class rmlElementClass("RmlElement", &baseObjectClass, nullptr, [](js::ClassTemplate& tpl)
{
    tpl.BindToType(alt::IBaseObject::Type::RML_ELEMENT);

    tpl.Property<&alt::IRmlElement::GetRelativeOffset>("relativeOffset");
    tpl.Property<&alt::IRmlElement::GetAbsoluteOffset>("absoluteOffset");
    tpl.Property<&alt::IRmlElement::GetBaseline>("baseline");
    tpl.Property<&alt::IRmlElement::GetZIndex>("zIndex");
    tpl.Property<&alt::IRmlElement::GetContainingBlock>("containingBlock");
    tpl.Property<&alt::IRmlElement::GetFocusedElement>("focusedElement");
    tpl.Property<&alt::IRmlElement::GetTagName>("tagName");
    tpl.Property<&alt::IRmlElement::GetRmlID, &alt::IRmlElement::SetRmlID>("rmlID");
    tpl.Property<&alt::IRmlElement::IsOwned>("isOwned");
    tpl.Property<&alt::IRmlElement::GetAbsoluteLeft>("absoluteLeft");
    tpl.Property<&alt::IRmlElement::GetAbsoluteTop>("absoluteTop");
    tpl.Property<&alt::IRmlElement::GetClientLeft>("clientLeft");
    tpl.Property<&alt::IRmlElement::GetClientTop>("clientTop");
    tpl.Property<&alt::IRmlElement::GetClientWidth>("clientWidth");
    tpl.Property<&alt::IRmlElement::GetClientHeight>("clientHeight");
    tpl.Property<&alt::IRmlElement::GetOffsetLeft>("offsetLeft");
    tpl.Property<&alt::IRmlElement::GetOffsetTop>("offsetTop");
    tpl.Property<&alt::IRmlElement::GetOffsetWidth>("offsetWidth");
    tpl.Property<&alt::IRmlElement::GetOffsetHeight>("offsetHeight");
    tpl.Property<&alt::IRmlElement::GetScrollLeft, &alt::IRmlElement::SetScrollLeft>("scrollLeft");
    tpl.Property<&alt::IRmlElement::GetScrollTop, &alt::IRmlElement::SetScrollTop>("scrollTop");
    tpl.Property<&alt::IRmlElement::GetScrollWidth>("scrollWidth");
    tpl.Property<&alt::IRmlElement::GetScrollHeight>("scrollHeight");
    tpl.Property<&alt::IRmlElement::IsVisible>("isVisible");
    tpl.Property<&alt::IRmlElement::GetParent>("parent");
    tpl.Property<&alt::IRmlElement::GetNextSibling>("nextSibling");
    tpl.Property<&alt::IRmlElement::GetPreviousSibling>("previousSibling");
    tpl.Property<&alt::IRmlElement::GetFirstChild>("firstChild");
    tpl.Property<&alt::IRmlElement::GetLastChild>("lastChild");
    tpl.Property<&alt::IRmlElement::GetChildCount>("childCount");
    tpl.Property<&alt::IRmlElement::GetInnerRML, &alt::IRmlElement::SetInnerRML>("innerRML");
    tpl.Property<&alt::IRmlElement::HasChildren>("hasChildren");
    tpl.Property("childNodes", ChildrenGetter);
    tpl.Property<&alt::IRmlElement::GetOwnerDocument>("ownerDocument");
    tpl.Property<&alt::IRmlElement::GetAttributes>("attributes");
    tpl.Property<&alt::IRmlElement::GetClassList>("classList");
    tpl.Property<&alt::IRmlElement::GetPseudoClassList>("pseudoClassList");

    tpl.DynamicProperty("style", StyleGetter, StyleSetter, StyleDeleter, nullptr);

    tpl.Method<&alt::IRmlElement::AddClass>("addClass");
    tpl.Method<&alt::IRmlElement::RemoveClass>("removeClass");
    tpl.Method<&alt::IRmlElement::HasClass>("hasClass");
    tpl.Method<&alt::IRmlElement::AddPseudoClass>("addPseudoClass");
    tpl.Method<&alt::IRmlElement::RemovePseudoClass>("removePseudoClass");
    tpl.Method<&alt::IRmlElement::HasPseudoClass>("hasPseudoClass");
    tpl.Method<&alt::IRmlElement::SetOffset>("setOffset");
    tpl.Method<&alt::IRmlElement::IsPointWithinElement>("isPointWithinElement");
    tpl.Method<&alt::IRmlElement::SetProperty>("setProperty");
    tpl.Method<&alt::IRmlElement::RemoveProperty>("removeProperty");
    tpl.Method<&alt::IRmlElement::HasProperty>("hasProperty");
    tpl.Method<&alt::IRmlElement::HasLocalProperty>("hasLocalProperty");
    tpl.Method<&alt::IRmlElement::GetProperty>("getProperty");
    tpl.Method<&alt::IRmlElement::GetLocalProperty>("getLocalProperty");
    tpl.Method<&alt::IRmlElement::GetPropertyAbsoluteValue>("getPropertyAbsoluteValue");
    tpl.Method<&alt::IRmlElement::SetAttribute>("setAttribute");
    tpl.Method<&alt::IRmlElement::RemoveAttribute>("removeAttribute");
    tpl.Method<&alt::IRmlElement::HasAttribute>("hasAttribute");
    tpl.Method<&alt::IRmlElement::GetAttribute>("getAttribute");
    tpl.Method<&alt::IRmlElement::GetClosest>("getClosest");
    tpl.Method<&alt::IRmlElement::GetChild>("getChild");
    tpl.Method<&alt::IRmlElement::AppendChild>("appendChild");
    tpl.Method<&alt::IRmlElement::InsertBefore>("insertBefore");
    tpl.Method<&alt::IRmlElement::ReplaceChild>("replaceChild");
    tpl.Method<&alt::IRmlElement::RemoveChild>("removeChild");
    tpl.Method<&alt::IRmlElement::Focus>("focus");
    tpl.Method<&alt::IRmlElement::Blur>("blur");
    tpl.Method<&alt::IRmlElement::Click>("click");
    tpl.Method<&alt::IRmlElement::ScrollIntoView>("scrollIntoView");
    tpl.Method<&alt::IRmlElement::GetElementByID>("getElementByID");
    tpl.Method<&alt::IRmlElement::GetElementsByTagName>("getElementsByTagName");
    tpl.Method<&alt::IRmlElement::GetElementsByClassName>("getElementsByClassName");
    tpl.Method<&alt::IRmlElement::QuerySelector>("querySelector");
    tpl.Method<&alt::IRmlElement::QuerySelectorAll>("querySelectorAll");

    tpl.GetByID<alt::IBaseObject::Type::RML_ELEMENT>();
});
