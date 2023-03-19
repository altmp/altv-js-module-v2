#include "Module.h"
#include "Namespace.h"

static void NetTimeGetter(js::PropertyContext& ctx)
{
    ctx.Return(alt::ICore::Instance().GetNetTime());
}

static void SetServerPassword(js::FunctionContext& ctx)
{
    if(!ctx.CheckArgCount(1)) return;

    std::string password;
    if(!ctx.GetArg(0, password)) return;

    alt::ICore::Instance().SetPassword(password);
}

static void HashServerPassword(js::FunctionContext& ctx)
{
    if(!ctx.CheckArgCount(1)) return;

    std::string password;
    if(!ctx.GetArg(0, password)) return;

    ctx.Return(alt::ICore::Instance().HashServerPassword(password));
}

static void StopServer(js::FunctionContext& ctx)
{
    alt::ICore::Instance().StopServer();
}

// clang-format off
extern js::Class playerClass, vehicleClass, colShapeClass, checkpointClass;
extern js::Namespace eventsNamespace, pedModelInfoNamespace, vehicleModelInfoNamespace;
static js::Module altModule("alt", "alt-shared", { &playerClass, &vehicleClass, &colShapeClass, &checkpointClass }, [](js::ModuleTemplate& module)
{
    module.StaticProperty("isClient", false);
    module.StaticProperty("isServer", true);
    module.StaticProperty("rootDir", alt::ICore::Instance().GetRootDirectory());
    module.StaticProperty("netTime", NetTimeGetter);

    module.StaticFunction("setServerPassword", SetServerPassword);
    module.StaticFunction("hashServerPasword", HashServerPassword);
    module.StaticFunction("stopServer", StopServer);
    // todo: get server config

    module.Namespace(eventsNamespace);
    module.Namespace(pedModelInfoNamespace);
    module.Namespace(vehicleModelInfoNamespace);

    // ColShapes namespaces
    module.Namespace("ColshapeSphere");
    module.Namespace("ColshapeCylinder");
    module.Namespace("ColshapeCircle");
    module.Namespace("ColshapeCuboid");
    module.Namespace("ColshapeRectangle");
    module.Namespace("ColshapePolygon");
});
