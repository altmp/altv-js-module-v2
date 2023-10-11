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

        void Register(NamespaceTemplate& tpl)
        {
            if(parent) parent->Register(tpl);
            initCb(tpl);
        }

        static std::unordered_map<std::string, Namespace*>& GetAll()
        {
            static std::unordered_map<std::string, Namespace*> namespaces;
            return namespaces;
        }

    public:
        Namespace(const std::string& _name, NamespaceInitializationCallback _cb) : name(_name), initCb(_cb)
        {
            GetAll().insert({ name, this });
        }
        Namespace(const std::string& _name, Namespace* _parent, NamespaceInitializationCallback _cb) : name(_name), parent(_parent), initCb(_cb)
        {
            GetAll().insert({ name, this });
        }

        const std::string& GetName() const
        {
            return name;
        }

        v8::Local<v8::ObjectTemplate> Get(v8::Isolate* isolate)
        {
            if(templateMap.contains(isolate)) return templateMap.at(isolate).Get();
            NamespaceTemplate tpl(isolate, v8::ObjectTemplate::New(isolate));
            Register(tpl);
            templateMap.insert({ isolate, tpl });
            return tpl.Get();
        }

        static void Cleanup(v8::Isolate* isolate)
        {
            for(auto& [_, namespace_] : GetAll()) namespace_->templateMap.erase(isolate);
        }
    };
}  // namespace js
