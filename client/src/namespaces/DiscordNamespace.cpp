#include "Namespace.h"
#include "interfaces/IAltResource.h"

static void IsReadyGetter(js::PropertyContext& ctx)
{
    ctx.Return(alt::ICore::Instance().GetDiscordManager()->IsUserDataReady());
}

static void UserIDGetter(js::PropertyContext& ctx)
{
    ctx.Return(alt::ICore::Instance().GetDiscordManager()->GetUserID());
}

static void UserNameGetter(js::PropertyContext& ctx)
{
    ctx.Return(alt::ICore::Instance().GetDiscordManager()->GetUsername());
}

static void DiscriminatorGetter(js::PropertyContext& ctx)
{
    ctx.Return(alt::ICore::Instance().GetDiscordManager()->GetDiscriminator());
}

static void AvatarGetter(js::PropertyContext& ctx)
{
    ctx.Return(alt::ICore::Instance().GetDiscordManager()->GetAvatar());
}

static void RequestOAuth2Token(js::FunctionContext& ctx)
{
    if(!ctx.CheckArgCount(1)) return;

    std::string appId;
    if(!ctx.GetArg(0, appId)) return;

    js::Promise* promise = new js::Promise;
    js::IAltResource* resource = ctx.GetResource<js::IAltResource>();
    auto callback = [=](bool success, const std::string& tokenStr)
    {
        std::string token = tokenStr;
        resource->PushNextTickCallback(
          [=]()
          {
              if(success) promise->Resolve(token);
              else
                  promise->Reject("Failed to get OAuth2 token");
              delete promise;
          });
    };
    alt::ICore::Instance().DiscordRequestOAuth2Token(appId, callback);

    ctx.Return(promise->Get());
}

// clang-format off
extern js::Namespace discordNamespace("Discord", [](js::NamespaceTemplate& tpl) {
    tpl.StaticProperty("isReady", IsReadyGetter);
    tpl.StaticProperty("userID", UserIDGetter);
    tpl.StaticProperty("userName", UserNameGetter);
    tpl.StaticProperty("discriminator", DiscriminatorGetter);
    tpl.StaticProperty("avatar", AvatarGetter);

    tpl.StaticFunction("requestOAuth2Token", RequestOAuth2Token);
});
