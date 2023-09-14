#pragma once

#include "v8.h"

#include "helpers/JS.h"

#include <unordered_map>

namespace js
{
    class ICompatibilityHandler
    {
        Persistent<v8::Object> moduleNamespace;
        bool enabled = false;

    protected:
        void RegisterCompatibilityExport(const std::string& name, v8::Local<v8::Value> value);

        void Initialize();
        void Reset();

    public:
        v8::Local<v8::Object> GetCompatibilityModuleNamespace();

        bool IsCompatibilityModeEnabled()
        {
            return enabled;
        }

        void ToggleCompatibilityMode(bool state)
        {
            enabled = state;
        }

        static void RegisterCompatibilityExportFunc(js::FunctionContext& ctx);
    };
}  // namespace js
