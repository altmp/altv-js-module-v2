#include "Module.h"
#include "CJavaScriptResource.h"
#include "helpers/NativeInvoker.h"

// clang-format off
static js::Module compatibilityModule("alt-client", [](js::IResource* resource) -> v8::Local<v8::Object> { return resource->GetCompatibilityModuleNamespace(); }, js::Module::Option::COMPATIBILITY_MODULE | js::Module::Option::EXPORT_AS_DEFAULT);

static void CallNative(const v8::FunctionCallbackInfo<v8::Value>& _info)
{
    alt::INative* native = (alt::INative*)_info.Data().As<v8::External>()->Value();
    js::FunctionContext ctx{ _info };
    CJavaScriptResource* resource = ctx.GetResource<CJavaScriptResource>();

    if(!ctx.Check(native->IsValid(), "Calling invalid native")) return;

    js::NativeInvoker::Invoke(ctx, native, true);
}
static js::Module compatibilityNativesModule("natives", [](js::ModuleTemplate& tpl) {
    std::vector<alt::INative*> natives = alt::ICore::Instance().GetAllNatives();
    for(alt::INative* native : natives)
        tpl.StaticFunction(native->GetName(), v8::FunctionTemplate::New(tpl.GetIsolate(), CallNative, v8::External::New(tpl.GetIsolate(), native)));
}, nullptr, js::Module::Option::COMPATIBILITY_MODULE | js::Module::Option::EXPORT_AS_DEFAULT);
