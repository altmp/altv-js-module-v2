#include "Class.h"
#include "helpers/Buffer.h"

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
static void Read<std::string>(js::FunctionContext& ctx)
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
static void Write(js::FunctionContext& ctx)
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
static void Write<std::string>(js::FunctionContext& ctx)
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

    delete buffer;
    ctx.SetExtraInternalFieldValue(nullptr);
}

static void Constructor(js::FunctionContext& ctx)
{
    if(!ctx.CheckArgCount(1)) return;

    size_t size;
    if(!ctx.GetArg(0, size)) return;
    if(!ctx.Check(size > 0 && size < 4096, "Buffer size must be greater than 0 and less than 4096 bytes")) return;

    js::Buffer* buffer = new js::Buffer(size);
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
