#pragma once

#include "v8.h"

namespace js
{
    using CommandArgs = const std::vector<std::string>;

    void DebugHandlesCommand(CommandArgs&);
    void DumpBindingCommand(CommandArgs&);
    void DumpAllBindingsCommand(CommandArgs&);
    void DumpSampleCommand(CommandArgs&);
    void DumpAllSamplesCommand(CommandArgs&);
    void ResetSamplesCommand(CommandArgs&);
    void DumpBuffersCommand(CommandArgs&);
}  // namespace js
