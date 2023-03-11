#pragma once

#include "v8.h"

#include "helpers/JS.h"
#include "helpers/Template.h"

namespace js
{
    class Namespace
    {
    public:
        using NamespaceInitializationCallback = std::function<void(NamespaceTemplate&)>;

    private:
        std::string name;
        NamespaceInitializationCallback initCb;
        Namespace* parent = nullptr;
        std::unordered_map<v8::Isolate*, NamespaceTemplate> templateMap;

    public:
        Namespace(const std::string& _name, NamespaceInitializationCallback _cb) : name(_name), initCb(_cb) {}
        Namespace(const std::string& _name, Namespace* _parent, NamespaceInitializationCallback _cb) : name(_name), parent(_parent), initCb(_cb) {}

        const std::string& GetName() const
        {
            return name;
        }

        v8::Local<v8::ObjectTemplate> Get(v8::Isolate* isolate)
        {
            if(templateMap.contains(isolate)) return templateMap.at(isolate).Get();
            NamespaceTemplate tpl(isolate, parent ? parent->Get(isolate) : v8::ObjectTemplate::New(isolate));
            initCb(tpl);
            templateMap.insert({ isolate, tpl });
            return tpl.Get();
        }
    };
}  // namespace js
