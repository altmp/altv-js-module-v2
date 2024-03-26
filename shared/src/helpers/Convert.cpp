#include "Convert.h"
#include "interfaces/IAltResource.h"
#include "JS.h"
#include "helpers/ValueBuffer.h"

v8::Local<v8::Value> js::JSValue(alt::IBaseObject* object)
{
    v8::Isolate* isolate = v8::Isolate::GetCurrent();
    if(!object) return v8::Null(isolate);
    IResource* resource = GetCurrentResource(isolate);
    if(!resource) return v8::Null(isolate);
    ScriptObject* scriptObject = resource->GetScriptObject(object);
    if(!scriptObject) return v8::Null(isolate);
    return scriptObject->Get();
}

v8::Local<v8::Value> js::JSValue(alt::Vector2f vec)
{
    v8::Isolate* isolate = v8::Isolate::GetCurrent();
    IResource* resource = GetCurrentResource(isolate);
    if(!resource) return v8::Null(isolate);
    return resource->CreateVector2(vec);
}

v8::Local<v8::Value> js::JSValue(alt::Vector3f vec)
{
    v8::Isolate* isolate = v8::Isolate::GetCurrent();
    IResource* resource = GetCurrentResource(isolate);
    if(!resource) return v8::Null(isolate);
    return resource->CreateVector3(vec);
}

v8::Local<v8::Value> js::JSValue(alt::Position pos)
{
    alt::Vector3f vec = pos;
    return JSValue(vec);
}

v8::Local<v8::Value> js::JSValue(alt::Rotation rot)
{
    alt::Vector3f vec = rot;
    return JSValue(vec);
}

v8::Local<v8::Value> js::JSValue(alt::RGBA rgba)
{
    v8::Isolate* isolate = v8::Isolate::GetCurrent();
    IResource* resource = GetCurrentResource(isolate);
    if(!resource) return v8::Null(isolate);
    return resource->CreateRGBA(rgba);
}

v8::Local<v8::Value> js::JSValue(alt::Quaternion quaternion)
{
    v8::Isolate* isolate = v8::Isolate::GetCurrent();
    IResource* resource = GetCurrentResource(isolate);
    if(!resource) return v8::Null(isolate);
    return resource->CreateQuaternion(quaternion);
}

v8::Local<v8::Value> js::JSValue(const js::Object& jsObj)
{
    return jsObj.Get();
}

v8::Local<v8::Value> js::JSValue(const js::Array& jsArr)
{
    return jsArr.Get();
}

v8::Local<v8::Value> js::JSValue(const js::Promise& jsPromise)
{
    return jsPromise.Get();
}

v8::Local<v8::Value> js::JSValue(js::Promise* jsPromise)
{
    return jsPromise->Get();
}

alt::MValue js::JSToMValue(v8::Local<v8::Value> val, bool allowFunction)
{
    alt::ICore& core = alt::ICore::Instance();

    v8::Isolate* isolate = v8::Isolate::GetCurrent();
    v8::Local<v8::Context> ctx = isolate->GetEnteredOrMicrotaskContext();

    if(val.IsEmpty()) return core.CreateMValueNone();
    if(val->IsUndefined()) return core.CreateMValueNone();
    if(val->IsNull()) return core.CreateMValueNil();
    if(val->IsBoolean()) return core.CreateMValueBool(val->BooleanValue(isolate));
    if(val->IsInt32()) return core.CreateMValueInt(val->Int32Value(ctx).ToChecked());
    if(val->IsUint32()) return core.CreateMValueUInt(val->Uint32Value(ctx).ToChecked());
    if(val->IsBigInt())
    {
        bool isPositive;
        uint64_t unsignedVal = val.As<v8::BigInt>()->Uint64Value(&isPositive);
        if(isPositive) return core.CreateMValueUInt(unsignedVal);
        else
            return core.CreateMValueInt(val.As<v8::BigInt>()->Int64Value());
    }
    if(val->IsNumber()) return core.CreateMValueDouble(val->NumberValue(ctx).ToChecked());
    if(val->IsString()) return core.CreateMValueString(*v8::String::Utf8Value(isolate, val));
    if(val->IsObject())
    {
        if(val->IsArray())
        {
            js::Array arr(val.As<v8::Array>());
            uint32_t length = arr.Length();
            alt::MValueList list = core.CreateMValueList(length);
            alt::MValue val;
            for(uint32_t i = 0; i < length; i++)
            {
                if(!arr.Get(i, val)) continue;
                list->Set(i, val);
            }

            return list;
        }
        else if(val->IsFunction())
        {
            if(!allowFunction)
            {
                Logger::Error("Cannot convert function to MValue");
                return core.CreateMValueNone();
            }
            v8::Local<v8::Function> jsFunc = val.As<v8::Function>();
            IAltResource::Function* func = new IAltResource::Function(ctx, jsFunc);
            return core.CreateMValueFunction(func);
        }
        else if(val->IsArrayBuffer())
        {
            auto v8Buffer = val.As<v8::ArrayBuffer>()->GetBackingStore();
            return core.CreateMValueByteArray((uint8_t*)v8Buffer->Data(), v8Buffer->ByteLength());
        }
        else if(val->IsTypedArray())
        {
            v8::Local<v8::TypedArray> typedArray = val.As<v8::TypedArray>();
            if(!typedArray->HasBuffer()) return core.CreateMValueNone();
            v8::Local<v8::ArrayBuffer> v8Buffer = typedArray->Buffer();
            return core.CreateMValueByteArray((uint8_t*)((uintptr_t)v8Buffer->GetBackingStore()->Data() + typedArray->ByteOffset()), typedArray->ByteLength());
        }
        else if(val->IsMap())
        {
            v8::Local<v8::Map> map = val.As<v8::Map>();
            js::Array arr = map->AsArray();
            uint32_t length = arr.Length();

            alt::MValueDict dict = alt::ICore::Instance().CreateMValueDict();
            for(uint32_t i = 0; i < length; i += 2)
            {
                std::string key;
                if(!arr.Get(i, key)) continue;
                alt::MValue value;
                if(!arr.Get(i + 1, value)) continue;
                dict->Set(key, value);
            }
            return dict;
        }
        else if(val->IsProxy())
        {
            v8::Local<v8::Value> proxyValue = val.As<v8::Proxy>()->GetTarget();
            return JSToMValue(proxyValue, allowFunction);
        }
        else
        {
            js::IResource* resource = js::IResource::GetFromContext(ctx);
            v8::Local<v8::Object> v8Obj = val.As<v8::Object>();
            js::Object obj{ val.As<v8::Object>() };
            if(resource->IsVector3(v8Obj))
            {
                alt::Vector3f vec;
                vec[0] = obj.Get<float, true>("x");
                vec[1] = obj.Get<float, true>("y");
                vec[2] = obj.Get<float, true>("z");
                return core.CreateMValueVector3(vec);
            }
            else if(resource->IsVector2(v8Obj))
            {
                alt::Vector2f vec;
                vec[0] = obj.Get<float, true>("x");
                vec[1] = obj.Get<float, true>("y");
                return core.CreateMValueVector2(vec);
            }
            else if(resource->IsRGBA(v8Obj))
            {
                alt::RGBA rgba;
                rgba.r = obj.Get<uint8_t, true>("r");
                rgba.g = obj.Get<uint8_t, true>("g");
                rgba.b = obj.Get<uint8_t, true>("b");
                rgba.a = obj.Get<uint8_t, true>("a");
                return core.CreateMValueRGBA(rgba);
            }
            else if(resource->IsBaseObject(v8Obj))
            {
                ScriptObject* scriptObject = resource->GetScriptObject(obj.Get());
                if(scriptObject == nullptr)
                {
                    js::Throw("Failed to serialize invalid base object (object is probably destroyed or is not in streaming range)");
                    return core.CreateMValueNone();
                }

                return core.CreateMValueBaseObject(scriptObject->GetObject());
            }
            else
            {
                v8::Local<v8::Value> serialize = obj.GetSymbol<v8::Local<v8::Value>>(Symbol::SERIALIZE);
                if(!serialize.IsEmpty() && serialize->IsFunction())
                {
                    js::Function serializeFunc = serialize.As<v8::Function>();
                    std::optional<v8::Local<v8::Value>> resultVal = serializeFunc.Call<v8::Local<v8::Value>>(obj);
                    if(resultVal.has_value()) return JSToMValue(resultVal.value());
                }

                alt::MValueDict dict = core.CreateMValueDict();
                auto keys = obj.GetKeys();
                for(auto& key : keys)
                {
                    alt::MValue val;
                    if(!obj.Get(key, val)) continue;
                    dict->Set(key, val);
                }

                return dict;
            }
        }
    }

    return core.CreateMValueNone();
}

v8::Local<v8::Value> js::MValueToJS(alt::MValueConst val)
{
    v8::Isolate* isolate = v8::Isolate::GetCurrent();
    v8::Local<v8::Context> ctx = isolate->GetEnteredOrMicrotaskContext();
    js::IResource* resource = js::IResource::GetFromContext(ctx);

    if (!val)
    {
        js::Throw("js::MValueToJS: val is nullptr - please forward to module maintainer");
        return v8::Undefined(isolate);
    }

    switch(val->GetType())
    {
        case alt::IMValue::Type::NONE: return v8::Undefined(isolate);
        case alt::IMValue::Type::NIL: return js::JSValue(nullptr);
        case alt::IMValue::Type::BOOL: return js::JSValue(std::dynamic_pointer_cast<const alt::IMValueBool>(val)->Value());
        case alt::IMValue::Type::INT:
        {
            int64_t _val = std::dynamic_pointer_cast<const alt::IMValueInt>(val)->Value();
            if(_val >= JS_MIN_SAFE_INTEGER && _val <= JS_MAX_SAFE_INTEGER) return js::JSValue((double)_val);
            return js::JSValue(_val);
        }
        case alt::IMValue::Type::UINT:
        {
            uint64_t _val = std::dynamic_pointer_cast<const alt::IMValueUInt>(val)->Value();
            if(_val <= JS_MAX_SAFE_INTEGER) return js::JSValue((double)_val);
            return js::JSValue(_val);
        }
        case alt::IMValue::Type::DOUBLE: return js::JSValue(std::dynamic_pointer_cast<const alt::IMValueDouble>(val)->Value());
        case alt::IMValue::Type::STRING: return js::JSValue(std::dynamic_pointer_cast<const alt::IMValueString>(val)->Value());
        case alt::IMValue::Type::LIST:
        {
            alt::MValueListConst list = std::dynamic_pointer_cast<const alt::IMValueList>(val);
            js::Array arr = v8::Array::New(isolate, (int)list->GetSize());

            for(uint32_t i = 0; i < list->GetSize(); ++i) arr.Set(i, list->Get(i));

            return arr.Get();
        }
        case alt::IMValue::Type::DICT:
        {
            alt::MValueDictConst dict = std::dynamic_pointer_cast<const alt::IMValueDict>(val);
            js::Object obj = v8::Object::New(isolate);

            for(auto it = dict->Begin(); it != dict->End(); ++it) obj.Set(it->first, it->second);

            return obj.Get();
        }
        case alt::IMValue::Type::BASE_OBJECT:
        {
            alt::IBaseObject* ref = std::dynamic_pointer_cast<const alt::IMValueBaseObject>(val)->RawValue();
            return resource->GetScriptObject(ref)->Get();
        }
        case alt::IMValue::Type::FUNCTION:
        {
            alt::MValueFunctionConst fn = std::dynamic_pointer_cast<const alt::IMValueFunction>(val);
            v8::Local<v8::External> extFn = v8::External::New(isolate, new alt::MValueFunctionConst(fn));
            return v8::Function::New(ctx, IAltResource::Function::ExternalFunctionCallback, extFn).ToLocalChecked();
        }
        case alt::IMValue::Type::VECTOR3:
        {
            return resource->CreateVector3(std::dynamic_pointer_cast<const alt::IMValueVector3>(val)->Value());
        }
        case alt::IMValue::Type::VECTOR2:
        {
            return resource->CreateVector2(std::dynamic_pointer_cast<const alt::IMValueVector2>(val)->Value());
        }
        case alt::IMValue::Type::RGBA:
        {
            return resource->CreateRGBA(std::dynamic_pointer_cast<const alt::IMValueRGBA>(val)->Value());
        }
        case alt::IMValue::Type::BYTE_ARRAY:
        {
            alt::MValueByteArrayConst buffer = std::dynamic_pointer_cast<const alt::IMValueByteArray>(val);

            v8::MaybeLocal<v8::Value> jsVal = RawBytesToJS(buffer, resource);
            if(!jsVal.IsEmpty()) return jsVal.ToLocalChecked();

            v8::Local<v8::ArrayBuffer> v8Buffer = v8::ArrayBuffer::New(isolate, buffer->GetSize());
            std::memcpy(v8Buffer->GetBackingStore()->Data(), buffer->GetData(), buffer->GetSize());
            return v8Buffer;
        }
        default: Logger::Warn("js::MValueToJS Unknown MValue type", (int)val->GetType());
    }

    return v8::Undefined(isolate);
}

void js::MValueArgsToJS(alt::MValueArgs args, Array& argsArray)
{
    for(size_t i = 0; i < args.size(); ++i) argsArray.Push(MValueToJS(args[i]));
}

v8::Local<v8::Value> js::ConfigValueToJS(Config::Value::ValuePtr val)
{
    v8 ::Isolate* isolate = v8::Isolate::GetCurrent();
    v8::Local<v8::Context> ctx = isolate->GetEnteredOrMicrotaskContext();

    v8::Local<v8::Value> out;
    switch(val->GetType())
    {
        case Config::Value::Type::STRING:
        {
            out = JSValue(val->AsString());
            break;
        }
        case Config::Value::Type::NUMBER:
        {
            out = JSValue(val->AsNumber());
            break;
        }
        case Config::Value::Type::BOOL:
        {
            out = JSValue(val->AsBool());
            break;
        }
        case Config::Value::Type::LIST:
        {
            v8::Local<v8::Array> arr = v8::Array::New(isolate, val->GetSize());
            for(size_t i = 0; i < val->GetSize(); i++)
            {
                v8::Local<v8::Value> value = ConfigValueToJS(val[i]);
                if(value.IsEmpty()) continue;
                arr->Set(ctx, i, value);
            }
            out = arr;
            break;
        }
        case Config::Value::Type::DICT:
        {
            v8::Local<v8::Object> obj = v8::Object::New(isolate);
            for(auto& pair : val->AsDict())
            {
                v8::Local<v8::Value> value = ConfigValueToJS(pair.second);
                if(value.IsEmpty()) continue;
                obj->Set(ctx, JSValue(pair.first), value);
            }
            out = obj;
            break;
        }
        default: return v8::Local<v8::Value>();
    }
    return out;
}

alt::MValueByteArray js::JSToRawBytes(v8::Local<v8::Value> val, IResource* resource)
{
    std::optional<std::pair<uint8_t*, size_t>> result = ValueSerializer::Serialize(val, resource);
    if(!result.has_value()) return {};
    return alt::ICore::Instance().CreateMValueByteArray(result->first, result->second);
}

v8::MaybeLocal<v8::Value> js::RawBytesToJS(alt::MValueByteArrayConst val, IResource* resource)
{
    std::optional<v8::Local<v8::Value>> result = ValueDeserializer::Deserialize((uint8_t*)val->GetData(), val->GetSize(), resource);
    if(!result.has_value()) return v8::MaybeLocal<v8::Value>();
    return result.value();
}

std::optional<alt::IBaseObject*> js::internal::ToBaseObject(v8::Local<v8::Value> val)
{
    IResource* resource = GetCurrentResource();
    ScriptObject* scriptObject = resource->GetScriptObject(val);
    if(scriptObject == nullptr) return std::nullopt;
    return scriptObject->GetObject();
}

js::IResource* js::GetCurrentResource(v8::Isolate* isolate)
{
    v8::Isolate* currentIsolate = isolate == nullptr ? v8::Isolate::GetCurrent() : isolate;
    return IResource::GetFromContext(currentIsolate->GetEnteredOrMicrotaskContext());
}
