#pragma once

#include <sstream>

#include "cpp-sdk/ICore.h"

namespace js
{
    class Logger
    {
    private:
        enum class Type
        {
            INFO,
            COLORED,
            WARN,
            ERR,
        };

        std::stringstream stream;
        Type type;

        Logger(Type type) : type(type) {}

        template<Type type>
        struct Instance
        {
            template<typename T>
            Logger& operator<<(const T& value) const
            {
                static Logger logger(type);
                logger << value;
                return logger;
            }
        };

    public:
        static constexpr struct EndlStruct
        {
        } Endl{};
        static constexpr Instance<Type::INFO> Info{};
        static constexpr Instance<Type::COLORED> Colored{};
        static constexpr Instance<Type::WARN> Warn{};
        static constexpr Instance<Type::ERR> Error{};

        template<typename T>
        Logger& operator<<(const T& value)
        {
            stream << value;
            return *this;
        }
        Logger& operator<<(const EndlStruct&);
    };
}  // namespace js
