#pragma once

#include "v8.h"

namespace js
{
    class IResource;
    enum class Type : uint8_t
    {
        INVALID,
        UNDEFINED,
        NULL_TYPE,
        BOOLEAN,
        NUMBER,
        STRING,
        SYMBOL,
        OBJECT,
        FUNCTION,
        ARRAY,
        ARRAY_BUFFER,
        SHARED_ARRAY_BUFFER,
        TYPED_ARRAY,
        DATA_VIEW,
        DATE,
        PROMISE,
        MAP,
        SET,
        BIG_INT,

        // Custom types
        VECTOR3,
        VECTOR2,
        RGBA,
        BASE_OBJECT,
    };

    bool IsVector3(v8::Local<v8::Value> value, IResource* resource);
    bool IsVector2(v8::Local<v8::Value> value, IResource* resource);
    bool IsRGBA(v8::Local<v8::Value> value, IResource* resource);
    bool IsBaseObject(v8::Local<v8::Value> value, IResource* resource);

    template<typename T>
    static Type GetType(v8::Local<T> value, js::IResource* resource)
    {
        if(value.IsEmpty()) return Type::INVALID;
        if(value->IsUndefined()) return Type::UNDEFINED;
        if(value->IsNull()) return Type::NULL_TYPE;
        if(value->IsBoolean()) return Type::BOOLEAN;
        if(value->IsNumber()) return Type::NUMBER;
        if(value->IsString()) return Type::STRING;
        if(value->IsSymbol()) return Type::SYMBOL;
        if(value->IsObject())
        {
            if(value->IsFunction()) return Type::FUNCTION;
            if(value->IsArray()) return Type::ARRAY;
            if(value->IsArrayBuffer()) return Type::ARRAY_BUFFER;
            if(value->IsSharedArrayBuffer()) return Type::SHARED_ARRAY_BUFFER;
            if(value->IsTypedArray()) return Type::TYPED_ARRAY;
            if(value->IsDataView()) return Type::DATA_VIEW;
            if(value->IsDate()) return Type::DATE;
            if(value->IsPromise()) return Type::PROMISE;
            if(value->IsMap()) return Type::MAP;
            if(value->IsSet()) return Type::SET;
            if(value->IsBigInt()) return Type::BIG_INT;

            if(IsVector3(value, resource)) return Type::VECTOR3;
            if(IsVector2(value, resource)) return Type::VECTOR2;
            if(IsRGBA(value, resource)) return Type::RGBA;
            if(IsBaseObject(value, resource)) return Type::BASE_OBJECT;

            return Type::OBJECT;
        }
        return Type::INVALID;
    }

    static std::string TypeToString(Type type)
    {
        switch(type)
        {
            case Type::UNDEFINED: return "Undefined";
            case Type::NULL_TYPE: return "Null";
            case Type::BOOLEAN: return "Boolean";
            case Type::NUMBER: return "Number";
            case Type::STRING: return "String";
            case Type::SYMBOL: return "Symbol";
            case Type::OBJECT: return "Object";
            case Type::FUNCTION: return "Function";
            case Type::ARRAY: return "Array";
            case Type::ARRAY_BUFFER: return "ArrayBuffer";
            case Type::SHARED_ARRAY_BUFFER: return "SharedArrayBuffer";
            case Type::TYPED_ARRAY: return "TypedArray";
            case Type::DATA_VIEW: return "DataView";
            case Type::DATE: return "Date";
            case Type::PROMISE: return "Promise";
            case Type::MAP: return "Map";
            case Type::SET: return "Set";
            case Type::BIG_INT: return "BigInt";
            case Type::VECTOR3: return "Vector3";
            case Type::VECTOR2: return "Vector2";
            case Type::RGBA: return "RGBA";
            case Type::BASE_OBJECT: return "BaseObject";
        }
        return "Invalid";
    }
}  // namespace js
