#pragma once

#include <string>
#include <unordered_map>

namespace js
{
    class Binding
    {
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

        static std::unordered_map<std::string, Binding> __bindings;

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

        static const Binding& Get(const std::string& name)
        {
            static Binding invalidBinding;
            if(!__bindings.contains(name)) return invalidBinding;
            return __bindings.at(name);
        }
    };
}  // namespace js
