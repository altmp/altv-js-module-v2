#pragma once

#include <unordered_map>
#include <functional>
#include <iostream>
#include <vector>

#include "v8.h"

#include "helpers/JS.h"
#include "helpers/Template.h"

namespace js
{
    class Class;
    class IResource;

    class Module
    {
        static std::unordered_map<std::string, Module*>& GetAll()
        {
            static std::unordered_map<std::string, Module*> modules;
            return modules;
        }

    public:
        using ModuleInitializationCallback = std::function<void(ModuleTemplate&)>;
        using CustomGetNamespaceCallback = std::function<v8::Local<v8::Object>(IResource*)>;

        enum class Option : uint16_t
        {
            NONE = 0,
            COMPATIBILITY_MODULE = 1 << 0,
            EXPORT_AS_DEFAULT = 1 << 1
        };

    private:
        std::string name;
        std::string parentModule;
        ModuleInitializationCallback initCb;
        CustomGetNamespaceCallback customGetNamespaceCb;
        std::unordered_map<v8::Isolate*, ModuleTemplate> templateMap;
        std::unordered_map<IResource*, Persistent<v8::Object>> instanceMap;
        std::vector<Class*> classes;
        Option options = Option::NONE;

        void Register(ModuleTemplate& tpl);

    public:
        Module(const std::string& _name, ModuleInitializationCallback _cb, CustomGetNamespaceCallback _customGetNamespaceCb = nullptr, Option _options = Option::NONE)
            : name(_name), initCb(_cb), customGetNamespaceCb(_customGetNamespaceCb), options(_options)
        {
            GetAll().insert({ name, this });
        }
        Module(const std::string& _name,
               const std::vector<Class*>& _classes,
               ModuleInitializationCallback _cb,
               CustomGetNamespaceCallback _customGetNamespaceCb = nullptr,
               Option _options = Option::NONE)
            : name(_name), classes(_classes), initCb(_cb), customGetNamespaceCb(_customGetNamespaceCb), options(_options)
        {
            GetAll().insert({ name, this });
        }
        Module(
          const std::string& _name, const std::string& _parent, ModuleInitializationCallback _cb, CustomGetNamespaceCallback _customGetNamespaceCb = nullptr, Option _options = Option::NONE)
            : name(_name), parentModule(_parent), initCb(_cb), customGetNamespaceCb(_customGetNamespaceCb), options(_options)
        {
            GetAll().insert({ name, this });
        }
        Module(const std::string& _name,
               const std::string& _parent,
               const std::vector<Class*>& _classes,
               ModuleInitializationCallback _cb,
               CustomGetNamespaceCallback _customGetNamespaceCb = nullptr,
               Option _options = Option::NONE)
            : name(_name), parentModule(_parent), classes(_classes), initCb(_cb), customGetNamespaceCb(_customGetNamespaceCb), options(_options)
        {
            GetAll().insert({ name, this });
        }
        Module(const std::string& _name, CustomGetNamespaceCallback _customGetNamespaceCb, Option _options = Option::NONE)
            : name(_name), customGetNamespaceCb(_customGetNamespaceCb), options(_options)
        {
            GetAll().insert({ name, this });
        }

        const std::string& GetName() const
        {
            return name;
        }
        v8::Local<v8::ObjectTemplate> GetTemplate(v8::Isolate* isolate)
        {
            return templateMap.at(isolate).Get();
        }
        v8::Local<v8::Object> GetNamespace(IResource* resource);
        Option GetOptions()
        {
            return options;
        }
        bool HasOption(Option option)
        {
            return (int)options & (int)option;
        }

        static bool Exists(const std::string& name)
        {
            return GetAll().contains(name);
        }
        static Module& Get(const std::string& name)
        {
            return *GetAll().at(name);
        }

        static void Initialize(v8::Isolate* isolate);
        static void Cleanup(v8::Isolate* isolate);
        static void CleanupForResource(IResource* resource);
    };
}  // namespace js

inline constexpr js::Module::Option operator|(js::Module::Option a, js::Module::Option b)
{
    return static_cast<js::Module::Option>(static_cast<uint16_t>(a) | static_cast<uint16_t>(b));
}

inline constexpr js::Module::Option operator&(js::Module::Option a, js::Module::Option b)
{
    return static_cast<js::Module::Option>(static_cast<uint16_t>(a) & static_cast<uint16_t>(b));
}
