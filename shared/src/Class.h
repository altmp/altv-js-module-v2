#pragma once

#include <unordered_map>
#include <functional>
#include <iostream>
#include <vector>

#include "v8.h"

#include "helpers/JS.h"
#include "helpers/Template.h"
#include "helpers/FunctionContext.h"
#include "interfaces/IScriptObjectHandler.h"

namespace js
{
    class Class
    {
        static std::vector<Class*>& GetAll()
        {
            static std::vector<Class*> classes;
            return classes;
        }

    public:
        using ClassInitializationCallback = std::function<void(ClassTemplate&)>;

    private:
        std::string name;
        Class* parentClass = nullptr;
        FunctionCallback ctor;
        ClassInitializationCallback initCb;
        std::unordered_map<v8::Isolate*, ClassTemplate> templateMap;
        int internalFieldCount = 0;

        void Register(v8::Isolate* isolate, ClassTemplate& tpl);

    public:
        Class(const std::string& _name, FunctionCallback _ctor, ClassInitializationCallback _cb) : name(_name), ctor(_ctor), initCb(_cb)
        {
            GetAll().push_back(this);
        }
        Class(const std::string& _name, Class* _parent, FunctionCallback _ctor, ClassInitializationCallback _cb) : name(_name), parentClass(_parent), ctor(_ctor), initCb(_cb)
        {
            GetAll().push_back(this);
        }

        const std::string& GetName() const
        {
            return name;
        }
        ClassTemplate& GetTemplate(v8::Isolate* isolate)
        {
            return templateMap.at(isolate);
        }
        v8::Local<v8::ObjectTemplate> GetPrototypeTemplate(v8::Isolate* isolate)
        {
            return templateMap.at(isolate).Get()->PrototypeTemplate();
        }

        void SetInternalFieldCount(int count)
        {
            internalFieldCount = count;
        }

        static void Initialize(v8::Isolate* isolate);
        static void Cleanup(v8::Isolate* isolate);
    };

}  // namespace js
