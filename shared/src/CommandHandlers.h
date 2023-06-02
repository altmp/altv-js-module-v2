#pragma once

#include "v8.h"

namespace js
{
    void DebugHandlesCommand(const std::vector<std::string>&);
    void DumpBindingCommand(const std::vector<std::string>&);
    void DumpAllBindingsCommand(const std::vector<std::string>&);
}  // namespace js
