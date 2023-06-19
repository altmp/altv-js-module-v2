#include "Class.h"
#include "cpp-sdk/ICore.h"

// clang-format off
extern js::Class sharedNetworkObjectClass;
extern js::Class networkObjectClass("NetworkObject", &sharedNetworkObjectClass, nullptr, [](js::ClassTemplate& tpl)
{
    tpl.BindToType(alt::IBaseObject::Type::NETWORK_OBJECT);

    tpl.GetByID<alt::IBaseObject::Type::NETWORK_OBJECT>();
});
