#include "IImportHandler.h"
#include "helpers/JS.h"

v8::MaybeLocal<v8::Module>
  IImportHandler::ResolveModuleCallback(v8::Local<v8::Context> context, v8::Local<v8::String> specifier, v8::Local<v8::FixedArray> importAssertions, v8::Local<v8::Module> referrer)
{
    // todo: add
    return v8::MaybeLocal<v8::Module>();
}

v8::MaybeLocal<v8::Module> IImportHandler::CompileModule(const std::string& name, const std::string& source)
{
    v8::Isolate* isolate = v8::Isolate::GetCurrent();
    v8::ScriptOrigin origin{ isolate, js::JSValue(name), 0, 0, false, GetNextScriptId(), v8::Local<v8::Value>(), false, false, true, v8::Local<v8::PrimitiveArray>() };
    v8::ScriptCompiler::Source compilerSource{ js::JSValue(source), origin };
    v8::MaybeLocal<v8::Module> maybeModule = v8::ScriptCompiler::CompileModule(isolate, &compilerSource);
    return maybeModule;
}

bool IImportHandler::InstantiateModule(v8::Local<v8::Context> context, v8::Local<v8::Module> module)
{
    v8::Maybe<bool> maybeResult = module->InstantiateModule(context, ResolveModuleCallback);
    return maybeResult.FromMaybe(false) && module->GetStatus() == v8::Module::kInstantiated;
}

bool IImportHandler::EvaluateModule(v8::Local<v8::Context> context, v8::Local<v8::Module> module)
{
    v8::MaybeLocal<v8::Value> maybeResult = module->Evaluate(context);
    return module->GetStatus() == v8::Module::kEvaluated;
}
