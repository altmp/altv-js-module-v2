#pragma once

#include <string>
#include <unordered_map>

#include <v8.h>

namespace js
{
    class IResource;

    template<typename T>
    using Persistent = v8::Persistent<T, v8::CopyablePersistentTraits<T>>;

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
        std::string src;
        std::unordered_map<IResource*, Persistent<v8::Module>> compiledModuleMap;

        v8::Local<v8::Module> Compile(IResource* resource);

    public:
        Binding() = default;
        Binding(const std::string& _name, Scope _scope, const std::string& _src) : valid(true), name(_name), scope(_scope), src(_src) {}

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
        const std::string& GetSource() const
        {
            return src;
        }
        v8::Local<v8::Module> GetCompiledModule(IResource* resource);

        static Binding& Get(const std::string& name)
        {
            static Binding invalidBinding;
            if(!__bindings.contains(name)) return invalidBinding;
            return __bindings.at(name);
        }
        static void CleanupForResource(IResource* resource);
    };
}  // namespace js
