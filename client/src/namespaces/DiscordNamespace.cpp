#include "Namespace.h"

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

// clang-format off
extern js::Namespace discordNamespace("Discord", [](js::NamespaceTemplate& tpl) {
    tpl.StaticProperty("isReady", IsReadyGetter);
    tpl.StaticProperty("userID", UserIDGetter);
    tpl.StaticProperty("userName", UserNameGetter);
    tpl.StaticProperty("discriminator", DiscriminatorGetter);
    tpl.StaticProperty("avatar", AvatarGetter);
});
