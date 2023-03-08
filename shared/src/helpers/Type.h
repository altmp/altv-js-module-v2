#pragma once

#include "v8.h"

namespace js
{
    class IResource;

    enum class Type : uint8_t
    {
        Invalid,
        Undefined,
        Null,
        Boolean,
        Number,
        String,
        Symbol,
        Object,
        Function,
        Array,
        ArrayBuffer,
        SharedArrayBuffer,
        TypedArray,
        DataView,
        Date,
        Promise,
        Map,
        Set,
        BigInt,

        // Custom types
        Vector3,
        Vector2,
        RGBA,
        BaseObject,
    };

    bool IsVector3(v8::Local<v8::Value> value, IResource* resource);
    bool IsVector2(v8::Local<v8::Value> value, IResource* resource);
    bool IsRGBA(v8::Local<v8::Value> value, IResource* resource);
    bool IsBaseObject(v8::Local<v8::Value> value, IResource* resource);

    template<typename T>
    static Type GetType(v8::Local<T> value, js::IResource* resource)
    {
        if(value.IsEmpty()) return Type::Invalid;
        if(value->IsUndefined()) return Type::Undefined;
        if(value->IsNull()) return Type::Null;
        if(value->IsBoolean()) return Type::Boolean;
        if(value->IsNumber()) return Type::Number;
        if(value->IsString()) return Type::String;
        if(value->IsSymbol()) return Type::Symbol;
        if(value->IsObject())
        {
            if(value->IsFunction()) return Type::Function;
            if(value->IsArray()) return Type::Array;
            if(value->IsArrayBuffer()) return Type::ArrayBuffer;
            if(value->IsSharedArrayBuffer()) return Type::SharedArrayBuffer;
            if(value->IsTypedArray()) return Type::TypedArray;
            if(value->IsDataView()) return Type::DataView;
            if(value->IsDate()) return Type::Date;
            if(value->IsPromise()) return Type::Promise;
            if(value->IsMap()) return Type::Map;
            if(value->IsSet()) return Type::Set;
            if(value->IsBigInt()) return Type::BigInt;
            if(IsVector3(value, resource)) return Type::Vector3;
            if(IsVector2(value, resource)) return Type::Vector2;
            if(IsRGBA(value, resource)) return Type::RGBA;
            if(IsBaseObject(value, resource)) return Type::BaseObject;
            return Type::Object;
        }
        return Type::Invalid;
    }

    static std::string TypeToString(Type type)
    {
        switch(type)
        {
            case Type::Undefined: return "Undefined";
            case Type::Null: return "Null";
            case Type::Boolean: return "Boolean";
            case Type::Number: return "Number";
            case Type::String: return "String";
            case Type::Symbol: return "Symbol";
            case Type::Object: return "Object";
            case Type::Function: return "Function";
            case Type::Array: return "Array";
            case Type::ArrayBuffer: return "ArrayBuffer";
            case Type::SharedArrayBuffer: return "SharedArrayBuffer";
            case Type::TypedArray: return "TypedArray";
            case Type::DataView: return "DataView";
            case Type::Date: return "Date";
            case Type::Promise: return "Promise";
            case Type::Map: return "Map";
            case Type::Set: return "Set";
            case Type::BigInt: return "BigInt";
        }
        return "Invalid";
    }
}  // namespace js
