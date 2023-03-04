#pragma once

#include <unordered_map>
#include <functional>
#include <iostream>

#include "v8.h"
#include "v8pp/module.hpp"

namespace js
{
    template<typename T>
    using Persistent = v8::Persistent<T, v8::CopyablePersistentTraits<T>>;

    class Module
    {
        static std::unordered_map<std::string, Module>& GetAll()
        {
            static std::unordered_map<std::string, Module> modules;
            return modules;
        }

    public:
        using ModuleInitializationCallback = std::function<void(v8pp::module&)>;

    private:
        std::string name;
        std::string parentModule;
        ModuleInitializationCallback initCb;
        std::unordered_map<v8::Isolate*, Persistent<v8::ObjectTemplate>> templateMap;

        void Register(v8pp::module& mod);

    public:
        Module(const std::string& _name, ModuleInitializationCallback _cb) : name(_name), initCb(_cb)
        {
            GetAll().insert({ name, *this });
        }
        Module(const std::string& _name, const std::string& _parent, ModuleInitializationCallback _cb) : name(_name), parentModule(_parent), initCb(_cb)
        {
            GetAll().insert({ name, *this });
        }

        const std::string& GetName() const
        {
            return name;
        }
        v8::Local<v8::ObjectTemplate> GetTemplate(v8::Isolate* isolate)
        {
            return templateMap.at(isolate).Get(isolate);
        }
        v8::Local<v8::Object> GetNamespace(v8::Local<v8::Context> context)
        {
            return GetTemplate(context->GetIsolate())->NewInstance(context).ToLocalChecked();
        }

        static bool Exists(const std::string& name)
        {
            return GetAll().contains(name);
        }
        static Module& Get(const std::string& name)
        {
            return GetAll().at(name);
        }

        static void Initialize(v8::Isolate* isolate);
        static void Cleanup(v8::Isolate* isolate);
    };
}  // namespace js
