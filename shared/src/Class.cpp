#include "Class.h"
#include "interfaces/IResource.h"

void js::Class::Register(v8::Isolate* isolate)
{
    ClassTemplate tpl{ isolate, this, ctor ? WrapFunction(ctor) : v8::FunctionTemplate::New(isolate) };
    if(parentClass)
    {
        if(!parentClass->templateMap.contains(isolate)) parentClass->Register(isolate);
        tpl.Get()->Inherit(parentClass->templateMap.at(isolate).Get());
    }
    initCb(tpl);
    tpl.Get()->SetClassName(js::JSValue(name));
    tpl.Get()->InstanceTemplate()->SetInternalFieldCount(internalFieldCount);
    templateMap.insert({ isolate, tpl });
}

void js::Class::Initialize(v8::Isolate* isolate)
{
    for(auto class_ : GetAll())
    {
        class_->Register(isolate);
#ifdef DEBUG_BINDINGS
        class_->GetTemplate(isolate).DumpRegisteredKeys();
        Logger::Colored("~g~[BINDINGS] ~w~Dumped class", class_->GetName());
#endif
    }
    ClassTemplate::CleanupPropertyGetterMap(isolate);  // Only needed while setting up the templates, so we can free the data here
}

void js::Class::Cleanup(v8::Isolate* isolate)
{
    for(auto class_ : GetAll())
    {
        class_->templateMap.erase(isolate);
    }
    ClassTemplate::CleanupDynamicPropertyData(isolate);
}
