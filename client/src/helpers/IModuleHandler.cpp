#include "IModuleHandler.h"
#include "Filesystem.h"
#include "interfaces/IResource.h"
#include "CJavaScriptResource.h"
#include "Module.h"
#include "Logger.h"
#include "magic_enum/include/magic_enum.hpp"
#include "CJavaScriptRuntime.h"

static constexpr const char bytecodeMagic[] = { 'A', 'L', 'T', 'B', 'C' };
static constexpr const char resourceImportPrefix[] = "@resource/";
static std::unordered_map<int, IModuleHandler::PersistentSyntheticModuleExports> syntheticModuleExports;

v8::MaybeLocal<v8::Value> IModuleHandler::SyntheticModuleEvaluateCallback(v8::Local<v8::Context> context, v8::Local<v8::Module> module)
{
    int identityHash = module->GetIdentityHash();
    if(!syntheticModuleExports.contains(identityHash)) return v8::MaybeLocal<v8::Value>();

    v8::Isolate* isolate = v8::Isolate::GetCurrent();
    for(const auto& [key, value] : syntheticModuleExports.at(identityHash)) module->SetSyntheticModuleExport(isolate, js::JSValue(key), value.Get(isolate));
    syntheticModuleExports.erase(identityHash);

    v8::Local<v8::Promise::Resolver> promise = v8::Promise::Resolver::New(context).ToLocalChecked();
    promise->Resolve(context, v8::Undefined(isolate));
    return promise;
}

v8::MaybeLocal<v8::Module>
  IModuleHandler::ResolveModuleCallback(v8::Local<v8::Context> context, v8::Local<v8::String> specifier, v8::Local<v8::FixedArray> importAssertions, v8::Local<v8::Module> referrer)
{
    CJavaScriptResource* resource = js::IResource::GetFromContext<CJavaScriptResource>(context);
    if(!resource) return v8::MaybeLocal<v8::Module>();

    std::unordered_map<std::string, std::string> assertions = TransformImportAssertions(importAssertions);
    return resource->Resolve(context, js::CppValue(specifier), referrer, assertions);
}

std::unordered_map<std::string, std::string> IModuleHandler::TransformImportAssertions(v8::Local<v8::FixedArray> assertions)
{
    v8::Isolate* isolate = v8::Isolate::GetCurrent();
    v8::Local<v8::Context> ctx = isolate->GetEnteredOrMicrotaskContext();
    std::unordered_map<std::string, std::string> result;

    for(int i = 0; i < assertions->Length() / 2; i += 2)
    {
        std::string key = js::CppValue(assertions->Get(ctx, i).As<v8::String>());
        std::string value = js::CppValue(assertions->Get(ctx, i + 1).As<v8::String>());
        result.insert({ key, value });
    }

    return result;
}

bool IModuleHandler::IsBytecodeBuffer(const std::vector<uint8_t>& buffer)
{
    return buffer.size() >= sizeof(bytecodeMagic) && std::memcmp(buffer.data(), bytecodeMagic, sizeof(bytecodeMagic)) == 0;
}

bool IModuleHandler::IsValidBuiltinModule(js::IResource* resource, const std::string& moduleName)
{
    if(!js::Module::Exists(moduleName)) return false;
    js::Module& mod = js::Module::Get(moduleName);

    bool compatibilityModeEnabled = resource->IsCompatibilityModeEnabled();
    if(mod.HasOption(js::Module::Option::COMPATIBILITY_MODULE) && !compatibilityModeEnabled) return false;

    return true;
}

v8::MaybeLocal<v8::Module>
  IModuleHandler::Resolve(v8::Local<v8::Context> context, const std::string& specifier, v8::Local<v8::Module> referrer, std::unordered_map<std::string, std::string>& assertions)
{
    v8::Isolate* isolate = context->GetIsolate();
    if(modules.contains(specifier)) return modules.at(specifier).module.Get(isolate);
    js::IResource* resource = js::IResource::GetFromContext(context);

    std::string name = specifier;
    v8::MaybeLocal<v8::Module> module;
    Module::Type type;

    if(assertions.contains("type"))
    {
        std::string assertionType = assertions.at("type");
        if(assertionType == "json")
        {
            module = ResolveJSON(context, specifier, GetModulePath(referrer), name);
            type = Module::Type::JSON;
        }
        else
        {
            js::Throw("Invalid import assertion type '" + assertionType + "'");
            return v8::MaybeLocal<v8::Module>();
        }
    }
    else if(IsValidBuiltinModule(resource, specifier))
    {
        module = ResolveBuiltin(context, specifier);
        type = Module::Type::Builtin;
    }
    else if(specifier.starts_with(resourceImportPrefix))
    {
        module = ResolveResource(context, specifier);
        type = Module::Type::Resource;
    }
    else
    {
        bool isBytecode = false;
        module = ResolveFile(context, specifier, GetModulePath(referrer), name, isBytecode);
        type = isBytecode ? Module::Type::Bytecode : Module::Type::File;
    }

    if(module.IsEmpty())
    {
        js::Throw("Module not found: " + specifier);
        return v8::MaybeLocal<v8::Module>();
    }
    modules.insert({ name, Module{ module.ToLocalChecked(), type } });
    return module;
}

v8::MaybeLocal<v8::Module> IModuleHandler::ResolveBuiltin(v8::Local<v8::Context> context, const std::string& specifier)
{
    js::Module& mod = js::Module::Get(specifier);
    js::Object exports = mod.GetNamespace(js::IResource::GetFromContext(context));
    return CompileSyntheticModule(specifier, exports.ToMap<v8::Local<v8::Value>>());
}

v8::MaybeLocal<v8::Module> IModuleHandler::ResolveResource(v8::Local<v8::Context> context, const std::string& specifier)
{
    std::string resourceName = specifier.substr(sizeof(resourceImportPrefix) - 1);
    alt::IResource* resource = alt::ICore::Instance().GetResource(resourceName);
    if(!resource || resource == js::IResource::GetFromContext(context)->GetResource()) return v8::MaybeLocal<v8::Module>();

    alt::MValueDict resourceExports = resource->GetExports();
    js::Object exports = js::MValueToJS(resourceExports).As<v8::Object>();
    return CompileSyntheticModule(specifier, exports.ToMap<v8::Local<v8::Value>>());
}

// Returns pair of resolved name and file content
static inline std::pair<std::string, std::vector<uint8_t>> ReadFile(v8::Local<v8::Context> context, const std::string& specifier, const std::string& referrer)
{
    alt::IResource* resource = js::IResource::GetFromContext(context)->GetResource();
    alt::IPackage::PathInfo path = alt::ICore::Instance().Resolve(resource, specifier, referrer);
    if(!path.pkg) return {};

    std::string fileName = path.fileName;
    if(!js::DoesFileExist(path.pkg, fileName)) return {};

    std::string name = path.prefix + fileName;
    return { name, js::ReadFile(path.pkg, fileName) };
}

v8::MaybeLocal<v8::Module> IModuleHandler::ResolveFile(v8::Local<v8::Context> context, const std::string& specifier, const std::string& referrer, std::string& name, bool& isBytecode)
{
    v8::Isolate* isolate = v8::Isolate::GetCurrent();

    auto [resolvedName, buffer] = ReadFile(context, specifier, referrer);
    if(resolvedName.empty()) return v8::MaybeLocal<v8::Module>{};
    if(modules.contains(resolvedName)) return modules.at(resolvedName).module.Get(isolate);

    name = resolvedName;
    isBytecode = IsBytecodeBuffer(buffer);
    if(isBytecode) return CompileBytecode(name, buffer);
    return CompileModule(name, std::string{ (char*)buffer.data(), buffer.size() });
}

v8::MaybeLocal<v8::Module> IModuleHandler::ResolveJSON(v8::Local<v8::Context> context, const std::string& specifier, const std::string& referrer, std::string& name)
{
    v8::Isolate* isolate = v8::Isolate::GetCurrent();

    auto [resolvedName, buffer] = ReadFile(context, specifier, referrer);
    if(modules.contains(resolvedName)) return modules.at(resolvedName).module.Get(isolate);

    std::string source{ (char*)buffer.data(), buffer.size() };
    v8::MaybeLocal<v8::Value> maybeValue = v8::JSON::Parse(context, js::JSValue(source));
    if(maybeValue.IsEmpty())
    {
        js::Logger::Error("Failed to parse JSON module: " + specifier);
        return v8::MaybeLocal<v8::Module>();
    }
    return CompileSyntheticModule(name, { { "default", maybeValue.ToLocalChecked() } });
}

v8::MaybeLocal<v8::Module> IModuleHandler::CompileModule(const std::string& name, const std::string& source)
{
    v8::Isolate* isolate = v8::Isolate::GetCurrent();
    v8::ScriptOrigin origin{ isolate, js::JSValue(name), 0, 0, false, GetNextScriptId(), v8::Local<v8::Value>(), false, false, true, v8::Local<v8::PrimitiveArray>() };
    v8::ScriptCompiler::Source compilerSource{ js::JSValue(source), origin };
    v8::MaybeLocal<v8::Module> maybeModule = v8::ScriptCompiler::CompileModule(isolate, &compilerSource);
    return maybeModule;
}

v8::Local<v8::Module> IModuleHandler::CompileSyntheticModule(const std::string& name, const SyntheticModuleExports& exports)
{
    v8::Isolate* isolate = v8::Isolate::GetCurrent();

    IModuleHandler::PersistentSyntheticModuleExports persistentExports;
    std::vector<v8::Local<v8::String>> exportKeys;
    exportKeys.reserve(exports.size());
    persistentExports.reserve(exports.size());
    for(const auto& [key, value] : exports)
    {
        exportKeys.push_back(js::JSValue(key));
        persistentExports.insert({ key, js::Persistent<v8::Value>(isolate, value) });
    }

    v8::Local<v8::Module> module = v8::Module::CreateSyntheticModule(isolate, js::JSValue(name), exportKeys, SyntheticModuleEvaluateCallback);

    syntheticModuleExports.insert({ module->GetIdentityHash(), persistentExports });
    return module;
}

v8::MaybeLocal<v8::Module> IModuleHandler::CompileBytecode(const std::string& name, const std::vector<uint8_t>& buffer)
{
    v8::Isolate* isolate = v8::Isolate::GetCurrent();

    // Read bytecode buffer data
    int sourceCodeSize = 0;
    size_t bytecodeSize = buffer.size() - sizeof(bytecodeMagic) - sizeof(int);
    uint8_t* bytecode = new uint8_t[bytecodeSize];
    memcpy(&sourceCodeSize, buffer.data() + sizeof(bytecodeMagic), sizeof(int));
    memcpy(bytecode, buffer.data() + sizeof(bytecodeMagic) + sizeof(int), bytecodeSize);

    std::string sourceStr = "'" + std::string(' ', sourceCodeSize - 2) + "'";

    v8::ScriptCompiler::CachedData* cachedData = new v8::ScriptCompiler::CachedData(bytecode, bytecodeSize, v8::ScriptCompiler::CachedData::BufferOwned);
    v8::ScriptOrigin origin(isolate, js::JSValue(name), 0, 0, false, GetNextScriptId(), v8::Local<v8::Value>(), false, false, true, v8::Local<v8::PrimitiveArray>());

    v8::ScriptCompiler::Source source{ js::JSValue(sourceStr), origin, cachedData };
    v8::MaybeLocal<v8::Module> module = v8::ScriptCompiler::CompileModule(isolate, &source, v8::ScriptCompiler::kConsumeCodeCache);
    if(cachedData->rejected)
    {
        js::Logger::Error("[JS] Trying to load invalid bytecode");
        return v8::MaybeLocal<v8::Module>();
    }
    return module;
}

bool IModuleHandler::InstantiateModule(v8::Local<v8::Context> context, v8::Local<v8::Module> module)
{
    v8::Maybe<bool> maybeResult = module->InstantiateModule(context, ResolveModuleCallback);
    return maybeResult.FromMaybe(false) && module->GetStatus() == v8::Module::kInstantiated;
}

v8::MaybeLocal<v8::Value> IModuleHandler::EvaluateModule(v8::Local<v8::Context> context, v8::Local<v8::Module> module)
{
    v8::MaybeLocal<v8::Value> maybeResult = module->Evaluate(context);
    return maybeResult;
}

void IModuleHandler::DumpModulesCache()
{
    v8::Isolate* isolate = CJavaScriptRuntime::Instance().GetIsolate();
    v8::Locker locker(isolate);
    v8::HandleScope scope(isolate);
    v8::Isolate::Scope isolateScope(isolate);

    js::Logger::Info("Modules cache:");
    for(const auto& [name, module] : modules)
    {
        js::Logger::Colored("~y~", name, "~w~| Type:~y~", magic_enum::enum_name(module.type), "~w~| Status:~y~", magic_enum::enum_name(module.module.Get(isolate)->GetStatus()));
    }
}
