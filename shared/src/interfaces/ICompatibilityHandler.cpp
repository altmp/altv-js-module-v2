#include "ICompatibilityHandler.h"
#include "interfaces/IResource.h"

void js::ICompatibilityHandler::RegisterCompatibilityExport(const std::string& name, v8::Local<v8::Value> value)
{
    if(!enabled) return;
    v8::Isolate* isolate = v8::Isolate::GetCurrent();
    v8::Local<v8::Context> context = isolate->GetEnteredOrMicrotaskContext();
    js::Object obj = moduleNamespace.Get(isolate);

    obj.Set(name, value);
}

void js::ICompatibilityHandler::Initialize()
{
    v8::Isolate* isolate = v8::Isolate::GetCurrent();
    moduleNamespace.Reset(isolate, v8::Object::New(isolate));
}

void js::ICompatibilityHandler::Reset()
{
    moduleNamespace.Reset();
}

v8::Local<v8::Object> js::ICompatibilityHandler::GetCompatibilityModuleNamespace()
{
    return moduleNamespace.Get(v8::Isolate::GetCurrent());
}

void js::ICompatibilityHandler::RegisterCompatibilityExportFunc(js::FunctionContext& ctx)
{
    if(!ctx.CheckArgCount(2)) return;

    std::string exportName;
    if(!ctx.GetArg(0, exportName)) return;

    v8::Local<v8::Value> exportValue;
    if(!ctx.GetArg(1, exportValue)) return;

    ctx.GetResource()->RegisterCompatibilityExport(exportName, exportValue);
}
