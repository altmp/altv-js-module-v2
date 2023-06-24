#include "Class.h"

static void FocusedGetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckThis()) return;
    alt::IWebView* view = ctx.GetThisObject<alt::IWebView>();

    ctx.Return(view->IsFocused());
}

static void FocusedSetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckThis()) return;
    alt::IWebView* view = ctx.GetThisObject<alt::IWebView>();

    bool value;
    if(!ctx.GetValue(value)) return;

    if(value) view->Focus();
    else
        view->Unfocus();
}

static void Emit(js::FunctionContext& ctx)
{
    if(!ctx.CheckThis()) return;
    if(!ctx.CheckArgCount(1, 32)) return;
    alt::IWebView* view = ctx.GetThisObject<alt::IWebView>();

    std::string eventName;
    if(!ctx.GetArg(0, eventName)) return;

    alt::MValueArgs args;
    args.reserve(ctx.GetArgCount() - 1);
    for(uint32_t i = 1; i < ctx.GetArgCount(); ++i)
    {
        alt::MValue val;
        if(!ctx.GetArg(i, val)) return;
        args.push_back(val);
    }

    view->Trigger(eventName, args);
}

// clang-format off
extern js::Class baseObjectClass;
extern js::Class webViewClass("WebView", &baseObjectClass, [](js::ClassTemplate& tpl) {
    tpl.BindToType(alt::IBaseObject::Type::WEBVIEW);

    tpl.Property("focused", FocusedGetter, FocusedSetter);
    tpl.Property<&alt::IWebView::GetUrl, &alt::IWebView::SetUrl>("url");
    tpl.Property<&alt::IWebView::IsVisible, &alt::IWebView::SetVisible>("visible");
    tpl.Property<&alt::IWebView::IsOverlay>("isOverlay");
    tpl.Property<&alt::IWebView::IsLoaded>("isLoaded");
    tpl.Property<&alt::IWebView::IsReady>("isReady");
    tpl.Property<&alt::IWebView::GetSize, &alt::IWebView::SetSize>("size");
    tpl.Property<&alt::IWebView::GetPosition, &alt::IWebView::SetPosition>("position");

    tpl.Method("emit", Emit);
    tpl.Method<&alt::IWebView::SetExtraHeader>("setExtraHeader");
    tpl.Method<&alt::IWebView::SetZoomLevel>("setZoomLevel");
    tpl.Method<&alt::IWebView::Reload>("reload");
});
