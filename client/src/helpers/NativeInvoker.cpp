#include "NativeInvoker.h"
#include "CJavaScriptResource.h"

bool js::NativeInvoker::PushArgs(js::FunctionContext& ctx, alt::INative* native)
{
    using Type = alt::INative::Type;

    std::vector<alt::INative::Type> nativeArgs = native->GetArgTypes();

    for(size_t i = 0; i < nativeArgs.size(); i++)
    {
        switch(nativeArgs[i])
        {
            case Type::ARG_BOOL:
            {
                if(!PushArg<bool>(ctx, i)) return false;
                break;
            }
            case Type::ARG_BOOL_PTR:
            {
                if(!PushArg<bool*>(ctx, i)) return false;
                break;
            }
            case Type::ARG_INT32:
            {
                if(!PushArg<int32_t>(ctx, i)) return false;
                break;
            }
            case Type::ARG_INT32_PTR:
            {
                if(!PushArg<int32_t*>(ctx, i)) return false;
                break;
            }
            case Type::ARG_UINT32:
            {
                if(!PushArg<uint32_t>(ctx, i)) return false;
                break;
            }
            case Type::ARG_UINT32_PTR:
            {
                if(!PushArg<uint32_t*>(ctx, i)) return false;
                break;
            }
            case Type::ARG_FLOAT:
            {
                if(!PushArg<float>(ctx, i)) return false;
                break;
            }
            case Type::ARG_FLOAT_PTR:
            {
                if(!PushArg<float*>(ctx, i)) return false;
                break;
            }
            /*
            case Type::ARG_VECTOR3:
            {
                if(!PushArg<alt::INative::Vector3>(ctx, i)) return false;
                break;
            }
            */
            case Type::ARG_STRUCT:
            {
                if(!PushArg<void*>(ctx, i)) return false;
                break;
            }
            case Type::ARG_VECTOR3_PTR:
            {
                if(!PushArg<alt::INative::Vector3*>(ctx, i)) return false;
                break;
            }
            case Type::ARG_STRING:
            {
                if(!PushArg<char*>(ctx, i)) return false;
                break;
            }
            default:
            {
                Logger::Warn("[JS] Unknown native argument type", magic_enum::enum_name(nativeArgs[i]), "for native", native->GetName(), "at index", i);
                break;
            }
        }
    }

    return true;
}

v8::Local<v8::Value> js::NativeInvoker::GetPointerReturnValue(alt::INative::Type type)
{
    using Type = alt::INative::Type;

    switch(type)
    {
        case Type::ARG_BOOL_PTR: return js::JSValue((bool)*reinterpret_cast<int32_t*>(&pointers[pointersCount++]));
        case Type::ARG_INT32_PTR: return js::JSValue(*reinterpret_cast<int32_t*>(&pointers[pointersCount++]));
        case Type::ARG_UINT32_PTR: return js::JSValue(*reinterpret_cast<uint32_t*>(&pointers[pointersCount++]));
        case Type::ARG_FLOAT_PTR: return js::JSValue(*reinterpret_cast<float*>(&pointers[pointersCount++]));
        case Type::ARG_VECTOR3_PTR:
        {
            alt::INative::Vector3* vector = reinterpret_cast<alt::INative::Vector3*>(&pointers[pointersCount]);
            pointersCount += 3;
            return resource->CreateVector3({ vector->x, vector->y, vector->z });
        }
    }
    // js::Logger::Warn("[JS] Unknown native pointer return type:", magic_enum::enum_name(type), (int)type);
    return v8::Undefined(resource->GetIsolate());
}

v8::Local<v8::Value> js::NativeInvoker::GetReturnValue()
{
    using Type = alt::INative::Type;

    switch(native->GetRetnType())
    {
        case Type::ARG_BOOL: return js::JSValue(nativeContext->ResultBool());
        case Type::ARG_INT32: return js::JSValue(nativeContext->ResultInt());
        case Type::ARG_UINT32: return js::JSValue(nativeContext->ResultUint());
        case Type::ARG_FLOAT: return js::JSValue(nativeContext->ResultFloat());
        case Type::ARG_VECTOR3:
        {
            alt::INative::Vector3 vector = nativeContext->ResultVector3();
            return resource->CreateVector3({ vector.x, vector.y, vector.z });
        }
        case Type::ARG_STRING: return js::JSValue(nativeContext->ResultString());
        case Type::ARG_VOID: return v8::Undefined(resource->GetIsolate());
    }
    js::Logger::Warn("[JS] Unknown native return type:", magic_enum::enum_name(native->GetRetnType()), (int)native->GetRetnType());
    return v8::Undefined(resource->GetIsolate());
}

void* js::NativeInvoker::GetBufferFromValue(v8::Local<v8::Value> val)
{
    void* ptr = nullptr;
    if(val->IsObject() && !val->IsNull() && resource->IsBuffer(val))
    {
        Buffer* buffer = static_cast<Buffer*>(val.As<v8::Object>()->GetAlignedPointerFromInternalField(1));
        if(buffer->GetSize() != 0) ptr = (void*)buffer->GetBuffer();
    }
    return ptr;
}

js::NativeInvoker::NativeInvoker(CJavaScriptResource* resource, alt::INative* native) : resource(resource), native(native), nativeContext(resource->GetNativeContext()) {}
js::NativeInvoker::~NativeInvoker()
{
    for (auto ptr : pointers)
        free(ptr);

    for (auto ptr: stringValues)
        free(ptr);
}

bool js::NativeInvoker::Invoke(js::FunctionContext& ctx, alt::INative* native)
{
    CJavaScriptResource* resource = ctx.GetResource<CJavaScriptResource>();
    std::shared_ptr<alt::INative::Context> nativeCtx = resource->GetNativeContext();
    NativeInvoker invoker{ resource, native };

    nativeCtx->Reset();

    std::vector<alt::INative::Type> args = native->GetArgTypes();
    if(!ctx.CheckArgCount(invoker.GetMinimumArgCount(), args.size())) return false;

    if(!invoker.PushArgs(ctx, native)) return false;

    if(!ctx.Check(native->Invoke(nativeCtx), "Failed to invoke native")) return false;

    if(invoker.returnsCount == 1) ctx.Return(invoker.GetReturnValue());
    else
    {
        // todo: maybe v2 should move away from this array shit
        js::Array arr{ invoker.returnsCount };

        invoker.pointersCount = 0;

        // First element is always the return value
        if(native->GetRetnType() != alt::INative::Type::ARG_VOID) arr.Push(invoker.GetReturnValue());

        // Then push the pointer arguments into the array
        for(auto& arg : args)
            if(auto val = invoker.GetPointerReturnValue(arg); !val->IsUndefined()) arr.Push(val);

        ctx.Return(arr);
    }

    return true;
}
