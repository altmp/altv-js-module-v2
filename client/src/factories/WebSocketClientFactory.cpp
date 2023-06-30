#include "FactoryHandler.h"
#include "interfaces/IResource.h"

// clang-format off
static js::FactoryHandler webSocketClientFactory(alt::IBaseObject::Type::WEBSOCKET_CLIENT, [](js::Object& args) -> alt::IBaseObject* {
    std::string url;
    if(!args.Get("url", url)) return nullptr;

    return alt::ICore::Instance().CreateWebSocketClient(url, args.GetResource()->GetResource());
});
