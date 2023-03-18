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
        class Instance
        {
            Logger& Get() const
            {
                static Logger logger(type);
                return logger;
            }

        public:
            template<typename T>
            Logger& operator<<(const T& value) const
            {
                Get() << value;
                return Get();
            }
            template<typename... Types>
            void operator()(Types... args) const
            {
                const char* sep = "";
                (((Get() << sep << args), sep = " "), ...);
                Get() << Endl;
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
