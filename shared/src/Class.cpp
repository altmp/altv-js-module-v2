#include "Class.h"
#include "interfaces/IResource.h"

void js::Class::Register(v8::Isolate* isolate, ClassTemplate& tpl)
{
    if(parentClass)
    {
        if(!parentClass->templateMap.contains(isolate)) parentClass->Register(isolate, tpl);
    }
    initCb(tpl);
    tpl.Get()->SetClassName(js::JSValue(name));
    tpl.Get()->InstanceTemplate()->SetInternalFieldCount(internalFieldCount);
}

void js::Class::Initialize(v8::Isolate* isolate)
{
    for(auto class_ : GetAll())
    {
        ClassTemplate tpl{ isolate, class_, class_->ctor ? WrapFunction(class_->ctor) : v8::FunctionTemplate::New(isolate) };
        class_->Register(isolate, tpl);
        class_->templateMap.insert({ isolate, tpl });
    }
}

void js::Class::Cleanup(v8::Isolate* isolate)
{
    for(auto class_ : GetAll())
    {
        class_->templateMap.erase(isolate);
    }
    ClassTemplate::CleanupDynamicPropertyData(isolate);
}
