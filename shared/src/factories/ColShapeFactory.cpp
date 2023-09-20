#include "FactoryHandler.h"
#include "interfaces/IResource.h"

// clang-format off
static js::FactoryHandler colShapeFactory(alt::IBaseObject::Type::COLSHAPE, [](js::Object& args) -> alt::IBaseObject* {
    alt::IColShape::ColShapeType colShapeType;
    if(!args.Get("colShapeType", colShapeType)) return nullptr;

    switch(colShapeType)
    {
        case alt::IColShape::ColShapeType::SPHERE:
        {
            alt::Vector3f pos;
            float radius;

            if(!args.Get("pos", pos)) return nullptr;
            if(!args.Get("radius", radius)) return nullptr;

            return alt::ICore::Instance().CreateColShapeSphere(pos, radius);
        }

        case alt::IColShape::ColShapeType::CYLINDER:
        {
            alt::Vector3f pos;
            float radius, height;

            if(!args.Get("pos", pos)) return nullptr;
            if(!args.Get("radius", radius)) return nullptr;
            if(!args.Get("height", height)) return nullptr;

            return alt::ICore::Instance().CreateColShapeCylinder(pos, radius, height);
        }

        case alt::IColShape::ColShapeType::CIRCLE:
        {
            alt::Vector2f pos;
            float radius;

            if(!args.Get("pos", pos)) return nullptr;
            if(!args.Get("radius", radius)) return nullptr;

            return alt::ICore::Instance().CreateColShapeCircle(alt::Vector3f(pos[0], pos[1], 0), radius);
        }

        case alt::IColShape::ColShapeType::CUBOID:
        {
            alt::Vector3f pos1, pos2;

            if(!args.Get("pos1", pos1)) return nullptr;
            if(!args.Get("pos2", pos2)) return nullptr;

            return alt::ICore::Instance().CreateColShapeCube(pos1, pos2);
        }

        case alt::IColShape::ColShapeType::RECT:
        {
            float x1, y1, x2, y2;

            if(!args.Get("x1", x1)) return nullptr;
            if(!args.Get("y1", y1)) return nullptr;
            if(!args.Get("x2", x2)) return nullptr;
            if(!args.Get("y2", y2)) return nullptr;

            return alt::ICore::Instance().CreateColShapeRectangle(x1, y1, x2, y2, 0);
        }

        case alt::IColShape::ColShapeType::POLYGON:
        {
            float minZ, maxZ;
            std::vector<alt::Vector2f> points;

            if(!args.Get("minZ", minZ)) return nullptr;
            if(!args.Get("maxZ", maxZ)) return nullptr;
            if(!args.Get("points", points)) return nullptr;

            return alt::ICore::Instance().CreateColShapePolygon(minZ, maxZ, points);
        }
    }

    js::Throw("Invalid ColShape type");
    return nullptr;
});
