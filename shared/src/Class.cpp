#include "Class.h"
#include "module/IResource.h"

void js::Class::ConstructorWrap(const v8::FunctionCallbackInfo<v8::Value>& info)
{
    FunctionContext ctx{ info };
    Class* class_ = static_cast<Class*>(info.Data().As<v8::External>()->Value());
    class_->ctor(ctx);
}

void js::Class::Register(v8::Isolate* isolate, ClassTemplate& templ)
{
    if(parentClass)
    {
        if(!parentClass->templateMap.contains(isolate)) parentClass->Register(isolate, templ);
    }
    initCb(templ);
    templ.Get()->SetClassName(js::JSValue(name));
    templ.Get()->InstanceTemplate()->SetInternalFieldCount(internalFieldCount);
}

void js::Class::Initialize(v8::Isolate* isolate)
{
    for(auto class_ : GetAll())
    {
        ClassTemplate templ{ isolate, class_->ctor ? v8::FunctionTemplate::New(isolate, ConstructorWrap, v8::External::New(isolate, class_)) : v8::FunctionTemplate::New(isolate) };
        class_->Register(isolate, templ);
        class_->templateMap.insert({ isolate, templ });
    }
}

void js::Class::Cleanup(v8::Isolate* isolate)
{
    for(auto class_ : GetAll())
    {
        class_->templateMap.erase(isolate);
    }
}
