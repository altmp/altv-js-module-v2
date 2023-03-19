#pragma once

#include <unordered_map>

#include "helpers/JS.h"

namespace js
{
    class FactoryHandler
    {
        static std::unordered_map<alt::IBaseObject::Type, FactoryHandler*>& GetHandlers()
        {
            static std::unordered_map<alt::IBaseObject::Type, FactoryHandler*> handlers;
            return handlers;
        }

    public:
        using FactoryCallback = alt::IBaseObject* (*)(js::Object& args);

    private:
        alt::IBaseObject::Type type;
        FactoryCallback callback;

    public:
        FactoryHandler(alt::IBaseObject::Type type, FactoryCallback callback) : type(type), callback(callback)
        {
            GetHandlers().insert({ type, this });
        }

        static alt::IBaseObject* Create(alt::IBaseObject::Type type, js::Object& args)
        {
            if(!GetHandlers().contains(type)) return nullptr;
            return GetHandlers().at(type)->callback(args);
        }
    };
}  // namespace js
