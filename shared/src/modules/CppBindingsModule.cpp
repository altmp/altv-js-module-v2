#include "Logger.h"
#include "Module.h"
#include "interfaces/IResource.h"

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
    if(!ctx.Check(!resource->HasCustomFactory(type), "Entity factory already set")) return;

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

    alt::IBaseObject* object = nullptr;
    switch(type)
    {
        case alt::IBaseObject::Type::VEHICLE:
        {
            uint32_t model = 0;
            if(args.GetType("model") == js::Type::NUMBER) model = args.Get<uint32_t>("model");
            else if(args.GetType("model") == js::Type::STRING)
                model = alt::ICore::Instance().Hash(args.Get<std::string>("model"));
            alt::Vector3f pos = args.Get<alt::Vector3f>("pos");
            alt::Vector3f rot = args.Get<alt::Vector3f>("rot");
            object = alt::ICore::Instance().CreateVehicle(model, pos, rot);
            break;
        }
    }

    if(!object)
    {
        ctx.Return(nullptr);
        return;
    }
    js::IResource* resource = ctx.GetResource();
    js::ScriptObject* scriptObject = resource->GetOrCreateScriptObject(ctx.GetContext(), object);
    if(!scriptObject)
    {
        ctx.Return(nullptr);
        return;
    }

    js::Function func = resource->GetBindingExport<v8::Function>("entity:addEntityToAll");
    if(!ctx.Check(func.IsValid(), "INTERNAL ERROR: Failed to get entity:addEntityToAll function")) return;
    func.Call(scriptObject->Get());

    ctx.Return(scriptObject->Get());
}

// clang-format off
// Used to provide C++ functions to the JS bindings
static js::Module cppBindingsModule("cppBindings", [](js::ModuleTemplate& module)
{
    module.StaticFunction("toggleEvent", ToggleEvent);
    module.StaticFunction("setEntityFactory", SetEntityFactory);
    module.StaticFunction("getEntityFactory", GetEntityFactory);

    module.StaticFunction("createEntity", CreateEntity);
});
