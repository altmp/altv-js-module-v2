#pragma once

#include <optional>
#include <vector>
#include <unordered_map>

#include "v8.h"
#include "cpp-sdk/SDK.h"

namespace js
{
    class Array;
    class IResource;

    class Object;
    class Array;

    alt::MValue JSToMValue(v8::Local<v8::Value> val, bool allowFunction = true);
    v8::Local<v8::Value> MValueToJS(alt::MValueConst val);
    void MValueArgsToJS(alt::MValueArgs args, Array& argsArray);

    inline v8::Local<v8::String> JSValue(const char* val)
    {
        return v8::String::NewFromUtf8(v8::Isolate::GetCurrent(), val).ToLocalChecked();
    }
    inline v8::Local<v8::String> JSValue(const std::string& val)
    {
        return v8::String::NewFromUtf8(v8::Isolate::GetCurrent(), val.c_str(), v8::NewStringType::kNormal, (int)val.size()).ToLocalChecked();
    }
    inline v8::Local<v8::String> JSValue(const uint16_t* val)
    {
        return v8::String::NewFromTwoByte(v8::Isolate::GetCurrent(), val).ToLocalChecked();
    }
    inline v8::Local<v8::Boolean> JSValue(bool val)
    {
        return v8::Boolean::New(v8::Isolate::GetCurrent(), val);
    }
    inline v8::Local<v8::Number> JSValue(double val)
    {
        return v8::Number::New(v8::Isolate::GetCurrent(), val);
    }
    inline v8::Local<v8::Integer> JSValue(int32_t val)
    {
        return v8::Integer::New(v8::Isolate::GetCurrent(), val);
    }
    inline v8::Local<v8::Integer> JSValue(uint32_t val)
    {
        return v8::Integer::NewFromUnsigned(v8::Isolate::GetCurrent(), val);
    }
    inline v8::Local<v8::BigInt> JSValue(int64_t val)
    {
        return v8::BigInt::New(v8::Isolate::GetCurrent(), val);
    }
    inline v8::Local<v8::BigInt> JSValue(uint64_t val)
    {
        return v8::BigInt::NewFromUnsigned(v8::Isolate::GetCurrent(), val);
    }
    template<class T>
    inline v8::Local<v8::Array> JSValue(const std::vector<T>& arr)
    {
        v8::Isolate* isolate = v8::Isolate::GetCurrent();
        v8::Local<v8::Context> ctx = isolate->GetEnteredOrMicrotaskContext();
        auto jsArr = v8::Array::New(isolate, arr.size());
        for(int i = 0; i < arr.size(); i++)
        {
            jsArr->Set(ctx, i, JSValue(arr[i]));
        }
        return jsArr;
    }
    template<class T>
    inline v8::Local<v8::Array> JSValue(const std::unordered_map<std::string, T>& map)
    {
        v8::Isolate* isolate = v8::Isolate::GetCurrent();
        v8::Local<v8::Context> ctx = isolate->GetEnteredOrMicrotaskContext();
        auto jsObj = v8::Object::New(isolate);
        for(auto& [key, val] : map)
        {
            jsObj->Set(ctx, JSValue(key), JSValue(val));
        }
        return jsObj;
    }
    inline v8::Local<v8::Primitive> JSValue(std::nullptr_t val)
    {
        return v8::Null(v8::Isolate::GetCurrent());
    }
    template<class T>
    inline v8::Local<T> JSValue(v8::Local<T> val)
    {
        return val;
    }
    inline v8::Local<v8::Value> JSValue(alt::MValueConst mvalue)
    {
        return MValueToJS(mvalue);
    }
    inline v8::Local<v8::Value> JSValue(alt::MValue mvalue)
    {
        return MValueToJS(mvalue);
    }
    v8::Local<v8::Value> JSValue(alt::IBaseObject* object);
    v8::Local<v8::Value> JSValue(alt::Vector2f vec);
    v8::Local<v8::Value> JSValue(alt::Vector3f vec);
    v8::Local<v8::Value> JSValue(alt::Position pos);
    v8::Local<v8::Value> JSValue(alt::Rotation rot);
    v8::Local<v8::Value> JSValue(alt::RGBA rgba);
    v8::Local<v8::Value> JSValue(const js::Object& jsObj);
    v8::Local<v8::Value> JSValue(const js::Array& jsArr);

    template<typename T, typename = void>
    constexpr bool IsJSValueConvertible = false;
    template<typename T>
    constexpr bool IsJSValueConvertible<T, std::void_t<decltype(JSValue(std::declval<T>()))>> = true;

    // Converts a JS value to a C++ value
    inline std::string CppValue(v8::Local<v8::Name> val)
    {
        return *v8::String::Utf8Value(v8::Isolate::GetCurrent(), val);
    }
    inline std::string CppValue(v8::Local<v8::Symbol> val)
    {
        return *v8::String::Utf8Value(v8::Isolate::GetCurrent(), val);
    }
    inline std::string CppValue(v8::Local<v8::String> val)
    {
        return *v8::String::Utf8Value(v8::Isolate::GetCurrent(), val);
    }
    inline double CppValue(v8::Local<v8::Number> val)
    {
        return val->Value();
    }
    inline int64_t CppValue(v8::Local<v8::Integer> val)
    {
        return val->Value();
    }
    inline uint32_t CppValue(v8::Local<v8::Uint32> val)
    {
        return val->Value();
    }
    inline int32_t CppValue(v8::Local<v8::Int32> val)
    {
        return val->Value();
    }
    inline uint64_t CppValue(v8::Local<v8::BigInt> val)
    {
        return val->Uint64Value();
    }
    inline bool CppValue(v8::Local<v8::Boolean> val)
    {
        return val->Value();
    }
    template<typename T, int Size = 0>
    std::optional<std::vector<T>> CppValue(v8::Local<v8::Array> arr)
    {
        v8::Isolate* isolate = v8::Isolate::GetCurrent();
        v8::Local<v8::Context> ctx = isolate->GetEnteredOrMicrotaskContext();
        uint32_t size = arr->Length();
        if(Size != 0 && size != Size) return std::nullopt;

        std::vector<T> result;
        result.reserve(size);
        for(uint32_t i = 0; i < size; i++)
        {
            v8::MaybeLocal<v8::Value> maybeVal = arr->Get(ctx, i);
            v8::Local<v8::Value> val;
            if(!maybeVal.ToLocal(&val)) return std::nullopt;

            if constexpr(std::is_same_v<T, v8::Local<v8::Value>>) result.push_back(val);
            else if constexpr(std::is_integral_v<T> || std::is_floating_point_v<T>)
            {
                if(!val->IsNumber()) return std::nullopt;
                result.push_back((T)val->ToNumber(ctx).ToLocalChecked()->Value());
            }
            else if constexpr(std::is_same_v<T, std::string>)
            {
                if(!val->IsString()) return std::nullopt;
                result.push_back(*v8::String::Utf8Value(isolate, val->ToString(ctx).ToLocalChecked()));
            }
            else if constexpr(std::is_same_v<T, bool>)
            {
                if(!val->IsBoolean()) return std::nullopt;
                result.push_back(val->ToBoolean(isolate)->Value());
            }
            else if constexpr(std::is_same_v<T, std::vector<typename T::value_type>>)
            {
                using VecType = typename T::value_type;
                if(!val->IsArray()) return std::nullopt;
                std::optional<std::vector<VecType>> vec = CppValue<VecType>(val.As<v8::Array>());
                if(!vec.has_value()) return std::nullopt;
                result.push_back(vec.value());
            }
            else if constexpr(std::is_same_v<T, std::unordered_map<typename T::value_type::first_type, typename T::value_type::second_type>>)
            {
                using MapType = typename T::value_type;
                if constexpr(!std::is_same_v<std::string, typename MapType::first_type>) return std::nullopt;
                if(!val->IsObject()) return std::nullopt;
                std::optional<std::unordered_map<std::string, typename MapType::second_type>> vec = CppValue<typename MapType::second_type>(val.As<v8::Object>());
                if(!vec.has_value()) return std::nullopt;
                result.push_back(vec.value());
            }
            else
                static_assert("Invalid type specified to CppValue<v8::Array>");
        }
        return result;
    }
    template<typename T>
    std::optional<std::unordered_map<std::string, T>> CppValue(v8::Local<v8::Object> obj)
    {
        v8::Isolate* isolate = v8::Isolate::GetCurrent();
        v8::Local<v8::Context> ctx = isolate->GetEnteredOrMicrotaskContext();
        std::optional<std::vector<std::string>> keys = CppValue<std::string>(obj->GetOwnPropertyNames(ctx).ToLocalChecked());
        if(!keys.has_value()) return std::nullopt;

        std::unordered_map<std::string, T> result;
        for(uint32_t i = 0; i < keys->size(); i++)
        {
            const std::string& key = keys->at(i);
            v8::MaybeLocal<v8::Value> maybeVal = obj->Get(ctx, JSValue(key));
            v8::Local<v8::Value> val;
            if(!maybeVal.ToLocal(&val)) return std::nullopt;

            if constexpr(std::is_same_v<T, v8::Local<v8::Value>>) result.insert({ key, val });
            else if constexpr(std::is_integral_v<T> || std::is_floating_point_v<T>)
            {
                if(!val->IsNumber()) return std::nullopt;
                result.insert({ key, (T)val->ToNumber(ctx).ToLocalChecked()->Value() });
            }
            else if constexpr(std::is_same_v<T, std::string>)
            {
                if(!val->IsString()) return std::nullopt;
                result.insert({ key, *v8::String::Utf8Value(isolate, val->ToString(ctx).ToLocalChecked()) });
            }
            else if constexpr(std::is_same_v<T, bool>)
            {
                if(!val->IsBoolean()) return std::nullopt;
                result.insert({ key, val->ToBoolean(isolate)->Value() });
            }
            else if constexpr(std::is_same_v<T, std::vector<typename T::value_type>>)
            {
                using VecType = typename T::value_type;
                if(!val->IsArray()) return std::nullopt;
                std::optional<std::vector<VecType>> vec = CppValue<VecType>(val.As<v8::Array>());
                if(!vec.has_value()) return std::nullopt;
                result.insert({ key, vec.value() });
            }
            else if constexpr(std::is_same_v<T, std::unordered_map<typename T::value_type::first_type, typename T::value_type::second_type>>)
            {
                using MapType = typename T::value_type;
                if constexpr(!std::is_same_v<std::string, typename MapType::first_type>) return std::nullopt;
                if(!val->IsObject()) return std::nullopt;
                std::optional<std::unordered_map<std::string, typename MapType::second_type>> vec = CppValue<typename MapType::second_type>(val.As<v8::Object>());
                if(!vec.has_value()) return std::nullopt;
                result.insert({ key, vec.value() });
            }
            else
                static_assert("Invalid type specified to CppValue<v8::Object>");
        }
        return result;
    }
    static std::optional<alt::Vector3f> ToVector3(v8::Local<v8::Value> val)
    {
        if(!val->IsObject()) return std::nullopt;

        v8::Local<v8::Object> obj = val.As<v8::Object>();
        v8::Local<v8::Context> ctx = obj->CreationContext();
        v8::Isolate* isolate = ctx->GetIsolate();

        v8::Local<v8::Value> xVal;
        v8::Local<v8::Value> yVal;
        v8::Local<v8::Value> zVal;

        if(!obj->Get(ctx, js::JSValue("x")).ToLocal(&xVal)) return std::nullopt;
        if(!obj->Get(ctx, js::JSValue("y")).ToLocal(&yVal)) return std::nullopt;
        if(!obj->Get(ctx, js::JSValue("z")).ToLocal(&zVal)) return std::nullopt;

        if(!xVal->IsNumber() || !yVal->IsNumber() || !zVal->IsNumber()) return std::nullopt;

        return alt::Vector3f(xVal->NumberValue(ctx).ToChecked(), yVal->NumberValue(ctx).ToChecked(), zVal->NumberValue(ctx).ToChecked());
    }
    static std::optional<alt::Vector2f> ToVector2(v8::Local<v8::Value> val)
    {
        if(!val->IsObject()) return std::nullopt;

        v8::Local<v8::Object> obj = val.As<v8::Object>();
        v8::Local<v8::Context> ctx = obj->CreationContext();
        v8::Isolate* isolate = ctx->GetIsolate();

        v8::Local<v8::Value> xVal;
        v8::Local<v8::Value> yVal;

        if(!obj->Get(ctx, js::JSValue("x")).ToLocal(&xVal)) return std::nullopt;
        if(!obj->Get(ctx, js::JSValue("y")).ToLocal(&yVal)) return std::nullopt;

        if(!xVal->IsNumber() || !yVal->IsNumber()) return std::nullopt;

        return alt::Vector2f(xVal->NumberValue(ctx).ToChecked(), yVal->NumberValue(ctx).ToChecked());
    }
    static std::optional<alt::RGBA> ToRGBA(v8::Local<v8::Value> val)
    {
        if(!val->IsObject()) return std::nullopt;

        v8::Local<v8::Object> obj = val.As<v8::Object>();
        v8::Local<v8::Context> ctx = obj->CreationContext();
        v8::Isolate* isolate = ctx->GetIsolate();

        v8::Local<v8::Value> rVal;
        v8::Local<v8::Value> gVal;
        v8::Local<v8::Value> bVal;
        v8::Local<v8::Value> aVal;

        if(!obj->Get(ctx, js::JSValue("r")).ToLocal(&rVal)) return std::nullopt;
        if(!obj->Get(ctx, js::JSValue("g")).ToLocal(&gVal)) return std::nullopt;
        if(!obj->Get(ctx, js::JSValue("b")).ToLocal(&bVal)) return std::nullopt;
        if(!obj->Get(ctx, js::JSValue("a")).ToLocal(&aVal)) return std::nullopt;

        if(!rVal->IsNumber() || !gVal->IsNumber() || !bVal->IsNumber() || !aVal->IsNumber()) return std::nullopt;

        return alt::RGBA(rVal->NumberValue(ctx).ToChecked(), gVal->NumberValue(ctx).ToChecked(), bVal->NumberValue(ctx).ToChecked(), aVal->NumberValue(ctx).ToChecked());
    }
    std::optional<alt::IBaseObject*> ToBaseObject(v8::Local<v8::Value> val);
    template<typename T>
    std::optional<T> CppValue(v8::Local<v8::Value> val)
    {
        if constexpr(std::is_same_v<T, v8::Local<v8::Value>>) return val;
        else if constexpr(std::is_integral_v<T> || std::is_floating_point_v<T>)
        {
            return (T)val->ToNumber(v8::Isolate::GetCurrent()->GetEnteredOrMicrotaskContext()).ToLocalChecked()->Value();
        }
        else if constexpr(std::is_same_v<T, std::string>)
        {
            return *v8::String::Utf8Value(v8::Isolate::GetCurrent(), val->ToString(v8::Isolate::GetCurrent()->GetEnteredOrMicrotaskContext()).ToLocalChecked());
        }
        else if constexpr(std::is_same_v<T, bool>)
        {
            return val->ToBoolean(v8::Isolate::GetCurrent())->Value();
        }
        else if constexpr(std::is_same_v<T, alt::MValue> || std::is_same_v<T, alt::MValueConst>)
        {
            alt::MValue mvalue = js::JSToMValue(val);
            if(!mvalue) return std::nullopt;
            return mvalue;
        }
        else if constexpr(std::is_same_v<T, alt::Vector3f> || std::is_same_v<T, alt::Position> || std::is_same_v<T, alt::Rotation>)
        {
            return ToVector3(val);
        }
        else if constexpr(std::is_same_v<T, alt::Vector2f>)
        {
            return ToVector2(val);
        }
        else if constexpr(std::is_same_v<T, alt::RGBA>)
        {
            return ToRGBA(val);
        }
        else if constexpr(std::is_same_v<T, alt::IBaseObject*> || std::is_base_of_v<alt::IBaseObject, std::remove_pointer_t<T>>)
        {
            std::optional<alt::IBaseObject*> obj = ToBaseObject(val);
            if(!obj.has_value()) return std::nullopt;
            return std::optional<T>(dynamic_cast<T>(obj.value()));
        }
        else if constexpr(std::is_same_v<T, js::Object>)
        {
            return js::Object(val.As<v8::Object>());
        }
        else if constexpr(std::is_same_v<T, js::Array>)
        {
            return js::Array(val.As<v8::Array>());
        }
        else if constexpr(std::is_same_v<T, std::vector<typename T::value_type>>)
        {
            if(!val->IsArray()) return std::nullopt;
            return CppValue<typename T::value_type>(val.As<v8::Array>());
        }
        else if constexpr(std::is_same_v<T, std::unordered_map<typename T::value_type::first_type, typename T::value_type::second_type>>)
        {
            if(!val->IsObject()) return std::nullopt;
            return CppValue<typename T::value_type>(val.As<v8::Object>());
        }
        else
            static_assert("Invalid type specified to CppValue<v8::Value>");
    }

    IResource* GetCurrentResource(v8::Isolate* isolate = nullptr);
}  // namespace js
