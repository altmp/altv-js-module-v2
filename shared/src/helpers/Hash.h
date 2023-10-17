#pragma once

#include <string>

namespace js
{
    template<size_t N>
    constexpr uint32_t ConstHash(const char (&str)[N])
    {
        uint32_t value = 0, temp = 0;
        for(size_t i = 0; i < N - 1; i++)
        {
            temp = str[i] + value;
            value = temp << 10;
            temp += value;
            value = temp >> 6;
            value ^= temp;
        }
        temp = value << 3;
        temp += value;
        uint32_t temp2 = temp >> 11;
        temp = temp2 ^ temp;
        temp2 = temp << 15;
        value = temp2 + temp;
        return value;
    }

    inline uint32_t Hash(std::string_view str)
    {
        uint32_t value = 0, temp = 0;
        for(size_t i = 0; i < str.length(); i++)
        {
            temp = str[i] + value;
            value = temp << 10;
            temp += value;
            value = temp >> 6;
            value ^= temp;
        }
        temp = value << 3;
        temp += value;
        uint32_t temp2 = temp >> 11;
        temp = temp2 ^ temp;
        temp2 = temp << 15;
        value = temp2 + temp;
        return value;
    }
}  // namespace js
