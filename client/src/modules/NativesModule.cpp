#include "Module.h"

// clang-format off
static js::Module nativesModule("@altv/natives", [](js::ModuleTemplate& module)
{
    std::vector<alt::INative*> natives = alt::ICore::Instance().GetAllNatives();
});
