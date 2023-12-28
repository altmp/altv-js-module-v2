#include "Class.h"
#include "interfaces/IResource.h"
#include "interfaces/IAltResource.h"

static void Accept(js::FunctionContext& ctx)
{
    if(!ctx.CheckThis()) return;

    auto* connectionInfo = ctx.GetThisObject<alt::IConnectionInfo>();
    bool sendNames = ctx.GetArg(0, true);

    connectionInfo->Accept(sendNames);
}

// clang-format off
extern js::Class connectionInfoClass("ConnectionInfo", nullptr, nullptr, [](js::ClassTemplate& tpl)
{
    tpl.BindToType(alt::IBaseObject::Type::CONNECTION_INFO);

    tpl.LazyProperty<&alt::IConnectionInfo::GetName>("name");
    tpl.LazyProperty<&alt::IConnectionInfo::GetSocialId>("socialID");
    tpl.LazyProperty<&alt::IConnectionInfo::GetCloudID>("cloudID");
    tpl.LazyProperty<&alt::IConnectionInfo::GetCloudAuthResult>("cloudAuthResult");
    tpl.LazyProperty<&alt::IConnectionInfo::GetSocialName>("socialName");
    tpl.LazyProperty<&alt::IConnectionInfo::GetHwIdHash>("hwidHash");
    tpl.LazyProperty<&alt::IConnectionInfo::GetHwIdExHash>("hwidExHash");
    tpl.LazyProperty<&alt::IConnectionInfo::GetAuthToken>("authToken");
    tpl.LazyProperty<&alt::IConnectionInfo::GetIsDebug>("debug");
    tpl.LazyProperty<&alt::IConnectionInfo::GetBranch>("branch");
    tpl.LazyProperty<&alt::IConnectionInfo::GetVersionMajor>("versionMajor");
    tpl.LazyProperty<&alt::IConnectionInfo::GetVersionMinor>("versionMinor");
    tpl.LazyProperty<&alt::IConnectionInfo::GetCdnUrl>("cdnUrl");
    tpl.LazyProperty<&alt::IConnectionInfo::GetPasswordHash>("passwordHash");
    tpl.LazyProperty<&alt::IConnectionInfo::GetIp>("ip");
    tpl.LazyProperty<&alt::IConnectionInfo::GetDiscordUserID>("discordUserID");

    tpl.Property<&alt::IConnectionInfo::IsAccepted>("isAccepted");
    tpl.Property<&alt::IConnectionInfo::GetText, &alt::IConnectionInfo::SetText>("text");

    tpl.Method("accept", Accept);
    tpl.Method<&alt::IConnectionInfo::Decline>("decline");

    tpl.GetByID<alt::IBaseObject::Type::CONNECTION_INFO>();
});
