#pragma once

#include "helpers/JS.h"

#include <string>

namespace js
{
    class Buffer
    {
        uint8_t* buf = nullptr;
        size_t size = 0;

    public:
        Buffer(size_t _size) : size(size)
        {
            buf = new uint8_t[_size];
        }
        ~Buffer()
        {
            delete buf;
        }

        uint8_t* GetBuffer()
        {
            return buf;
        }
        size_t GetSize()
        {
            return size;
        }

        template<typename T>
        bool Read(size_t offset, T& val)
        {
            if(offset + sizeof(T) > size)
            {
                js::Throw("Buffer offset is out of bounds");
                return false;
            }
            val = *reinterpret_cast<T*>((uintptr_t)buf + offset);
            return true;
        }
        bool ReadString(size_t offset, size_t length, std::string& val)
        {
            if(offset + length > size)
            {
                js::Throw("Buffer offset is out of bounds");
                return false;
            }
            val = std::string((char*)buf + offset, length);
            return true;
        }

        template<typename T>
        bool Write(size_t offset, const T& val)
        {
            if(offset + sizeof(T) > size)
            {
                js::Throw("Buffer offset is out of bounds");
                return false;
            }
            *reinterpret_cast<T*>((uintptr_t)buf + offset) = val;
            return true;
        }
        bool WriteString(size_t offset, const std::string& val)
        {
            if(offset + val.length() > size)
            {
                js::Throw("Buffer offset is out of bounds");
                return false;
            }
            memcpy((char*)buf + offset, val.c_str(), val.length());
            return true;
        }
    };
}  // namespace js
