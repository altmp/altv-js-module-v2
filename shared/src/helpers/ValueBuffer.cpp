#include "ValueBuffer.h"
#include "interfaces/IResource.h"
#include "JS.h"

// Magic bytes to identify raw JS value buffers
static constexpr uint8_t magicBytes[] = { 'J', 'S', 'V', 'a', 'l' };

bool js::IValueBuffer::Value(v8::Local<v8::Value>& value)
{
    ValueType type = GetValueType(value);
    if(!Type(type)) return false;
    switch(type)
    {
        case ValueType::JS_VALUE: return JSValue(value);
        case ValueType::ENTITY: return Entity(value);
        case ValueType::VECTOR3: return Vector3(value);
        case ValueType::VECTOR2: return Vector2(value);
        case ValueType::RGBA: return RGBA(value);
        case ValueType::QUATERNION: return Quaternion(value);
        case ValueType::BUFFER: return JSBuffer(value);
    }
    return false;
}

// *** Writer

bool js::ValueSerializer::Magic()
{
    serializer->WriteRawBytes(magicBytes, sizeof(magicBytes));
    return true;
}

bool js::ValueSerializer::Buffer(void*& data, size_t size)
{
    serializer->WriteRawBytes(data, size);
    return true;
}

bool js::ValueSerializer::Byte(uint8_t& value)
{
    serializer->WriteRawBytes(&value, sizeof(value));
    return true;
}

bool js::ValueSerializer::Bool(bool& value)
{
    serializer->WriteRawBytes(&value, sizeof(value));
    return true;
}

bool js::ValueSerializer::Type(ValueType& value)
{
    uint8_t type = static_cast<uint8_t>(value);
    serializer->WriteRawBytes(&type, sizeof(type));
    return true;
}

bool js::ValueSerializer::Int32(int32_t& value)
{
    serializer->WriteRawBytes(&value, sizeof(value));
    return true;
}

bool js::ValueSerializer::UInt32(uint32_t& value)
{
    serializer->WriteRawBytes(&value, sizeof(value));
    return true;
}

bool js::ValueSerializer::Int64(int64_t& value)
{
    serializer->WriteRawBytes(&value, sizeof(value));
    return true;
}

bool js::ValueSerializer::UInt64(uint64_t& value)
{
    serializer->WriteRawBytes(&value, sizeof(value));
    return true;
}

bool js::ValueSerializer::Float(float& value)
{
    serializer->WriteRawBytes(&value, sizeof(value));
    return true;
}

bool js::ValueSerializer::Double(double& value)
{
    serializer->WriteRawBytes(&value, sizeof(value));
    return true;
}

bool js::ValueSerializer::JSValue(v8::Local<v8::Value>& value)
{
    v8::Maybe<bool> result = serializer->WriteValue(resource->GetContext(), value);
    return result.FromMaybe(false);
}

bool js::ValueSerializer::Entity(v8::Local<v8::Value>& value)
{
    js::ScriptObject* scriptObject = resource->GetScriptObject(value);
    if(!scriptObject) return false;
    alt::IBaseObject* object = scriptObject->GetObject();
    if(!object) return false;

    uint32_t id;
    uint8_t type = static_cast<uint8_t>(object->GetType());
    bool remote;

#ifdef ALT_CLIENT_API
    remote = object->IsRemote();
    if(remote) id = object->GetRemoteID();
    else
        id = object->GetID();
#else
    remote = true;
    id = object->GetID();
#endif

    UInt32(id);
    Byte(type);
    Bool(remote);

    return true;
}

bool js::ValueSerializer::Vector3(v8::Local<v8::Value>& value)
{
    js::Object obj = value.As<v8::Object>();
    alt::Vector3f vector{ obj.Get<float, true>("x"), obj.Get<float, true>("y"), obj.Get<float, true>("z") };

    Float(vector[0]);
    Float(vector[1]);
    Float(vector[2]);
    return true;
}

bool js::ValueSerializer::Vector2(v8::Local<v8::Value>& value)
{
    js::Object obj = value.As<v8::Object>();
    alt::Vector2f vector{ obj.Get<float, true>("x"), obj.Get<float, true>("y") };

    Float(vector[0]);
    Float(vector[1]);
    return true;
}

bool js::ValueSerializer::RGBA(v8::Local<v8::Value>& value)
{
    js::Object obj = value.As<v8::Object>();
    alt::RGBA rgba{ obj.Get<uint8_t, true>("r"), obj.Get<uint8_t, true>("g"), obj.Get<uint8_t, true>("b"), obj.Get<uint8_t, true>("a") };

    Byte(rgba.r);
    Byte(rgba.g);
    Byte(rgba.b);
    Byte(rgba.a);
    return true;
}

bool js::ValueSerializer::Quaternion(v8::Local<v8::Value>& value)
{
    js::Object obj = value.As<v8::Object>();
    alt::Quaternion quaternion{ obj.Get<float, true>("x"), obj.Get<float, true>("y"), obj.Get<float, true>("z"), obj.Get<float, true>("w") };

    Float(quaternion.x);
    Float(quaternion.y);
    Float(quaternion.z);
    Float(quaternion.w);
    return true;
}

bool js::ValueSerializer::JSBuffer(v8::Local<v8::Value>& value)
{
    js::Object obj = value.As<v8::Object>();
    js::Buffer* buffer = obj.GetExtraInternalFieldValue<js::Buffer>();
    if(!buffer) return false;

    size_t size = buffer->GetSize();
    UInt64(size);
    void* data = buffer->GetBuffer();
    Buffer(data, size);
    return true;
}

js::IValueBuffer::ValueType js::ValueSerializer::GetValueType(v8::Local<v8::Value> value)
{
    if(value.IsEmpty()) return ValueType::INVALID;
    if(resource->IsBaseObject(value)) return ValueType::ENTITY;
    else if(resource->IsVector3(value))
        return ValueType::VECTOR3;
    else if(resource->IsVector2(value))
        return ValueType::VECTOR2;
    else if(resource->IsRGBA(value))
        return ValueType::RGBA;
    else if(resource->IsQuaternion(value))
        return ValueType::QUATERNION;
    else if(resource->IsBuffer(value))
        return ValueType::BUFFER;
    else
    {
        js::Type type = js::GetType(value, nullptr);
        switch(type)
        {
            case js::Type::FUNCTION:
            case js::Type::SHARED_ARRAY_BUFFER:
            case js::Type::PROMISE: return ValueType::INVALID;
        }
        return ValueType::JS_VALUE;
    }

    return ValueType::INVALID;
}

void js::ValueSerializer::ThrowDataCloneError(v8::Local<v8::String> message)
{
    js::Throw(CppValue(message));
}

v8::Maybe<bool> js::ValueSerializer::WriteHostObject(v8::Isolate* isolate, v8::Local<v8::Object> object)
{
    auto val = object.As<v8::Value>();
    return v8::Just<bool>(Value(val));
}

std::optional<std::pair<uint8_t*, size_t>> js::ValueSerializer::Serialize(v8::Local<v8::Value> value, IResource* resource)
{
    js::ValueSerializer writer;
    v8::ValueSerializer serializer(resource->GetIsolate(), &writer);
    writer.resource = resource;
    writer.serializer = &serializer;

    writer.serializer->WriteHeader();
    writer.Magic();
    bool result = writer.Value(value);
    if(!result) return std::nullopt;

    return serializer.Release();
}

// *** Reader

bool js::ValueDeserializer::Magic()
{
    void* magic = nullptr;
    if(!Buffer(magic, sizeof(magicBytes))) return false;
    return memcmp(magic, magicBytes, sizeof(magicBytes)) == 0;
}

bool js::ValueDeserializer::Buffer(void*& data, size_t size)
{
    return deserializer->ReadRawBytes(size, (const void**)&data);
}

bool js::ValueDeserializer::Byte(uint8_t& value)
{
    return Read<uint8_t>(value);
}

bool js::ValueDeserializer::Bool(bool& value)
{
    return Read<bool>(value);
}

bool js::ValueDeserializer::Type(ValueType& type)
{
    uint8_t typeVal = static_cast<uint8_t>(type);
    bool result = Read<uint8_t>(typeVal);
    if(!result) return false;
    type = static_cast<ValueType>(typeVal);
    return true;
}

bool js::ValueDeserializer::Int32(int32_t& value)
{
    return Read<int32_t>(value);
}

bool js::ValueDeserializer::UInt32(uint32_t& value)
{
    return Read<uint32_t>(value);
}

bool js::ValueDeserializer::Int64(int64_t& value)
{
    return Read<int64_t>(value);
}

bool js::ValueDeserializer::UInt64(uint64_t& value)
{
    return Read<uint64_t>(value);
}

bool js::ValueDeserializer::Float(float& value)
{
    return Read<float>(value);
}

bool js::ValueDeserializer::Double(double& value)
{
    return Read<double>(value);
}

bool js::ValueDeserializer::JSValue(v8::Local<v8::Value>& value)
{
    v8::MaybeLocal<v8::Value> result = deserializer->ReadValue(resource->GetContext());
    if(result.IsEmpty()) return false;
    value = result.ToLocalChecked();
    return true;
}

bool js::ValueDeserializer::Entity(v8::Local<v8::Value>& value)
{
    uint32_t id;
    if(!UInt32(id)) return false;
    uint8_t type;
    if(!Byte(type)) return false;
    bool remote;
    if(!Bool(remote)) return false;

    alt::IBaseObject* entity = nullptr;
#ifdef ALT_CLIENT_API
    if(remote) entity = alt::ICore::Instance().GetBaseObjectByRemoteID((alt::IBaseObject::Type)type, id);
    else
        entity = alt::ICore::Instance().GetBaseObjectByID((alt::IBaseObject::Type)type, id);
#else
    if(type == (uint8_t)alt::IBaseObject::Type::LOCAL_PLAYER) type = (uint8_t)alt::IBaseObject::Type::PLAYER;
    entity = alt::ICore::Instance().GetBaseObjectByID((alt::IBaseObject::Type)type, id);
#endif

    if(!entity) return false;
    value = resource->GetOrCreateScriptObject(resource->GetContext(), entity)->Get();
    return true;
}

bool js::ValueDeserializer::Vector3(v8::Local<v8::Value>& value)
{
    float x, y, z;
    if(!Float(x)) return false;
    if(!Float(y)) return false;
    if(!Float(z)) return false;
    value = resource->CreateVector3({ x, y, z });
    return true;
}

bool js::ValueDeserializer::Vector2(v8::Local<v8::Value>& value)
{
    float x, y;
    if(!Float(x)) return false;
    if(!Float(y)) return false;
    value = resource->CreateVector2({ x, y });
    return true;
}

bool js::ValueDeserializer::RGBA(v8::Local<v8::Value>& value)
{
    uint8_t r, g, b, a;
    if(!Byte(r)) return false;
    if(!Byte(g)) return false;
    if(!Byte(b)) return false;
    if(!Byte(a)) return false;
    value = resource->CreateRGBA({ r, g, b, a });
    return true;
}

bool js::ValueDeserializer::Quaternion(v8::Local<v8::Value>& value)
{
    float x, y, z, w;
    if(!Float(x)) return false;
    if(!Float(y)) return false;
    if(!Float(z)) return false;
    if(!Float(w)) return false;
    value = resource->CreateQuaternion({ x, y, z, w });
    return true;
}

extern js::Class bufferClass;
bool js::ValueDeserializer::JSBuffer(v8::Local<v8::Value>& value)
{
    size_t size;
    if(!UInt64(size)) return false;
    uint8_t* data = new uint8_t[size];
    void* dataPtr = data;
    if(!Buffer(dataPtr, size))
    {
        delete[] data;
        return false;
    }
    value = bufferClass.Create(resource->GetContext(), new js::Buffer(data, size, false));
    return true;
}

v8::MaybeLocal<v8::Object> js::ValueDeserializer::ReadHostObject(v8::Isolate* isolate)
{
    v8::Local<v8::Value> value;
    if(!Value(value)) return v8::MaybeLocal<v8::Object>();
    return value.As<v8::Object>();
}

js::IValueBuffer::ValueType js::ValueDeserializer::GetValueType(v8::Local<v8::Value> value)
{
    return js::IValueBuffer::ValueType::INVALID;
}

std::optional<v8::Local<v8::Value>> js::ValueDeserializer::Deserialize(uint8_t* bytes, size_t size, IResource* resource)
{
    js::ValueDeserializer reader;
    v8::ValueDeserializer deserializer(resource->GetIsolate(), bytes, size, &reader);
    reader.resource = resource;
    reader.deserializer = &deserializer;

    if(!reader.deserializer->ReadHeader(resource->GetContext()).FromMaybe(false)) return std::nullopt;
    if(!reader.Magic()) return std::nullopt;
    v8::Local<v8::Value> value;
    bool result = reader.Value(value);
    if(!result) return std::nullopt;

    return value;
}
