#pragma once

#include <optional>

#include "v8.h"

namespace js
{
    class IResource;

    class IValueBuffer
    {
    public:
        enum class ValueType : uint8_t
        {
            INVALID,
            JS_VALUE,
            ENTITY,
            VECTOR3,
            VECTOR2,
            RGBA,
            QUATERNION,
            BUFFER
        };

    protected:
        IResource* resource = nullptr;

        virtual bool Buffer(void*& data, size_t size) = 0;
        virtual bool Byte(uint8_t& value) = 0;
        virtual bool Bool(bool& value) = 0;
        virtual bool Type(ValueType& value) = 0;
        virtual bool Int32(int32_t& value) = 0;
        virtual bool UInt32(uint32_t& value) = 0;
        virtual bool Int64(int64_t& value) = 0;
        virtual bool UInt64(uint64_t& value) = 0;
        virtual bool Float(float& value) = 0;
        virtual bool Double(double& value) = 0;

        virtual bool JSValue(v8::Local<v8::Value>& value) = 0;
        virtual bool Entity(v8::Local<v8::Value>& value) = 0;
        virtual bool Vector3(v8::Local<v8::Value>& value) = 0;
        virtual bool Vector2(v8::Local<v8::Value>& value) = 0;
        virtual bool RGBA(v8::Local<v8::Value>& value) = 0;
        virtual bool Quaternion(v8::Local<v8::Value>& value) = 0;
        virtual bool JSBuffer(v8::Local<v8::Value>& value) = 0;

        virtual ValueType GetValueType(v8::Local<v8::Value> value) = 0;

    public:
        bool Value(v8::Local<v8::Value>& value);
    };

    class ValueSerializer : public virtual IValueBuffer, public v8::ValueSerializer::Delegate
    {
        v8::ValueSerializer* serializer = nullptr;

        void ThrowDataCloneError(v8::Local<v8::String> message) override;
        v8::Maybe<bool> WriteHostObject(v8::Isolate* isolate, v8::Local<v8::Object> object) override;

        bool Buffer(void*& data, size_t size) override;
        bool Byte(uint8_t& value) override;
        bool Bool(bool& value) override;
        bool Type(ValueType& value) override;
        bool Int32(int32_t& value) override;
        bool UInt32(uint32_t& value) override;
        bool Int64(int64_t& value) override;
        bool UInt64(uint64_t& value) override;
        bool Float(float& value) override;
        bool Double(double& value) override;

        bool JSValue(v8::Local<v8::Value>& value) override;
        bool Entity(v8::Local<v8::Value>& value) override;
        bool Vector3(v8::Local<v8::Value>& value) override;
        bool Vector2(v8::Local<v8::Value>& value) override;
        bool RGBA(v8::Local<v8::Value>& value) override;
        bool Quaternion(v8::Local<v8::Value>& value) override;
        bool JSBuffer(v8::Local<v8::Value>& value) override;

        ValueType GetValueType(v8::Local<v8::Value> value) override;

    public:
        static std::optional<std::pair<uint8_t*, size_t>> Serialize(v8::Local<v8::Value> value, IResource* resource);
    };

    class ValueDeserializer : public virtual IValueBuffer, public v8::ValueDeserializer::Delegate
    {
        v8::ValueDeserializer* deserializer = nullptr;

        v8::MaybeLocal<v8::Object> ReadHostObject(v8::Isolate* isolate) override;

        bool Buffer(void*& data, size_t size) override;
        bool Byte(uint8_t& value) override;
        bool Bool(bool& value) override;
        bool Type(ValueType& value) override;
        bool Int32(int32_t& value) override;
        bool UInt32(uint32_t& value) override;
        bool Int64(int64_t& value) override;
        bool UInt64(uint64_t& value) override;
        bool Float(float& value) override;
        bool Double(double& value) override;

        bool JSValue(v8::Local<v8::Value>& value) override;
        bool Entity(v8::Local<v8::Value>& value) override;
        bool Vector3(v8::Local<v8::Value>& value) override;
        bool Vector2(v8::Local<v8::Value>& value) override;
        bool RGBA(v8::Local<v8::Value>& value) override;
        bool Quaternion(v8::Local<v8::Value>& value) override;
        bool JSBuffer(v8::Local<v8::Value>& value) override;

        ValueType GetValueType(v8::Local<v8::Value> value) override;

        template<typename T>
        bool Read(T& value)
        {
            void* ptr = nullptr;
            if(!deserializer->ReadRawBytes(sizeof(T), (const void**)&ptr)) return false;
            value = *(T*)ptr;
            return true;
        }

    public:
        static std::optional<v8::Local<v8::Value>> Deserialize(uint8_t* bytes, size_t size, IResource* resource);
    };
}  // namespace js
