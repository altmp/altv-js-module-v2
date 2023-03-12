#include "Bindings.h"
#include "interfaces/IResource.h"

static v8::MaybeLocal<v8::Module> ResolveModuleCallback(v8::Local<v8::Context> context, v8::Local<v8::String> specifier, v8::Local<v8::FixedArray> assertions, v8::Local<v8::Module> referrer)
{
    return v8::MaybeLocal<v8::Module>();
}

v8::Local<v8::Module> js::Binding::Compile(IResource* resource)
{
    v8::Isolate* isolate = resource->GetIsolate();
    v8::Local<v8::Context> context = resource->GetContext();
    std::string moduleName = "internal:" + name;
    v8::ScriptOrigin origin{
        isolate, v8::String::NewFromUtf8(isolate, moduleName.c_str()).ToLocalChecked(), 0, 0, false, -1, v8::Local<v8::Value>(), false, false, true, v8::Local<v8::PrimitiveArray>()
    };
    v8::ScriptCompiler::Source source{ v8::String::NewFromUtf8(isolate, src.c_str()).ToLocalChecked(), origin };
    v8::MaybeLocal<v8::Module> maybeModule = v8::ScriptCompiler::CompileModule(isolate, &source);
    if(maybeModule.IsEmpty())
    {
        Logger::Error("INTERNAL ERROR: Failed to compile bindings module", name);
        return v8::Local<v8::Module>();
    }
    v8::Local<v8::Module> mod = maybeModule.ToLocalChecked();
    v8::Maybe<bool> result = mod->InstantiateModule(context, &ResolveModuleCallback);
    if(result.IsNothing() || !result.ToChecked())
    {
        Logger::Error("INTERNAL ERROR: Failed to instantiate bindings module", name);
        return v8::Local<v8::Module>();
    }
    compiledModuleMap.insert({ resource, std::move(Persistent<v8::Module>(isolate, mod)) });
    return mod;
}

v8::Local<v8::Module> js::Binding::GetCompiledModule(IResource* resource)
{
    v8::Isolate* isolate = resource->GetIsolate();
    v8::Local<v8::Module> mod;

    auto it = compiledModuleMap.find(resource);
    if(it == compiledModuleMap.end()) mod = Compile(resource);
    else
        mod = it->second.Get(isolate);

    return mod;
}

std::vector<js::Binding*> js::Binding::GetBindingsForScope(Scope scope)
{
    std::vector<Binding*> sharedBindings;
    std::vector<Binding*> bindings;
    for(auto& [_, binding] : __bindings)
    {
        if(binding.scope == Scope::SHARED) sharedBindings.push_back(&binding);
        else if(binding.scope == scope)
            bindings.push_back(&binding);
    }
    // Insert shared bindings at the beginning
    sharedBindings.insert(sharedBindings.end(), bindings.begin(), bindings.end());
    return sharedBindings;
}

void js::Binding::CleanupForResource(IResource* resource)
{
    for(auto& [_, binding] : __bindings)
    {
        binding.compiledModuleMap.erase(resource);
    }
}
