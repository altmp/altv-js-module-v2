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

static void GetClassList(js::FunctionContext& ctx)
{
    if(!ctx.CheckThis()) return;
    alt::IRmlElement* element = ctx.GetThisObject<alt::IRmlElement>();

    const std::vector<std::string> list = element->GetClassList();
    size_t size = list.size();
    js::Array arr(size);
    for(size_t i = 0; i < size; i++)
    {
        arr.Set(i, list[i]);
    }

    ctx.Return(arr);
}

static void GetPseudoClassList(js::FunctionContext& ctx)
{
    if(!ctx.CheckThis()) return;
    alt::IRmlElement* element = ctx.GetThisObject<alt::IRmlElement>();

    const std::vector<std::string> list = element->GetPseudoClassList();
    size_t size = list.size();
    js::Array arr(size);
    for(size_t i = 0; i < size; i++)
    {
        arr.Set(i, list[i]);
    }

    ctx.Return(arr);
}

static void GetAttributes(js::FunctionContext& ctx)
{
    if(!ctx.CheckThis()) return;
    alt::IRmlElement* element = ctx.GetThisObject<alt::IRmlElement>();

    js::Object attributes;
    for(auto attr : element->GetAttributes())
    {
        attributes.Set(attr.first.c_str(), attr.second);
    }

    ctx.Return(attributes);
}

static void GetElementsByTagName(js::FunctionContext& ctx)
{
    if(!ctx.CheckThis()) return;
    if(!ctx.CheckArgCount(1)) return;
    alt::IRmlElement* element = ctx.GetThisObject<alt::IRmlElement>();

    std::string tag;
    if(!ctx.GetArg(0, tag)) return;

    const std::vector<alt::IRmlElement*> elements = element->GetElementsByTagName(tag);
    size_t size = elements.size();
    js::Array arr(size);
    for(size_t i = 0; i < size; i++)
    {
        arr.Set(i, elements[i]);
    }

    ctx.Return(arr);
}

static void GetElementsByClassName(js::FunctionContext& ctx)
{
    if(!ctx.CheckThis()) return;
    if(!ctx.CheckArgCount(1)) return;
    alt::IRmlElement* element = ctx.GetThisObject<alt::IRmlElement>();

    std::string className;
    if(!ctx.GetArg(0, className)) return;

    const std::vector<alt::IRmlElement*> elements = element->GetElementsByClassName(className);
    size_t size = elements.size();
    js::Array arr(size);
    for(size_t i = 0; i < size; i++)
    {
        arr.Set(i, elements[i]);
    }

    ctx.Return(arr);
}

static void QuerySelectorAll(js::FunctionContext& ctx)
{
    if(!ctx.CheckThis()) return;
    if(!ctx.CheckArgCount(1)) return;
    alt::IRmlElement* element = ctx.GetThisObject<alt::IRmlElement>();

    std::string selector;
    if(!ctx.GetArg(0, selector)) return;

    const std::vector<alt::IRmlElement*> elements = element->QuerySelectorAll(selector);
    size_t size = elements.size();
    js::Array arr(size);
    for(size_t i = 0; i < size; i++)
    {
        arr.Set(i, elements[i]);
    }

    ctx.Return(arr);
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
    tpl.Property<&alt::IRmlElement::HasChildren>("hasChildren");
    tpl.Property("childNodes", ChildrenGetter);
    tpl.Property<&alt::IRmlElement::GetOwnerDocument>("ownerDocument");

    tpl.DynamicProperty("style", StyleGetter, StyleSetter, StyleDeleter, nullptr);

    tpl.Method<&alt::IRmlElement::AddClass>("addClass");
    tpl.Method<&alt::IRmlElement::RemoveClass>("removeClass");
    tpl.Method<&alt::IRmlElement::HasClass>("hasClass");
    tpl.Method("getClassList", GetClassList);
    tpl.Method<&alt::IRmlElement::AddPseudoClass>("addPseudoClass");
    tpl.Method<&alt::IRmlElement::RemovePseudoClass>("removePseudoClass");
    tpl.Method<&alt::IRmlElement::HasPseudoClass>("hasPseudoClass");
    tpl.Method("getPseudoClassList", GetPseudoClassList);
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
    tpl.Method("getAttributes", GetAttributes);
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
    tpl.Method("getElementsByTagName", GetElementsByTagName);
    tpl.Method("getElementsByClassName", GetElementsByClassName);
    tpl.Method<&alt::IRmlElement::QuerySelector>("querySelector");
    tpl.Method("querySelectorAll", QuerySelectorAll);

    tpl.GetByID<alt::IBaseObject::Type::RML_ELEMENT>();
});
