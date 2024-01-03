#include "Logger.h"
#include "Module.h"
#include "interfaces/IResource.h"
#include "FactoryHandler.h"
#include "magic_enum/include/magic_enum.hpp"

static void ToggleEvent(js::FunctionContext& ctx)
{
    if(!ctx.CheckArgCount(2)) return;

    alt::CEvent::Type type;
    if(!ctx.GetArg(0, type)) return;

    bool state;
    if(!ctx.GetArg(1, state)) return;

    alt::ICore::Instance().ToggleEvent(type, state);
}

static void SetEntityFactory(js::FunctionContext& ctx)
{
    if(!ctx.CheckArgCount(2)) return;

    alt::IBaseObject::Type type;
    if(!ctx.GetArg(0, type)) return;

    v8::Local<v8::Value> factory;
    if(!ctx.GetArg(1, factory)) return;

    js::IResource* resource = ctx.GetResource();
    resource->SetCustomFactory(type, factory.As<v8::Function>());
}

static void GetEntityFactory(js::FunctionContext& ctx)
{
    if(!ctx.CheckArgCount(1)) return;

    alt::IBaseObject::Type type;
    if(!ctx.GetArg(0, type)) return;

    js::IResource* resource = ctx.GetResource();
    v8::Local<v8::Function> factory = resource->GetCustomFactory(type);
    if(factory.IsEmpty())
    {
        ctx.Return(nullptr);
        return;
    }
    ctx.Return(factory);
}

static void CreateEntity(js::FunctionContext& ctx)
{
    if(!ctx.CheckArgCount(2)) return;

    alt::IBaseObject::Type type;
    if(!ctx.GetArg(0, type)) return;

    js::Object args;
    if(!ctx.GetArg(1, args)) return;

    js::IResource* resource = ctx.GetResource();
    js::ScriptObject* scriptObject = nullptr;
    {
        js::TryCatch tryCatch;
        alt::IBaseObject* object = js::FactoryHandler::Create(type, args);
        if(!object)
        {
            if(!tryCatch.HasCaught()) ctx.Throw("Failed to create entity of type " + std::string(magic_enum::enum_name(type)));
            tryCatch.ReThrow();
            return;
        }

        scriptObject = resource->GetScriptObject(object);
        if(!scriptObject)
        {
            if(!tryCatch.HasCaught()) ctx.Throw("Failed to create entity of type " + std::string(magic_enum::enum_name(type)));
            tryCatch.ReThrow();
            return;
        }
    }

    js::Function func = resource->GetBindingExport<v8::Function>(js::BindingExport::ADD_ENTITY_TO_ALL);
    if(!ctx.Check(func.IsValid(), "INTERNAL ERROR: Failed to get addEntityToAll function")) return;
    func.Call(scriptObject->Get());

    ctx.Return(scriptObject->Get());
}

static void GetAllEntities(js::FunctionContext& ctx)
{
    std::vector<alt::IEntity*> entities = alt::ICore::Instance().GetEntities();

    ctx.Return(entities);
}

static void GetAllVirtualEntities(js::FunctionContext& ctx)
{
    std::vector<alt::IBaseObject*> virtualEntities = alt::ICore::Instance().GetBaseObjects(alt::IBaseObject::Type::VIRTUAL_ENTITY);
    ctx.Return(virtualEntities);
}

static void GetCurrentSourceLocation(js::FunctionContext& ctx)
{
    int framesToSkip = ctx.GetArg<int>(0, 0);

    js::Object obj;
    js::SourceLocation location = js::SourceLocation::GetCurrent(ctx.GetResource(), framesToSkip);
    obj.Set("fileName", location.file);
    obj.Set("lineNumber", location.line);

    ctx.Return(obj);
}

static void RegisterExport(js::FunctionContext& ctx)
{
    if(!ctx.CheckArgCount(2)) return;

    js::BindingExport export_;
    if(!ctx.GetArg(0, export_)) return;

    v8::Local<v8::Value> value;
    if(!ctx.GetArg(1, value)) return;

    js::IResource* resource = ctx.GetResource();
    if(!ctx.Check(!resource->HasBindingExport(export_), "Binding export already registered")) return;

    resource->SetBindingExport(export_, value);
}

static void GetBuiltinModule(js::FunctionContext& ctx)
{
    if(!ctx.CheckArgCount(1)) return;
    js::IResource* resource = ctx.GetResource();

    std::string name;
    if(!ctx.GetArg(0, name)) return;

    if(!js::Module::Exists(name))
    {
        ctx.Return(nullptr);
        return;
    }
    js::Module& mod = js::Module::Get(name);
    if(mod.HasOption(js::Module::Option::COMPATIBILITY_MODULE) && !resource->IsCompatibilityModeEnabled())
    {
        ctx.Return(nullptr);
        return;
    }
    ctx.Return(mod.GetNamespace(resource));
}

static void ResourceNameGetter(js::LazyPropertyContext& ctx)
{
    ctx.Return(ctx.GetResource()->GetResource()->GetName());
}

static void BindingExportGetter(js::LazyPropertyContext& ctx)
{
    js::Object obj;
    auto values = magic_enum::enum_entries<js::BindingExport>();
    for(auto& [value, key] : values)
    {
        obj.Set(key.data(), (int)value);
    }
    ctx.Return(obj);
}

// clang-format off
// Used to provide C++ functions to the JS bindings
extern js::Module sharedCppBindingsModule("sharedCppBindings", [](js::ModuleTemplate& module)
{
    module.StaticFunction("toggleEvent", ToggleEvent);
    module.StaticFunction("setEntityFactory", SetEntityFactory);
    module.StaticFunction("getEntityFactory", GetEntityFactory);

    module.StaticFunction("createEntity", CreateEntity);
    module.StaticFunction("getAllEntities", GetAllEntities);
    module.StaticFunction("getAllVirtualEntities", GetAllVirtualEntities);
    module.StaticFunction("getCurrentSourceLocation", GetCurrentSourceLocation);

    module.StaticFunction("registerExport", RegisterExport);
    module.StaticFunction("registerCompatibilityExport", js::ICompatibilityHandler::RegisterCompatibilityExportFunc);

    module.StaticFunction("getBuiltinModule", GetBuiltinModule);

    module.StaticLazyProperty("resourceName", ResourceNameGetter);

    module.StaticEnum<js::BindingExport>("BindingExport");
});
