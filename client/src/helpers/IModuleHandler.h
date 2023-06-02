#pragma once

#include <unordered_map>

#include "v8.h"
#include "helpers/JS.h"

class IModuleHandler
{
public:
    struct Module
    {
        enum class Type
        {
            Builtin,
            Resource,
            File,
            Bytecode
        };

        js::Persistent<v8::Module> module;
        Type type;

        Module(v8::Local<v8::Module> _module, Type _type) : module(v8::Isolate::GetCurrent(), _module), type(_type) {}
    };

    using SyntheticModuleExports = std::unordered_map<std::string, v8::Local<v8::Value>>;

protected:
    static v8::MaybeLocal<v8::Value> SyntheticModuleEvaluateCallback(v8::Local<v8::Context> context, v8::Local<v8::Module> module);
    static v8::MaybeLocal<v8::Module>
      ResolveModuleCallback(v8::Local<v8::Context> context, v8::Local<v8::String> specifier, v8::Local<v8::FixedArray> importAssertions, v8::Local<v8::Module> referrer);

    std::string GetModulePath(v8::Local<v8::Module> module)
    {
        for(auto& [path, _module] : modules)
        {
            if(_module.module == module) return path;
        }
        return "";
    }

    bool IsBytecodeBuffer(const std::vector<uint8_t>& buffer);

    v8::MaybeLocal<v8::Module> Resolve(v8::Local<v8::Context> context, const std::string& specifier, v8::Local<v8::Module> referrer);
    v8::MaybeLocal<v8::Module> ResolveBuiltin(v8::Local<v8::Context> context, const std::string& specifier);
    v8::MaybeLocal<v8::Module> ResolveResource(v8::Local<v8::Context> context, const std::string& specifier);
    v8::MaybeLocal<v8::Module> ResolveFile(v8::Local<v8::Context> context, const std::string& specifier, const std::string& referrer, std::string& name, bool& isBytecode);

    int GetNextScriptId()
    {
        static int nextScriptId = 0;
        return ++nextScriptId;
    }

    std::unordered_map<std::string, Module> modules;

public:
    v8::MaybeLocal<v8::Module> CompileModule(const std::string& name, const std::string& source);
    v8::Local<v8::Module> CompileSyntheticModule(const std::string& name, const SyntheticModuleExports& exports);
    v8::MaybeLocal<v8::Module> CompileBytecode(const std::string& name, const std::vector<uint8_t>& bytecode);

    bool InstantiateModule(v8::Local<v8::Context> context, v8::Local<v8::Module> module);
    v8::MaybeLocal<v8::Value> EvaluateModule(v8::Local<v8::Context> context, v8::Local<v8::Module> module);
};
