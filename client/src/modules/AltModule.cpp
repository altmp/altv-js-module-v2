#include "Module.h"

// clang-format off
extern js::Class playerClass, localPlayerClass, vehicleClass, pedClass, networkObjectClass, bufferClass, audioClass, audioFilterClass, blipClass, textLabelClass;
extern js::Namespace eventsNamespace, discordNamespace, voiceNamespace;
static js::Module altModule("@altv/client", "@altv/shared",
    { &playerClass, &localPlayerClass, &vehicleClass, &pedClass, &networkObjectClass, &bufferClass, &audioClass, &audioFilterClass, &blipClass, &textLabelClass },
[](js::ModuleTemplate& module) {
    module.StaticProperty("isClient", true);
    module.StaticProperty("isServer", false);

    module.Namespace(eventsNamespace);
    module.Namespace(discordNamespace);
    module.Namespace(voiceNamespace);
});
