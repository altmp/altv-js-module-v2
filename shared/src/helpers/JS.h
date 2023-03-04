#pragma once

#include "v8.h"

namespace js
{
    template<typename T>
    using Persistent = v8::Persistent<T, v8::CopyablePersistentTraits<T>>;
}  // namespace js
