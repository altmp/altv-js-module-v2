#include "Class.h"
#include "helpers/Buffer.h"

static void Send(js::FunctionContext& ctx)
{
    if(!ctx.CheckThis()) return;
    if(!ctx.CheckArgCount(1)) return;
    if(!ctx.CheckArgType(0, { js::Type::STRING, js::Type::BUFFER })) return;
    alt::IWebSocketClient* websocket = ctx.GetThisObject<alt::IWebSocketClient>();

    if(ctx.GetArgType(0) == js::Type::STRING)
    {
        std::string msg;
        if(!ctx.GetArg(0, msg)) return;

        ctx.Return(websocket->Send(msg));
    }
    else if(ctx.GetArgType(0) == js::Type::BUFFER)
    {
        js::Buffer* buffer;
        if(!ctx.GetArg(0, buffer)) return;

        ctx.Return(websocket->SendBinary(std::string{ (char*)buffer->GetBuffer(), buffer->GetSize() }));
    }
}

// clang-format off
extern js::Class baseObjectClass;
extern js::Class webSocketClientClass("WebSocketClient", &baseObjectClass, [](js::ClassTemplate& tpl) {
    tpl.BindToType(alt::IBaseObject::Type::WEBSOCKET_CLIENT);

    tpl.Property<&alt::IWebSocketClient::GetUrl, &alt::IWebSocketClient::SetUrl>("url");
    tpl.Property<&alt::IWebSocketClient::IsAutoReconnectEnabled, &alt::IWebSocketClient::SetAutoReconnectEnabled>("autoReconnect");
    tpl.Property<&alt::IWebSocketClient::IsPerMessageDeflateEnabled, &alt::IWebSocketClient::SetPerMessageDeflateEnabled>("perMessageDeflate");
    tpl.Property<&alt::IWebSocketClient::GetPingInterval, &alt::IWebSocketClient::SetPingInterval>("pingInterval");
    tpl.Property<&alt::IWebSocketClient::GetReadyState>("readyState");

    tpl.Method<&alt::IWebSocketClient::Start>("start");
    tpl.Method<&alt::IWebSocketClient::Stop>("stop");
    tpl.Method("send", Send);
    tpl.Method<&alt::IWebSocketClient::AddSubProtocol>("addSubProtocol");
    tpl.Method<&alt::IWebSocketClient::GetSubProtocols>("getSubProtocols");
    tpl.Method<&alt::IWebSocketClient::SetExtraHeader>("setExtraHeader");
    tpl.Method<&alt::IWebSocketClient::GetExtraHeaders>("getExtraHeaders");

    tpl.GetByID<alt::IBaseObject::Type::WEBSOCKET_CLIENT>();
});
