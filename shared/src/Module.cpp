#include "Module.h"

void js::Module::Register(v8pp::module& mod)
{
    if(!parentModule.empty())
    {
        Module& parentMod = Get(parentModule);
        parentMod.Register(mod);
    }
    initCb(mod);
}

void js::Module::Initialize(v8::Isolate* isolate)
{
    for(auto& [name, module] : GetAll())
    {
        v8pp::module mod(isolate);
        module.Register(mod);
        module.templateMap.insert({ isolate, Persistent<v8::ObjectTemplate>(isolate, mod.impl()) });
    }
}

void js::Module::Cleanup(v8::Isolate* isolate)
{
    for(auto& [name, module] : GetAll())
    {
        module.templateMap.erase(isolate);
    }
}
