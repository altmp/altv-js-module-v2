#pragma once

#include "v8.h"

#include "helpers/JS.h"

#include <unordered_map>

namespace js
{
    class ICompatibilityHandler
    {
        Persistent<v8::Object> moduleNamespace;

    protected:
        void RegisterCompatibilityExport(const std::string& name, v8::Local<v8::Value> value);

        void Initialize();
        void Reset();

    public:
        v8::Local<v8::Object> GetCompatibilityModuleNamespace();

        static void RegisterCompatibilityExportFunc(js::FunctionContext& ctx);
    };
}  // namespace js
