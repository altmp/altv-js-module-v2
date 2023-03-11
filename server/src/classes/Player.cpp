#include "Class.h"
#include "interfaces/IResource.h"
#include "cpp-sdk/ICore.h"

static void Ctor(js::FunctionContext& ctx)
{
    if(!ctx.CheckCtor()) return;
    if(!ctx.CheckArgCount(2)) return;

    std::string name;
    if(!ctx.GetArg(0, name, js::Type::STRING)) return;

    std::string name2;
    if(!ctx.GetArg(1, name2)) return;

    std::cout << "got name " << name << std::endl;
    std::cout << "got name2 " << name2 << std::endl;
}

// clang-format off
extern js::Class sharedPlayerClass;
extern js::Class playerClass("Player", &sharedPlayerClass, Ctor, [](js::ClassTemplate& tpl)
{
    js::IScriptObjectHandler::BindClassToType(alt::IBaseObject::Type::PLAYER, &playerClass);

    tpl.StaticProperty("server", 45);
});
