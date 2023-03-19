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

        case alt::IBaseObject::Type::COLSHAPE:
        {
            alt::IColShape::ColShapeType colShapeType;
            if(!args.Get("colShapeType", colShapeType)) return;

            switch(colShapeType)
            {
                case alt::IColShape::ColShapeType::SPHERE:
                {
                    alt::Vector3f pos;
                    float radius;

                    if(!args.Get("pos", pos)) return;
                    if(!args.Get("radius", radius)) return;

                    object = alt::ICore::Instance().CreateColShapeSphere(pos, radius);
                    break;
                }

                case alt::IColShape::ColShapeType::CYLINDER:
                {
                    alt::Vector3f pos;
                    float radius, height;

                    if(!args.Get("pos", pos)) return;
                    if(!args.Get("radius", radius)) return;
                    if(!args.Get("height", height)) return;

                    object = alt::ICore::Instance().CreateColShapeCylinder(pos, radius, height);
                    break;
                }

                case alt::IColShape::ColShapeType::CIRCLE:
                {
                    alt::Vector3f pos;
                    float radius;

                    if(!args.Get("pos", pos)) return;
                    if(!args.Get("radius", radius)) return;

                    object = alt::ICore::Instance().CreateColShapeCircle(pos, radius);
                    break;
                }

                case alt::IColShape::ColShapeType::CUBOID:
                {
                    alt::Vector3f pos1, pos2;

                    if(!args.Get("pos1", pos1)) return;
                    if(!args.Get("pos2", pos2)) return;

                    object = alt::ICore::Instance().CreateColShapeCube(pos1, pos2);
                    break;
                }

                case alt::IColShape::ColShapeType::RECT:
                {
                    float x1, y1, x2, y2;

                    if(!args.Get("x1", x1)) return;
                    if(!args.Get("y1", y1)) return;
                    if(!args.Get("x2", x2)) return;
                    if(!args.Get("y2", y2)) return;

                    std::cout << "x1: " << x1 << std::endl;

                    object = alt::ICore::Instance().CreateColShapeRectangle(x1, y1, x2, y2, 0);
                    break;
                }

                case alt::IColShape::ColShapeType::CHECKPOINT_CYLINDER:
                {
                    uint8_t type;
                    alt::Vector3f pos;
                    float radius, height;
                    alt::RGBA color;

                    if(!args.Get("type", type)) return;
                    if(!args.Get("pos", pos)) return;
                    if(!args.Get("radius", radius)) return;
                    if(!args.Get("height", height)) return;
                    if(!args.Get("color", color)) return;

                    object = alt::ICore::Instance().CreateCheckpoint(type, pos, radius, height, color);
                    break;
                }

                case alt::IColShape::ColShapeType::POLYGON:
                {
                    float minZ, maxZ;
                    std::vector<alt::Vector2f> points;

                    if(!args.Get("minZ", minZ)) return;
                    if(!args.Get("maxZ", maxZ)) return;
                    if(!args.Get("points", points)) return;

                    object = alt::ICore::Instance().CreateColShapePolygon(minZ, maxZ, points);
                    break;
                }
            }

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
