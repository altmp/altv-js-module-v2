#include "Class.h"

static void ChildrenGetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckThis()) return;
    alt::IRmlElement* element = ctx.GetThisObject<alt::IRmlElement>();

    size_t size = element->GetChildCount();
    js::Array arr(size);
    for(size_t i = 0; i < size; i++)
    {
        arr.Set(i, element->GetChild(i));
    }

    ctx.Return(arr);
}

static void StyleGetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckThis()) return;
    alt::IRmlElement* element = ctx.GetThisObject<alt::IRmlElement>();

    // TODO
}

static void On(js::FunctionContext& ctx)
{
    if(!ctx.CheckThis()) return;
    if(!ctx.CheckArgCount(2)) return;
    alt::IRmlElement* element = ctx.GetThisObject<alt::IRmlElement>();

    std::string evName;
    if(!ctx.GetArg(0, evName)) return;

    js::FunctionCallback fun;
    if(!ctx.GetArg(1, fun)) return;

    // TODO
}

static void Off(js::FunctionContext& ctx)
{
    if(!ctx.CheckThis()) return;
    if(!ctx.CheckArgCount(2)) return;
    alt::IRmlElement* element = ctx.GetThisObject<alt::IRmlElement>();

    std::string evName;
    if(!ctx.GetArg(0, evName)) return;

    js::FunctionCallback fun;
    if(!ctx.GetArg(1, fun)) return;

    // TODO
}

static void GetEventListeners(js::FunctionContext& ctx)
{
    if(!ctx.CheckThis()) return;
    if(!ctx.CheckArgCount(1)) return;
    alt::IRmlElement* element = ctx.GetThisObject<alt::IRmlElement>();

    std::string evName;
    if(!ctx.GetArg(0, evName)) return;

    // TODO
}

static void AppendChild(js::FunctionContext& ctx)
{
    if(!ctx.CheckThis()) return;
    if(!ctx.CheckArgCount(1)) return;
    alt::IRmlElement* element = ctx.GetThisObject<alt::IRmlElement>();

    // TODO
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
    tpl.Property<&alt::IRmlElement::GetRmlID, &alt::IRmlElement::SetRmlID>("rmlId");
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
    tpl.Property<&alt::IRmlElement::HasChildren>("hasChildren");
    tpl.Property<&alt::IRmlElement::GetInnerRML, &alt::IRmlElement::SetInnerRML>("innerRML");
    tpl.Property<&alt::IRmlElement::HasChildren>("ownerDocument");
    tpl.Property("childNodes", ChildrenGetter);
    tpl.Property("style", StyleGetter);

    tpl.Method("on", On);
    tpl.Method("off", Off);
    tpl.Method("getEventListeners", GetEventListeners);
    tpl.Method("appendChild", AppendChild);
    /*tpl.Method("insertBefore", InsertBefore);
    tpl.Method("replaceChild", ReplaceChild);
    tpl.Method("removeChild", RemoveChild);
    tpl.Method("addClass", AddClass);
    tpl.Method("removeClass", RemoveClass);
    tpl.Method("hasClass", HasClass);
    tpl.Method("getClassList", GetClassList);
    tpl.Method("addPseudoClass", AddPseudoClass);
    tpl.Method("removePseudoClass", RemovePseudoClass);
    tpl.Method("hasPseudoClass", HasPseudoClass);
    tpl.Method("getPseudoClassList", GetPseudoClassList);
    tpl.Method("setOffset", SetOffset);
    tpl.Method("isPointWithinElement", IsPointWithinElement);
    tpl.Method("setProperty", SetProperty);
    tpl.Method("removeProperty", RemoveProperty);
    tpl.Method("hasProperty", HasProperty);
    tpl.Method("hasLocalProperty", HasLocalProperty);
    tpl.Method("getProperty", GetProperty);
    tpl.Method("getLocalProperty", GetLocalProperty);
    tpl.Method("getPropertyAbsoluteValue", GetPropertyAbsoluteValue);
    tpl.Method("setAttribute", SetAttribute);
    tpl.Method("removeAttribute", RemoveAttribute);
    tpl.Method("hasAttribute", HasAttribute);
    tpl.Method("getAttribute", GetAttribute);
    tpl.Method("getAttributes", GetAttributes);
    tpl.Method("closest", GetClosest);
    tpl.Method("getElementByID", GetElementByID);
    tpl.Method("getElementsByTagName", GetElementsByTagName);
    tpl.Method("getElementsByClassName", GetElementsByClassName);
    tpl.Method("querySelector", QuerySelector);
    tpl.Method("querySelectorAll", QuerySelectorAll);
    tpl.Method("focus", Focus);*/
    tpl.Method<&alt::IRmlElement::Blur>("blur");
    tpl.Method<&alt::IRmlElement::Click>("click");
    //tpl.Method("scrollIntoView", ScrollIntoView);

    tpl.GetByID<alt::IBaseObject::Type::RML_ELEMENT>();
});
