#include "IAltResource.h"

alt::MValue js::IAltResource::Function::Call(alt::MValueArgs args) const
{
    auto& core = alt::ICore::Instance();
    if(!resource->GetResource()->IsStarted()) return core.CreateMValueNone();

    v8::Isolate* isolate = resource->GetIsolate();
    v8::Local<v8::Context> context = resource->GetContext();
    v8::Locker locker(isolate);
    v8::Isolate::Scope isolateScope(isolate);
    v8::HandleScope handleScope(isolate);
    v8::Context::Scope contextScope(context);

    v8::Local<v8::Function> jsFunc = function.Get(isolate);
    std::vector<v8::Local<v8::Value>> jsArgs;
    jsArgs.reserve(args.size());
    for(size_t i = 0; i < args.size(); ++i) jsArgs.push_back(MValueToJS(args[i]));

    js::Function func(jsFunc);
    auto result = func.Call<alt::MValue>(jsArgs);
    if(!result) return core.CreateMValueNone();
    return result.value();
}

void js::IAltResource::Function::ExternalFunctionCallback(const v8::FunctionCallbackInfo<v8::Value>& info)
{
    alt::MValueFunctionConst* func = static_cast<alt::MValueFunctionConst*>(info.Data().As<v8::External>()->Value());
    alt::MValueArgs args;
    args.reserve(info.Length());
    for(size_t i = 0; i < info.Length(); ++i) args.push_back(JSToMValue(info[i]));
    alt::MValue retValue = (*func)->Call(args);
    info.GetReturnValue().Set(MValueToJS(retValue));
}

extern js::Class resourceClass;
v8::Local<v8::Object> js::IAltResource::CreateResourceObject(alt::IResource* resource)
{
    if(resourceObjects.contains(resource)) return resourceObjects.at(resource).Get(isolate);
    v8::Local<v8::Object> resourceObj = resourceClass.Create(GetContext(), resource);
    resourceObjects.insert({ resource, resourceClass.MakePersistent(resourceObj) });
    return resourceObj;
}
