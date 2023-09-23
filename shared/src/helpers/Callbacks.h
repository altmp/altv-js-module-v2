#pragma once

#include "v8.h"
#include "CallContext.h"

namespace js::internal
{
    using FunctionCallback = void (*)(FunctionContext&);
    using PropertyCallback = void (*)(PropertyContext&);
    using LazyPropertyCallback = void (*)(LazyPropertyContext&);

    using DynamicPropertyGetter = void (*)(DynamicPropertyGetterContext&);
    using DynamicPropertySetter = void (*)(DynamicPropertySetterContext&);
    using DynamicPropertyDeleter = void (*)(DynamicPropertyDeleterContext&);
    using DynamicPropertyEnumerator = void (*)(DynamicPropertyEnumeratorContext&);
}  // namespace js::internal
