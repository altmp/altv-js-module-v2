#pragma once

#include <string>

namespace js
{
    class Buffer
    {
        uint8_t* buf = nullptr;
        size_t size = 0;

        void ThrowOutOfBoundsException()
        {
            v8::Isolate* isolate = v8::Isolate::GetCurrent();
            isolate->ThrowException(v8::Exception::Error(v8::String::NewFromUtf8(isolate, "Buffer offset is out of bounds").ToLocalChecked()));
        }

    public:
        Buffer(size_t _size) : size(_size)
        {
            buf = new uint8_t[_size];
        }
        Buffer(uint8_t* _data, size_t _size, bool copy = true) : size(_size)
        {
            if(copy)
            {
                buf = new uint8_t[_size];
                memcpy(buf, _data, _size);
            }
            else
                buf = _data;
        }
        ~Buffer()
        {
            delete[] buf;
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
                ThrowOutOfBoundsException();
                return false;
            }
            val = *reinterpret_cast<T*>((uintptr_t)buf + offset);
            return true;
        }
        bool ReadString(size_t offset, size_t length, std::string& val)
        {
            if(offset + length > size)
            {
                ThrowOutOfBoundsException();
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
                ThrowOutOfBoundsException();
                return false;
            }
            *reinterpret_cast<T*>((uintptr_t)buf + offset) = val;
            return true;
        }
        bool WriteString(size_t offset, const std::string& val)
        {
            if(offset + val.length() > size)
            {
                ThrowOutOfBoundsException();
                return false;
            }
            memcpy((char*)buf + offset, val.c_str(), val.length());
            return true;
        }
    };
}  // namespace js
