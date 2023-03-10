#include "IResource.h"

alt::MValue js::IResource::Function::Call(alt::MValueArgs args) const
{
    auto& core = alt::ICore::Instance();
    if(!resource->GetResource()->IsStarted()) return core.CreateMValueNone();

    v8::Isolate* isolate = resource->GetIsolate();
    v8::Local<v8::Context> context = resource->GetContext();
    v8::Locker locker(isolate);
    v8::Isolate::Scope isolateScope(isolate);
    v8::HandleScope handleScope(isolate);
    v8::Context::Scope contextScope(context);

    v8::Local<v8::Function> func = function.Get(isolate);
    std::vector<v8::Local<v8::Value>> jsArgs;
    jsArgs.reserve(args.GetSize());
    for(size_t i = 0; i < args.GetSize(); ++i) jsArgs.push_back(MValueToJS(args[i]));

    // todo: function helper
    v8::MaybeLocal<v8::Value> maybeResult = func->Call(context, v8::Undefined(isolate), jsArgs.size(), jsArgs.data());
    if(maybeResult.IsEmpty()) return core.CreateMValueNone();
    return JSToMValue(maybeResult.ToLocalChecked());
}

void js::IResource::Function::ExternalFunctionCallback(const v8::FunctionCallbackInfo<v8::Value>& info)
{
    alt::MValueFunctionConst* func = static_cast<alt::MValueFunctionConst*>(info.Data().As<v8::External>()->Value());
    alt::MValueArgs args;
    args.Reserve(info.Length());
    for(size_t i = 0; i < info.Length(); ++i) args.Push(JSToMValue(info[i], false));
    alt::MValue retValue = (*func)->Call(args);
    info.GetReturnValue().Set(MValueToJS(retValue));
}

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

    {
        TemporaryGlobalExtension altExtension(ctx, "__alt", altModule.GetNamespace(this));
        TemporaryGlobalExtension clientScriptEventExtension(ctx, "__clientScriptEventType", js::JSValue((int)alt::CEvent::Type::CLIENT_SCRIPT_EVENT));
        TemporaryGlobalExtension serverScriptEventExtension(ctx, "__serverScriptEventType", js::JSValue((int)alt::CEvent::Type::SERVER_SCRIPT_EVENT));
        TemporaryGlobalExtension getBindingExtension(ctx, "getBinding", WrapFunction(GetBindingNamespaceWrapper)->GetFunction(ctx).ToLocalChecked());

        for(auto binding : bindings) InitializeBinding(binding);
        RegisterBindingExports();
        InitializeEvents();
    }
}
