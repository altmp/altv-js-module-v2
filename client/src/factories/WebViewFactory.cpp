#include "FactoryHandler.h"
#include "interfaces/IResource.h"

// clang-format off
static js::FactoryHandler webViewFactory(alt::IBaseObject::Type::WEBVIEW, [](js::Object& args) -> alt::IBaseObject* {
    std::string url;
    if(!args.Get("url", url)) return nullptr;

    if(args.Has("drawable"))
    {
        uint32_t drawable;
        if(!args.GetAsHash("drawable", drawable)) return nullptr;

        std::string targetTexture;
        if(!args.Get("targetTexture", targetTexture)) return nullptr;

        return alt::ICore::Instance().CreateWebView(url, drawable, targetTexture, args.GetResource()->GetResource());
    }
    else
    {
        alt::Vector2i pos = args.Get<alt::Vector2i>("pos", {0, 0});
        alt::Vector2i size = args.Get<alt::Vector2i>("size", {0, 0});
        bool isVisible = args.Get("isVisible", true);
        bool isOverlay = args.Get("isOverlay", false);

        return alt::ICore::Instance().CreateWebView(url, pos, size, isVisible, isOverlay, args.GetResource()->GetResource());
    }
});
