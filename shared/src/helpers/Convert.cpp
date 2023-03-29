#include "Convert.h"
#include "interfaces/IResource.h"
#include "JS.h"

v8::Local<v8::Value> js::JSValue(alt::IBaseObject* object)
{
    v8::Isolate* isolate = v8::Isolate::GetCurrent();
    if(!object) return v8::Null(isolate);
    IResource* resource = GetCurrentResource(isolate);
    if(!resource) return v8::Null(isolate);
    ScriptObject* scriptObject = resource->GetOrCreateScriptObject(resource->GetContext(), object);
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

v8::Local<v8::Value> js::JSValue(const js::Object& jsObj)
{
    return jsObj.Get();
}

v8::Local<v8::Value> js::JSValue(const js::Array& jsArr)
{
    return jsArr.Get();
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
            v8::Local<v8::Array> v8Arr = val.As<v8::Array>();
            alt::MValueList list = core.CreateMValueList(v8Arr->Length());

            for(uint32_t i = 0; i < v8Arr->Length(); ++i)
            {
                v8::Local<v8::Value> value;
                if(!v8Arr->Get(ctx, i).ToLocal(&value)) continue;
                list->Set(i, JSToMValue(value, allowFunction));
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
            IResource::Function* func = new IResource::Function(ctx, jsFunc);
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
            v8::Local<v8::Array> mapArr = map->AsArray();
            uint32_t size = mapArr->Length();

            alt::MValueDict dict = alt::ICore::Instance().CreateMValueDict();
            for(uint32_t i = 0; i < size; i += 2)
            {
                auto maybeKey = mapArr->Get(ctx, i);
                auto maybeValue = mapArr->Get(ctx, i + 1);
                v8::Local<v8::Value> key;
                v8::Local<v8::Value> value;

                if(!maybeKey.ToLocal(&key)) continue;
                if(!maybeValue.ToLocal(&value)) continue;
                std::string keyString = *v8::String::Utf8Value(isolate, key);
                if(keyString.empty()) continue;
                dict->Set(keyString, JSToMValue(value, false));
            }
            return dict;
        }
        else
        {
            js::IResource* resource = js::IResource::GetFromContext(ctx);
            v8::Local<v8::Object> v8Obj = val.As<v8::Object>();
            js::Object obj{ val.As<v8::Object>() };
            if(resource->IsVector3(v8Obj))
            {
                alt::Vector3f vec;
                vec[0] = obj.Get<float>("x");
                vec[1] = obj.Get<float>("y");
                vec[2] = obj.Get<float>("z");
                return core.CreateMValueVector3(vec);
            }
            else if(resource->IsVector2(v8Obj))
            {
                alt::Vector2f vec;
                vec[0] = obj.Get<float>("x");
                vec[1] = obj.Get<float>("y");
                return core.CreateMValueVector2(vec);
            }
            else if(resource->IsRGBA(v8Obj))
            {
                alt::RGBA rgba;
                rgba.r = obj.Get<uint8_t>("r");
                rgba.g = obj.Get<uint8_t>("g");
                rgba.b = obj.Get<uint8_t>("b");
                rgba.a = obj.Get<uint8_t>("a");
                return core.CreateMValueRGBA(rgba);
            }
            else if(resource->IsBaseObject(v8Obj))
            {
                ScriptObject* scriptObject = resource->GetScriptObject(obj.Get());
                if(scriptObject == nullptr) return core.CreateMValueNone();
                return core.CreateMValueBaseObject(scriptObject->GetObject());
            }
            else
            {
                alt::MValueDict dict = core.CreateMValueDict();
                v8::Local<v8::Array> keys;

                if(!v8Obj->GetOwnPropertyNames(ctx).ToLocal(&keys)) return core.CreateMValueNone();

                for(uint32_t i = 0; i < keys->Length(); ++i)
                {
                    v8::Local<v8::Value> v8Key;
                    if(!keys->Get(ctx, i).ToLocal(&v8Key)) return core.CreateMValueNone();
                    v8::Local<v8::Value> value;
                    if(!v8Obj->Get(ctx, v8Key).ToLocal(&value)) return core.CreateMValueNone();
                    if(value->IsUndefined()) continue;

                    std::string key = *v8::String::Utf8Value(isolate, v8Key);
                    dict->Set(key, JSToMValue(value, allowFunction));
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

    switch(val->GetType())
    {
        case alt::IMValue::Type::NONE: return v8::Undefined(isolate);
        case alt::IMValue::Type::NIL: return js::JSValue(nullptr);
        case alt::IMValue::Type::BOOL: return js::JSValue(val.As<alt::IMValueBool>()->Value());
        case alt::IMValue::Type::INT:
        {
            int64_t _val = val.As<alt::IMValueInt>()->Value();
            if(_val >= JS_MIN_SAFE_INTEGER && _val <= JS_MAX_SAFE_INTEGER) return js::JSValue((double)_val);
            return js::JSValue(_val);
        }
        case alt::IMValue::Type::UINT:
        {
            uint64_t _val = val.As<alt::IMValueUInt>()->Value();
            if(_val <= JS_MAX_SAFE_INTEGER) return js::JSValue((double)_val);
            return js::JSValue(_val);
        }
        case alt::IMValue::Type::DOUBLE: return js::JSValue(val.As<alt::IMValueDouble>()->Value());
        case alt::IMValue::Type::STRING: return js::JSValue(val.As<alt::IMValueString>()->Value());
        case alt::IMValue::Type::LIST:
        {
            alt::MValueListConst list = val.As<alt::IMValueList>();
            v8::Local<v8::Array> v8Arr = v8::Array::New(isolate, (int)list->GetSize());

            for(uint32_t i = 0; i < list->GetSize(); ++i) v8Arr->Set(ctx, i, MValueToJS(list->Get(i)));

            return v8Arr;
        }
        case alt::IMValue::Type::DICT:
        {
            alt::MValueDictConst dict = val.As<alt::IMValueDict>();
            v8::Local<v8::Object> v8Obj = v8::Object::New(isolate);

            for(auto it = dict->Begin(); it; it = dict->Next())
            {
                v8Obj->Set(ctx, js::JSValue(it->GetKey()), MValueToJS(it->GetValue()));
            }

            return v8Obj;
        }
        case alt::IMValue::Type::BASE_OBJECT:
        {
            alt::IBaseObject* ref = val.As<alt::IMValueBaseObject>()->RawValue();
            return resource->GetOrCreateScriptObject(ctx, ref)->Get();
        }
        case alt::IMValue::Type::FUNCTION:
        {
            alt::MValueFunctionConst fn = val.As<alt::IMValueFunction>();
            v8::Local<v8::External> extFn = v8::External::New(isolate, new alt::MValueFunctionConst(fn));
            return v8::Function::New(ctx, IResource::Function::ExternalFunctionCallback, extFn).ToLocalChecked();
        }
        case alt::IMValue::Type::VECTOR3:
        {
            return resource->CreateVector3(val.As<alt::IMValueVector3>()->Value());
        }
        case alt::IMValue::Type::VECTOR2:
        {
            return resource->CreateVector2(val.As<alt::IMValueVector2>()->Value());
        }
        case alt::IMValue::Type::RGBA:
        {
            return resource->CreateRGBA(val.As<alt::IMValueRGBA>()->Value());
        }
        case alt::IMValue::Type::BYTE_ARRAY:
        {
            alt::MValueByteArrayConst buffer = val.As<alt::IMValueByteArray>();
            // todo: raw event support
            // Check if the buffer is a raw JS value buffer
            // v8::MaybeLocal<v8::Value> jsVal = RawBytesToJS(buffer);
            // if(!jsVal.IsEmpty()) return jsVal.ToLocalChecked();

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
    for(size_t i = 0; i < args.GetSize(); ++i) argsArray.Push(MValueToJS(args[i]));
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

std::optional<alt::IBaseObject*> js::ToBaseObject(v8::Local<v8::Value> val)
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
