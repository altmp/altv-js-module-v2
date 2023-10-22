#include "Class.h"
#include "interfaces/IAltResource.h"

static void ResponseCallback(alt::IHttpClient::HttpResponse response, const void* userData)
{
    js::Promise* promise = const_cast<js::Promise*>(static_cast<const js::Promise*>(userData));
    js::IAltResource* resource = static_cast<js::IAltResource*>(promise->GetResource());
    resource->PushNextTickCallback(
      [=]()
      {
          js::Object obj;
          obj.Set("statusCode", response.statusCode);
          obj.Set("headers", response.headers);
          obj.Set("body", response.body);

          promise->Resolve(obj);
          delete promise;
      });
}

template<auto Method, bool HasBody, bool HasProgressCallback = false>
static void GenericRequest(js::FunctionContext& ctx)
{
    if(!ctx.CheckThis()) return;
    if(!ctx.CheckArgCount(1)) return;
    alt::IHttpClient* client = ctx.GetThisObject<alt::IHttpClient>();

    std::string url;
    if(!ctx.GetArg(0, url)) return;

    std::string body;
    if constexpr(HasBody)
    {
        if(!ctx.GetArg(1, body)) return;
    }

    js::Promise* promise = ctx.GetResource()->CreatePromise();
    if constexpr(HasBody) (client->*Method)(ResponseCallback, url, body, (void*)promise);
    else if constexpr(HasProgressCallback)
        (client->*Method)(ResponseCallback, url, (void*)promise, nullptr);
    else
        (client->*Method)(ResponseCallback, url, (void*)promise);

    ctx.Return(promise->Get());
}

static void ExtraHeadersGetter(js::DynamicPropertyGetterContext& ctx)
{
    if(!ctx.CheckParent()) return;
    alt::IHttpClient* client = ctx.GetParent<alt::IHttpClient>();

    alt::MValueDict dict = client->GetExtraHeaders();
    alt::MValueConst value = dict->Get(ctx.GetProperty());

    ctx.Return(value);
}

static void ExtraHeadersSetter(js::DynamicPropertySetterContext& ctx)
{
    if(!ctx.CheckParent()) return;
    alt::IHttpClient* client = ctx.GetParent<alt::IHttpClient>();

    std::string value;
    if(!ctx.GetValue(value)) return;

    client->SetExtraHeader(ctx.GetProperty(), value);
}

static void ExtraHeadersEnumerator(js::DynamicPropertyEnumeratorContext& ctx)
{
    if(!ctx.CheckParent()) return;
    alt::IHttpClient* client = ctx.GetParent<alt::IHttpClient>();

    alt::MValueDict dict = client->GetExtraHeaders();
    js::Array arr(dict->GetSize());

    for(auto it = dict->Begin(); it != dict->End(); ++it) arr.Push(it->first);

    ctx.Return(arr.Get());
}

// clang-format off
extern js::Class httpClientClass("HttpClient", [](js::ClassTemplate& tpl)
{
    tpl.BindToType(alt::IBaseObject::Type::HTTP_CLIENT);

    tpl.Method("get", GenericRequest<&alt::IHttpClient::Get, false, true>);
    tpl.Method("head", GenericRequest<&alt::IHttpClient::Head, false>);
    tpl.Method("post", GenericRequest<&alt::IHttpClient::Post, true>);
    tpl.Method("put", GenericRequest<&alt::IHttpClient::Put, true>);
    tpl.Method("delete", GenericRequest<&alt::IHttpClient::Delete, true>);
    tpl.Method("connect", GenericRequest<&alt::IHttpClient::Connect, true>);
    tpl.Method("options", GenericRequest<&alt::IHttpClient::Options, true>);
    tpl.Method("trace", GenericRequest<&alt::IHttpClient::Trace, true>);
    tpl.Method("patch", GenericRequest<&alt::IHttpClient::Patch, true>);

    tpl.DynamicProperty("extraHeaders", ExtraHeadersGetter, ExtraHeadersSetter, nullptr, ExtraHeadersEnumerator);

    tpl.GetByID<alt::IBaseObject::Type::HTTP_CLIENT>();
});
