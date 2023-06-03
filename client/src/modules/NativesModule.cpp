#include "Module.h"
#include "CJavaScriptResource.h"
#include "helpers/NativeInvoker.h"

static void CallNative(const v8::FunctionCallbackInfo<v8::Value>& _info)
{
    alt::INative* native = (alt::INative*)_info.Data().As<v8::External>()->Value();
    js::FunctionContext ctx{ _info };
    CJavaScriptResource* resource = ctx.GetResource<CJavaScriptResource>();

    if(!ctx.Check(native->IsValid(), "Calling invalid native")) return;

    js::NativeInvoker::Invoke(ctx, native);
}

// clang-format off
static js::Module nativesModule("@altv/natives", [](js::ModuleTemplate& module)
{
    std::vector<alt::INative*> natives = alt::ICore::Instance().GetAllNatives();
    for(alt::INative* native : natives)
        module.StaticFunction(native->GetName(), v8::FunctionTemplate::New(module.GetIsolate(), CallNative, v8::External::New(module.GetIsolate(), native)));
});
