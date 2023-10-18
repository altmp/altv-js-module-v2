#pragma once

#include "v8.h"
#include "helpers/JS.h"

#include <array>

namespace js
{
    enum class BindingExport : uint8_t
    {
        // Functions
        ON_EVENT,
        TICK,
        ADD_ENTITY_TO_ALL,
        LOG_INSPECT,
        HASH,

        // Classes
        VECTOR3_CLASS,
        VECTOR2_CLASS,
        RGBA_CLASS,
        QUATERNION_CLASS,

        SIZE,
    };

    class IBindingExportHandler
    {
        std::array<Persistent<v8::Value>, (size_t)BindingExport::SIZE> bindingExports;

    protected:
        void Reset()
        {
            bindingExports.fill(js::Persistent<v8::Value>{});
        }

    public:
        void SetBindingExport(BindingExport export_, v8::Local<v8::Value> val)
        {
            v8::Isolate* isolate = v8::Isolate::GetCurrent();
            bindingExports[(size_t)export_] = Persistent<v8::Value>(isolate, val);
        }
        bool HasBindingExport(BindingExport export_)
        {
            return !bindingExports[(size_t)export_].IsEmpty();
        }

        template<typename T = v8::Value>
        v8::Local<T> GetBindingExport(BindingExport export_)
        {
            static_assert(std::is_base_of_v<v8::Value, T>, "T must inherit from v8::Value");
            v8::Isolate* isolate = v8::Isolate::GetCurrent();
            return bindingExports[(size_t)export_].Get(isolate).As<T>();
        }
    };
}  // namespace js
