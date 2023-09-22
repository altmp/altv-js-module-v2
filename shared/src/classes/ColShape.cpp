#include "Class.h"
#include "cpp-sdk/ICore.h"

static void RadiusGetter(js::LazyPropertyContext& ctx)
{
    if (!ctx.CheckThis()) return;
    alt::IColShape* colShape = ctx.GetThisObject<alt::IColShape>();

    if (colShape->GetColshapeType() == alt::IColShape::ColShapeType::SPHERE)
    {
        auto* sphere = dynamic_cast<alt::IColShapeSphere*>(colShape);
        ctx.Return(sphere->GetRadius());
    }
    else if (colShape->GetColshapeType() == alt::IColShape::ColShapeType::CYLINDER)
    {
        auto* cylinder = dynamic_cast<alt::IColShapeCylinder*>(colShape);
        ctx.Return(cylinder->GetRadius());
    }
    else if (colShape->GetColshapeType() == alt::IColShape::ColShapeType::CIRCLE)
    {
        auto* circle = dynamic_cast<alt::IColShapeCircle*>(colShape);
        ctx.Return(circle->GetRadius());
    }
}

static void HeightGetter(js::LazyPropertyContext& ctx)
{
    if (!ctx.CheckThis()) return;
    alt::IColShape* colShape = ctx.GetThisObject<alt::IColShape>();

    if (colShape->GetColshapeType() == alt::IColShape::ColShapeType::CYLINDER)
    {
        auto* cylinder = dynamic_cast<alt::IColShapeCylinder*>(colShape);
        ctx.Return(cylinder->GetHeight());
    }
}

static void MinGetter(js::LazyPropertyContext& ctx)
{
    if (!ctx.CheckThis()) return;
    alt::IColShape* colShape = ctx.GetThisObject<alt::IColShape>();

    if (colShape->GetColshapeType() == alt::IColShape::ColShapeType::CUBOID)
    {
        auto* cuboid = dynamic_cast<alt::IColShapeCuboid*>(colShape);
        ctx.Return(cuboid->GetMin());
    }
    else if (colShape->GetColshapeType() == alt::IColShape::ColShapeType::RECT)
    {
        auto* rect = dynamic_cast<alt::IColShapeRect*>(colShape);
        ctx.Return(rect->GetMin());
    }
}

static void MaxGetter(js::LazyPropertyContext& ctx)
{
    if (!ctx.CheckThis()) return;
    alt::IColShape* colShape = ctx.GetThisObject<alt::IColShape>();

    if (colShape->GetColshapeType() == alt::IColShape::ColShapeType::CUBOID)
    {
        auto* cuboid = dynamic_cast<alt::IColShapeCuboid*>(colShape);
        ctx.Return(cuboid->GetMax());
    }
    else if (colShape->GetColshapeType() == alt::IColShape::ColShapeType::RECT)
    {
        auto* rect = dynamic_cast<alt::IColShapeRect*>(colShape);
        ctx.Return(rect->GetMax());
    }
}

static void MinZGetter(js::LazyPropertyContext& ctx)
{
    if (!ctx.CheckThis()) return;
    alt::IColShape* colShape = ctx.GetThisObject<alt::IColShape>();

    if (colShape->GetColshapeType() == alt::IColShape::ColShapeType::POLYGON)
    {
        auto* poly = dynamic_cast<alt::IColShapePoly*>(colShape);
        ctx.Return(poly->GetMinZ());
    }
}

static void MaxZGetter(js::LazyPropertyContext& ctx)
{
    if (!ctx.CheckThis()) return;
    alt::IColShape* colShape = ctx.GetThisObject<alt::IColShape>();

    if (colShape->GetColshapeType() == alt::IColShape::ColShapeType::POLYGON)
    {
        auto* poly = dynamic_cast<alt::IColShapePoly*>(colShape);
        ctx.Return(poly->GetMaxZ());
    }
}

static void PointsGetter(js::LazyPropertyContext& ctx)
{
    if (!ctx.CheckThis()) return;
    alt::IColShape* colShape = ctx.GetThisObject<alt::IColShape>();

    if (colShape->GetColshapeType() == alt::IColShape::ColShapeType::POLYGON)
    {
        auto* poly = dynamic_cast<alt::IColShapePoly*>(colShape);
        ctx.Return(poly->GetPoints());
    }
}

// clang-format off
extern js::Class worldObjectClass;
extern js::Class colShapeClass("ColShape", &worldObjectClass, nullptr, [](js::ClassTemplate& tpl)
{
    tpl.BindToType(alt::IBaseObject::Type::COLSHAPE);

    tpl.LazyProperty<&alt::IColShape::GetColshapeType>("colShapeType");
    tpl.Property<&alt::IColShape::IsPlayersOnly, &alt::IColShape::SetPlayersOnly>("playersOnly");

    // NOTE (xLuxy): This is a temporary workaround for colShape getters until SDK supports multiple colshape BaseObject types
    tpl.LazyProperty("radius", RadiusGetter);
    tpl.LazyProperty("height", HeightGetter);
    tpl.LazyProperty("min", MinGetter);
    tpl.LazyProperty("max", MaxGetter);
    tpl.LazyProperty("minZ", MinZGetter);
    tpl.LazyProperty("maxZ", MaxZGetter);
    tpl.LazyProperty("points", PointsGetter);

    tpl.Method<&alt::IColShape::IsEntityIn>("isEntityIn");
    tpl.Method<&alt::IColShape::IsEntityIdIn>("isEntityIdIn");
    tpl.Method<&alt::IColShape::IsPointIn>("isPointIn");

    tpl.GetByID<alt::IBaseObject::Type::COLSHAPE>();

#ifdef ALT_CLIENT_API
    tpl.GetByRemoteID<alt::IBaseObject::Type::COLSHAPE>();
#endif
});
