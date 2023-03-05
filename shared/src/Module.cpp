#include "Module.h"
#include "Class.h"

void js::Module::Register(ModuleTemplate& templ)
{
    v8::Isolate* isolate = templ.GetIsolate();
    if(!parentModule.empty())
    {
        Module& parentMod = Get(parentModule);
        parentMod.Register(templ);
    }
    for(js::Class* class_ : classes)
    {
        templ.StaticProperty(class_->GetName(), class_->GetTemplate(isolate).Get());
    }
    initCb(templ);
}

void js::Module::Initialize(v8::Isolate* isolate)
{
    for(auto& [name, module] : GetAll())
    {
        ModuleTemplate mod{ isolate, v8::ObjectTemplate::New(isolate) };
        module->Register(mod);
        module->templateMap.insert({ isolate, mod });
    }
}

void js::Module::Cleanup(v8::Isolate* isolate)
{
    for(auto& [name, module] : GetAll())
    {
        module->templateMap.erase(isolate);
    }
}
