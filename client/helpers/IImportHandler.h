#pragma once

#include "v8.h"

class IImportHandler
{
    static v8::MaybeLocal<v8::Module>
      ResolveModuleCallback(v8::Local<v8::Context> context, v8::Local<v8::String> specifier, v8::Local<v8::FixedArray> importAssertions, v8::Local<v8::Module> referrer);

    int GetNextScriptId()
    {
        static int nextScriptId = 0;
        return ++nextScriptId;
    }

public:
    v8::MaybeLocal<v8::Module> CompileModule(const std::string& name, const std::string& source);
    bool InstantiateModule(v8::Local<v8::Context> context, v8::Local<v8::Module> module);
    bool EvaluateModule(v8::Local<v8::Context> context, v8::Local<v8::Module> module);
};
