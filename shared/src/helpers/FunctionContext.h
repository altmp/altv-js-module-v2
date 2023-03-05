#pragma once

#include "v8.h"

namespace js
{
    class FunctionContext
    {
        v8::FunctionCallbackInfo<v8::Value> info;

    public:
        FunctionContext() = delete;
        FunctionContext(const v8::FunctionCallbackInfo<v8::Value>& _info) : info(_info) {}
    };
}  // namespace js
