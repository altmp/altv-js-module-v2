#include "Module.h"
#include "Class.h"

void js::Module::Register(ModuleTemplate& tpl)
{
    v8::Isolate* isolate = tpl.GetIsolate();
    if(!parentModule.empty())
    {
        Module& parentMod = Get(parentModule);
        parentMod.Register(tpl);
    }
    for(js::Class* class_ : classes)
    {
        tpl.StaticProperty(class_->GetName(), class_->GetTemplate(isolate).Get());
    }
    initCb(tpl);
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
