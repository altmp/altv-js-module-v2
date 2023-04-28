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

    static constexpr int64_t JS_MAX_SAFE_INTEGER = 9007199254740991;
    static constexpr int64_t JS_MIN_SAFE_INTEGER = JS_MAX_SAFE_INTEGER * -1;

    alt::MValue JSToMValue(v8::Local<v8::Value> val, bool allowFunction = true);
    v8::Local<v8::Value> MValueToJS(alt::MValueConst val);
    void MValueArgsToJS(alt::MValueArgs args, Array& argsArray);
    v8::Local<v8::Value> ConfigValueToJS(Config::Value::ValuePtr val);

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
    inline v8::Local<v8::Value> JSValue(int64_t val)
    {
        if(val >= JS_MIN_SAFE_INTEGER && val <= JS_MAX_SAFE_INTEGER) return JSValue((double)val);
        return v8::BigInt::New(v8::Isolate::GetCurrent(), val);
    }
    inline v8::Local<v8::Value> JSValue(uint64_t val)
    {
        if(val >= JS_MIN_SAFE_INTEGER && val <= JS_MAX_SAFE_INTEGER) return JSValue((double)val);
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
    v8::Local<v8::Value> JSValue(alt::Quaternion quaternion);
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
    static std::optional<alt::Quaternion> ToQuaternion(v8::Local<v8::Value> val)
    {
        if(!val->IsObject()) return std::nullopt;

        v8::Local<v8::Object> obj = val.As<v8::Object>();
        v8::Local<v8::Context> ctx = obj->CreationContext();
        v8::Isolate* isolate = ctx->GetIsolate();

        v8::Local<v8::Value> xVal;
        v8::Local<v8::Value> yVal;
        v8::Local<v8::Value> zVal;
        v8::Local<v8::Value> wVal;

        if(!obj->Get(ctx, js::JSValue("x")).ToLocal(&xVal)) return std::nullopt;
        if(!obj->Get(ctx, js::JSValue("y")).ToLocal(&yVal)) return std::nullopt;
        if(!obj->Get(ctx, js::JSValue("z")).ToLocal(&zVal)) return std::nullopt;
        if(!obj->Get(ctx, js::JSValue("w")).ToLocal(&wVal)) return std::nullopt;

        if(!xVal->IsNumber() || !yVal->IsNumber() || !zVal->IsNumber() || !wVal->IsNumber()) return std::nullopt;

        return alt::Quaternion(xVal->NumberValue(ctx).ToChecked(), yVal->NumberValue(ctx).ToChecked(), zVal->NumberValue(ctx).ToChecked(), wVal->NumberValue(ctx).ToChecked());
    }
    std::optional<alt::IBaseObject*> ToBaseObject(v8::Local<v8::Value> val);

    // https://stackoverflow.com/a/16337657/19498259
    template<typename>
    struct IsStdVector : std::false_type
    {
    };
    template<typename T, typename A>
    struct IsStdVector<std::vector<T, A>> : std::true_type
    {
    };
    template<typename>
    struct IsStdUnorderedMap : std::false_type
    {
    };
    template<typename T, typename A>
    struct IsStdUnorderedMap<std::unordered_map<T, A>> : std::true_type
    {
    };

    template<typename T>
    std::optional<T> CppValue(v8::Local<v8::Value> val)
    {
        if constexpr(std::is_same_v<T, v8::Local<v8::Value>>) return val;
        else if constexpr(std::is_same_v<T, int64_t> || std::is_same_v<T, uint64_t>)
        {
            constexpr bool isSigned = std::is_same_v<T, int64_t>;
            v8::Local<v8::BigInt> bigInt = val->ToBigInt(v8::Isolate::GetCurrent()->GetEnteredOrMicrotaskContext()).ToLocalChecked();
            if constexpr(isSigned) return bigInt->Int64Value();
            else
                return bigInt->Uint64Value();
        }
        else if constexpr(std::is_integral_v<T> || std::is_floating_point_v<T>)
        {
            if(val->IsNull()) return std::nullopt;
            double value = val->NumberValue(v8::Isolate::GetCurrent()->GetEnteredOrMicrotaskContext()).ToChecked();
            if(std::isnan(value)) return std::nullopt;
            return (T)value;
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
        else if constexpr(std::is_same_v<T, alt::Quaternion>)
        {
            return ToQuaternion(val);
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
        else if constexpr(IsStdVector<T>::value)
        {
            if(!val->IsArray()) return std::nullopt;
            v8::Local<v8::Context> context = v8::Isolate::GetCurrent()->GetEnteredOrMicrotaskContext();
            std::vector<typename T::value_type> vec;
            v8::Local<v8::Array> arr = val.As<v8::Array>();
            vec.reserve(arr->Length());
            for(uint32_t i = 0; i < arr->Length(); i++)
            {
                auto maybeVal = arr->Get(context, i);
                v8::Local<v8::Value> val;
                if(!maybeVal.ToLocal(&val)) continue;
                std::optional<typename T::value_type> value = CppValue<typename T::value_type>(val);
                if(!value.has_value()) continue;
                vec.push_back(value.value());
            }
            return vec;
        }
        else if constexpr(IsStdUnorderedMap<T>::value)
        {
            if(!val->IsObject()) return std::nullopt;
            v8::Local<v8::Context> context = v8::Isolate::GetCurrent()->GetEnteredOrMicrotaskContext();
            std::unordered_map<std::string, typename T::value_type::second_type> map;
            v8::Local<v8::Object> obj = val.As<v8::Object>();
            auto maybeKeys = obj->GetOwnPropertyNames(context);
            v8::Local<v8::Array> keysArr;
            if(!maybeKeys.ToLocal(&keysArr)) return std::nullopt;
            std::optional<std::vector<std::string>> keysOpt = CppValue<std::vector<std::string>>(keysArr);
            if(!keysOpt.has_value()) return std::nullopt;
            const std::vector<std::string>& keys = keysOpt.value();
            for(std::string& key : keys)
            {
                auto maybeVal = obj->Get(context, js::JSValue(key));
                v8::Local<v8::Value> val;
                if(!maybeVal.ToLocal(&val)) continue;
                std::optional<typename T::value_type::second_type> value = CppValue<typename T::value_type::second_type>(val);
                if(!value.has_value()) continue;
                map.insert({ key, value.value() });
            }
            return map;
        }

        return std::nullopt;
    }

    IResource* GetCurrentResource(v8::Isolate* isolate = nullptr);
}  // namespace js
