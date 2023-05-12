#pragma once

#include "v8.h"
#include "CallContext.h"

namespace js
{
    using FunctionCallback = void (*)(FunctionContext&);
    using PropertyCallback = void (*)(PropertyContext&);
    using LazyPropertyCallback = void (*)(LazyPropertyContext&);

    using DynamicPropertyGetter = void (*)(DynamicPropertyContext<v8::Value>&);
    using DynamicPropertySetter = void (*)(DynamicPropertyContext<v8::Value>&);
    using DynamicPropertyDeleter = void (*)(DynamicPropertyContext<v8::Boolean>&);
    using DynamicPropertyEnumerator = void (*)(DynamicPropertyContext<v8::Array>&);
}  // namespace js
