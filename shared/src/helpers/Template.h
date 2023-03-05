#pragma once

#include "v8.h"
#include "JS.h"
#include "Convert.h"

namespace js
{
    template<typename TemplateType>
    class Template
    {
        v8::Isolate* isolate;
        Persistent<TemplateType> templ;

    public:
        Template(v8::Isolate* _isolate, v8::Local<TemplateType> _templ) : isolate(_isolate), templ(_isolate, _templ) {}

        v8::Local<TemplateType> Get() const
        {
            return templ.Get(isolate);
        }
        v8::Isolate* GetIsolate() const
        {
            return isolate;
        }

        template<typename T>
        void StaticProperty(const std::string& name, T value)
        {
            Get()->Set(js::JSValue(name), js::JSValue(value));
        }
    };

    class ModuleTemplate : public Template<v8::ObjectTemplate>
    {
    public:
        ModuleTemplate(v8::Isolate* isolate, v8::Local<v8::ObjectTemplate> templ) : Template(isolate, templ) {}
    };

    class ClassTemplate : public Template<v8::FunctionTemplate>
    {
    public:
        ClassTemplate(v8::Isolate* isolate, v8::Local<v8::FunctionTemplate> templ) : Template(isolate, templ) {}
    };
}  // namespace js
