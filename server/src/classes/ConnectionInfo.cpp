#include "Class.h"
#include "interfaces/IResource.h"
#include "cpp-sdk/ICore.h"

static void Accept(js::FunctionContext& ctx)
{
    if (!ctx.CheckThis()) return;

    auto* connectionInfo = ctx.GetThisObject<alt::IConnectionInfo>();
    bool sendNames = ctx.GetArg(0, true);

    connectionInfo->Accept(sendNames);
}

// clang-format off
extern js::Class connectionInfoClass("ConnectionInfo", nullptr, nullptr, [](js::ClassTemplate& tpl)
{
    tpl.BindToType(alt::IBaseObject::Type::CONNECTION_INFO);

    tpl.Property<&alt::IConnectionInfo::GetName>("name");
    tpl.Property<&alt::IConnectionInfo::GetSocialId>("socialId");
    tpl.Property<&alt::IConnectionInfo::GetSocialName>("socialName");
    tpl.Property<&alt::IConnectionInfo::GetHwIdHash>("hwidHash");
    tpl.Property<&alt::IConnectionInfo::GetHwIdExHash>("hwidExHash");
    tpl.Property<&alt::IConnectionInfo::GetAuthToken>("authToken");
    tpl.Property<&alt::IConnectionInfo::GetIsDebug>("debug");
    tpl.Property<&alt::IConnectionInfo::GetBranch>("branch");
    tpl.Property<&alt::IConnectionInfo::GetBuild>("build");
    tpl.Property<&alt::IConnectionInfo::GetCdnUrl>("cdnUrl");
    tpl.Property<&alt::IConnectionInfo::GetPasswordHash>("passwordHash");
    tpl.Property<&alt::IConnectionInfo::GetIp>("ip");
    tpl.Property<&alt::IConnectionInfo::GetDiscordUserID>("discordUserId");
    tpl.Property<&alt::IConnectionInfo::GetCloudAuthHash>("cloudAuthHash");
    tpl.Property<&alt::IConnectionInfo::IsAccepted>("isAccepted");
    tpl.Property<&alt::IConnectionInfo::GetText>("text");

    tpl.Method("accept", Accept);
    tpl.Method<&alt::IConnectionInfo::Decline>("decline");
    tpl.Method<&alt::IConnectionInfo::SetText>("setText");
});
