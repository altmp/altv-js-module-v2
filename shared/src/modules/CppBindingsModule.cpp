#include "Module.h"
#include "interfaces/IResource.h"
#include "Logger.h"

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
    if(!ctx.CheckArgCount(1, INT32_MAX)) return;

    alt::IBaseObject::Type type;
    if(!ctx.GetArg(0, type)) return;

    alt::IBaseObject* object = nullptr;
    switch(type)
    {
        case alt::IBaseObject::Type::VEHICLE:
        {
            uint32_t model;
            if(!ctx.GetArg(1, model)) return;
            alt::Vector3f pos;
            if(!ctx.GetArg(2, pos)) return;
            alt::Vector3f rot;
            if(!ctx.GetArg(3, rot)) return;
            object = alt::ICore::Instance().CreateVehicle(model, pos, rot);
            break;
        }
    }

    js::IResource* resource = ctx.GetResource();
    js::ScriptObject* scriptObject = resource->GetOrCreateScriptObject(ctx.GetContext(), object);
    if(!scriptObject)
    {
        ctx.Return(nullptr);
        return;
    }

    js::Function func = resource->GetBindingExport<v8::Function>("entity:addEntityToAll");
    if(func.Get().IsEmpty())
    {
        ctx.Return(nullptr);
        return;
    }
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
