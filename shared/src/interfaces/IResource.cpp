#include "IResource.h"

void js::IResource::GetBindingNamespaceWrapper(js::FunctionContext& ctx)
{
    if(!ctx.CheckArgCount(1)) return;

    std::string bindingName;
    if(!ctx.GetArg(0, bindingName)) return;

    Binding& binding = Binding::Get(bindingName);
    if(!ctx.Check(binding.IsValid(), "Invalid binding name")) return;
    IResource* resource = ctx.GetResource();
    if(!resource) return;

    v8::Local<v8::Module> bindingModule = binding.GetCompiledModule(resource);
    if(bindingModule->GetStatus() != v8::Module::Status::kEvaluated) resource->InitializeBinding(&binding);
    ctx.Return(bindingModule->GetModuleNamespace());
}

void js::IResource::InitializeBinding(js::Binding* binding)
{
    if(binding->GetName().ends_with("bootstrap.js")) return;  // Skip bootstrap bindings, those are handled separately

    v8::Local<v8::Module> module = binding->GetCompiledModule(this);
    if(module.IsEmpty())
    {
        alt::ICore::Instance().LogError("INTERNAL ERROR: Failed to compile binding module " + binding->GetName());
        return;
    }
    if(module->GetStatus() == v8::Module::Status::kEvaluated) return;

    module->Evaluate(GetContext());
    if(module->GetStatus() != v8::Module::Status::kEvaluated)
    {
        alt::ICore::Instance().LogError("INTERNAL ERROR: Failed to evaluate binding module " + binding->GetName());
        v8::Local<v8::Value> exception = module->GetException();
        if(!exception.IsEmpty()) alt::ICore::Instance().LogError("INTERNAL ERROR: " + std::string(*v8::String::Utf8Value(isolate, exception)));
    }
}

void js::IResource::RegisterBindingExport(const std::string& name, const std::string& bindingName, const std::string& exportName)
{
    Binding& binding = Binding::Get(bindingName);
    if(!binding.IsValid())
    {
        alt::ICore::Instance().LogError("INTERNAL ERROR: Failed to get binding " + bindingName);
        return;
    }
    v8::Local<v8::Module> mod = binding.GetCompiledModule(this);
    v8::Local<v8::Object> moduleNamespace = mod->GetModuleNamespace().As<v8::Object>();
    v8::MaybeLocal<v8::Value> maybeExportedValue = moduleNamespace->Get(GetContext(), js::JSValue(exportName));

    v8::Local<v8::Value> exportedValue;
    if(!maybeExportedValue.ToLocal(&exportedValue) || exportedValue->IsUndefined())
    {
        alt::ICore::Instance().LogError("INTERNAL ERROR: Failed to get exported value " + exportName + " from binding " + bindingName);
        return;
    }
    bindingExports.insert({ name, Persistent<v8::Value>(isolate, exportedValue) });
}

void js::IResource::InitializeBindings(Binding::Scope scope, Module& altModule)
{
    std::vector<Binding*> bindings = Binding::GetBindingsForScope(scope);
    v8::Local<v8::Context> ctx = GetContext();

    ctx->Global()->Set(ctx, js::JSValue("__alt"), altModule.GetNamespace(this));
    ctx->Global()->Set(ctx, js::JSValue("getBinding"), WrapFunction(GetBindingNamespaceWrapper)->GetFunction(ctx).ToLocalChecked());

    for(auto binding : bindings) InitializeBinding(binding);
    RegisterBindingExports();
    InitializeEvents();

    ctx->Global()->Delete(ctx, js::JSValue("__alt"));
    ctx->Global()->Delete(ctx, js::JSValue("getBinding"));
}
