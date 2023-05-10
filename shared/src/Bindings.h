#pragma once

#include <string>
#include <unordered_map>

#include <v8.h>

#include "helpers/JS.h"

namespace js
{
    class IResource;

    class Binding
    {
        static std::unordered_map<std::string, Binding> __bindings;

    public:
        enum class Scope : uint8_t
        {
            SHARED,
            SERVER,
            CLIENT
        };

    private:
        bool valid = false;
        std::string name;
        Scope scope;
        ExternalString* src = nullptr;
        std::unordered_map<IResource*, Persistent<v8::Module>> compiledModuleMap;

        v8::Local<v8::Module> Compile(IResource* resource);

    public:
        Binding() = default;
        Binding(const std::string& _name, Scope _scope, const std::vector<char>& _src) : valid(true), name(_name), scope(_scope)
        {
            char* data = new char[_src.size()];
            memcpy(data, _src.data(), _src.size());
            src = new ExternalString(data, _src.size());
        }

        bool IsValid() const
        {
            return valid;
        }
        const std::string& GetName() const
        {
            return name;
        }
        Scope GetScope() const
        {
            return scope;
        }
        const char* GetSource() const
        {
            return src->data();
        }
        v8::Local<v8::Module> GetCompiledModule(IResource* resource);

        static std::vector<Binding*> GetBindingsForScope(Scope scope);
        static Binding& Get(const std::string& name)
        {
            static Binding invalidBinding{};
            if(!__bindings.contains(name)) return invalidBinding;
            return __bindings.at(name);
        }
        static void CleanupForResource(IResource* resource);
    };
}  // namespace js
