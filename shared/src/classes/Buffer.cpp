#include "Class.h"
#include "helpers/Buffer.h"
#include "interfaces/IResource.h"

template<typename T>
static void Read(js::FunctionContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldValue()) return;
    if(!ctx.CheckArgCount(1)) return;
    js::Buffer* buffer = ctx.GetExtraInternalFieldValue<js::Buffer>();

    size_t offset;
    if(!ctx.GetArg(0, offset)) return;

    T val;
    if(!buffer->Read(offset, val)) return;

    ctx.Return(val);
}
template<>
void Read<std::string>(js::FunctionContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldValue()) return;
    if(!ctx.CheckArgCount(2)) return;
    js::Buffer* buffer = ctx.GetExtraInternalFieldValue<js::Buffer>();

    size_t offset;
    if(!ctx.GetArg(0, offset)) return;

    size_t length;
    if(!ctx.GetArg(1, length)) return;

    std::string val;
    if(!buffer->ReadString(offset, length, val)) return;

    ctx.Return(val);
}

template<typename T>
void Write(js::FunctionContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldValue()) return;
    if(!ctx.CheckArgCount(2)) return;
    js::Buffer* buffer = ctx.GetExtraInternalFieldValue<js::Buffer>();

    size_t offset;
    if(!ctx.GetArg(0, offset)) return;

    T val;
    if(!ctx.GetArg(1, val)) return;

    buffer->Write(offset, val);
}
template<>
void Write<std::string>(js::FunctionContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldValue()) return;
    if(!ctx.CheckArgCount(2)) return;
    js::Buffer* buffer = ctx.GetExtraInternalFieldValue<js::Buffer>();

    size_t offset;
    if(!ctx.GetArg(0, offset)) return;

    std::string val;
    if(!ctx.GetArg(1, val)) return;

    buffer->WriteString(offset, val);
}

static void SizeGetter(js::LazyPropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldValue()) return;
    js::Buffer* buffer = ctx.GetExtraInternalFieldValue<js::Buffer>();

    ctx.Return(buffer->GetSize());
}

static void Destroy(js::FunctionContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldValue()) return;
    js::Buffer* buffer = ctx.GetExtraInternalFieldValue<js::Buffer>();

    ctx.GetResource()->RemoveOwnedBuffer(buffer);
    ctx.SetExtraInternalFieldValue(nullptr);
    delete buffer;
}

static void Constructor(js::FunctionContext& ctx)
{
    if(!ctx.CheckArgCount(1)) return;
    if(!ctx.CheckArgType(0, { js::Type::NUMBER, js::Type::ARRAY_BUFFER, js::Type::ARRAY_BUFFER_VIEW })) return;

    js::Buffer* buffer;
    if(ctx.GetArgType(0) == js::Type::NUMBER)
    {
        uint32_t size;
        if(!ctx.GetArg(0, size)) return;
        if(!ctx.Check(size > 0 && size < 4096, "Buffer size must be greater than 0 and less than 4096 bytes")) return;

        buffer = new js::Buffer(size);
    }
    else if(ctx.GetArgType(0) == js::Type::ARRAY_BUFFER)
    {
        v8::Local<v8::Value> value;
        if(!ctx.GetArg(0, value)) return;
        v8::Local<v8::ArrayBuffer> arrayBuffer = value.As<v8::ArrayBuffer>();

        buffer = new js::Buffer((uint8_t*)arrayBuffer->GetBackingStore()->Data(), arrayBuffer->ByteLength());
    }
    else if(ctx.GetArgType(0) == js::Type::ARRAY_BUFFER_VIEW)
    {
        v8::Local<v8::Value> value;
        if(!ctx.GetArg(0, value)) return;
        v8::Local<v8::ArrayBufferView> arrayBufferView = value.As<v8::ArrayBufferView>();

        buffer = new js::Buffer((uint8_t*)((uintptr_t)arrayBufferView->Buffer()->GetBackingStore()->Data() + (uintptr_t)arrayBufferView->ByteOffset()), arrayBufferView->ByteLength());
    }

    ctx.GetResource()->AddOwnedBuffer(buffer);
    ctx.SetExtraInternalFieldValue(buffer);
}

// clang-format off
extern js::Class bufferClass("Buffer", Constructor, [](js::ClassTemplate& tpl)
{
    tpl.LazyProperty("size", SizeGetter);

    tpl.Method("readUInt8", Read<uint8_t>);
    tpl.Method("readUInt16", Read<uint16_t>);
    tpl.Method("readUInt32", Read<uint32_t>);
    tpl.Method("readUInt64", Read<uint64_t>);
    tpl.Method("readInt8", Read<int8_t>);
    tpl.Method("readInt16", Read<int16_t>);
    tpl.Method("readInt32", Read<int32_t>);
    tpl.Method("readInt64", Read<int64_t>);
    tpl.Method("readFloat", Read<float>);
    tpl.Method("readDouble", Read<double>);
    tpl.Method("readString", Read<std::string>);

    tpl.Method("writeUInt8", Write<uint8_t>);
    tpl.Method("writeUInt16", Write<uint16_t>);
    tpl.Method("writeUInt32", Write<uint32_t>);
    tpl.Method("writeUInt64", Write<uint64_t>);
    tpl.Method("writeInt8", Write<int8_t>);
    tpl.Method("writeInt16", Write<int16_t>);
    tpl.Method("writeInt32", Write<int32_t>);
    tpl.Method("writeInt64", Write<int64_t>);
    tpl.Method("writeFloat", Write<float>);
    tpl.Method("writeDouble", Write<double>);
    tpl.Method("writeString", Write<std::string>);

    tpl.Method("destroy", Destroy);
}, true);
