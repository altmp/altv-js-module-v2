#include "Module.h"
#include "Namespace.h"

// clang-format off
extern js::Class playerClass, vehicleClass, colShapeClass, checkpointClass;
extern js::Namespace eventsNamespace;
static js::Module altModule("alt", "alt-shared", { &playerClass, &vehicleClass, &colShapeClass, &checkpointClass }, [](js::ModuleTemplate& module)
{
    module.StaticProperty("isClient", false);
    module.StaticProperty("isServer", true);

    module.Namespace(eventsNamespace);

    // ColShapes namespaces
    module.Namespace("ColshapeSphere");
    module.Namespace("ColshapeCylinder");
    module.Namespace("ColshapeCircle");
    module.Namespace("ColshapeCuboid");
    module.Namespace("ColshapeRectangle");
    module.Namespace("ColshapePolygon");
});
