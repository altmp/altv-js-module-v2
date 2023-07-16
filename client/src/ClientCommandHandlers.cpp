#include "ClientCommandHandlers.h"
#include "CJavaScriptResource.h"

void js::DumpModulesCacheCommand(const std::vector<std::string>& args)
{
    if(!args.size())
    {
        Logger::Warn("Usage: dumpmodulescache <resource name>");
        return;
    }

    alt::IResource* resource = alt::ICore::Instance().GetResource(args[0]);
    if(!resource)
    {
        Logger::Warn("Resource", args[0], "not found");
        return;
    }
    if(resource->GetType() != "jsv2")
    {
        Logger::Warn("Resource", args[0], "is not a JS v2 resource");
        return;
    }

    CJavaScriptResource* jsResource = dynamic_cast<CJavaScriptResource*>(resource->GetImpl());
    jsResource->DumpModulesCache();
}
