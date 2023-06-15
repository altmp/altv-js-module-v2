#pragma once

#include <unordered_map>
#include <functional>
#include <iostream>
#include <vector>

#include "v8.h"

#include "helpers/JS.h"
#include "helpers/Template.h"
#include "helpers/CallContext.h"
#include "interfaces/IScriptObjectHandler.h"

namespace js
{
    class Class
    {
        static uint16_t GetNextClassId()
        {
            static uint16_t nextId = 100;  // Start with an offset, if we need class ids for other objects in the future
            return nextId++;
        }

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
        FunctionCallback ctor = nullptr;
        ClassInitializationCallback initCb;
        std::unordered_map<v8::Isolate*, ClassTemplate> templateMap;
        int internalFieldCount = 0;
        uint16_t classId = GetNextClassId();

        void Register(v8::Isolate* isolate);

    public:
        Class(const std::string& _name, FunctionCallback _ctor, ClassInitializationCallback _cb, bool hasExtraExternalField = false)
            : name(_name), ctor(_ctor), initCb(_cb), internalFieldCount(hasExtraExternalField ? 2 : 0)
        {
            GetAll().push_back(this);
        }
        Class(const std::string& _name, Class* _parent, FunctionCallback _ctor, ClassInitializationCallback _cb, bool hasExtraExternalField = false)
            : name(_name), parentClass(_parent), ctor(_ctor), initCb(_cb), internalFieldCount(hasExtraExternalField ? 2 : 0)
        {
            GetAll().push_back(this);
        }
        Class(const std::string& _name, ClassInitializationCallback _cb, bool hasExtraExternalField = false) : name(_name), initCb(_cb), internalFieldCount(hasExtraExternalField ? 2 : 0)
        {
            GetAll().push_back(this);
        }

        uint16_t GetClassId() const
        {
            return classId;
        }
        const std::string& GetName() const
        {
            return name;
        }
        Class* GetParentClass() const
        {
            return parentClass;
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

        v8::Local<v8::Object> Create(v8::Local<v8::Context> context, void* extraInternalFieldValue = nullptr)
        {
            v8::Local<v8::Object> obj = templateMap.at(context->GetIsolate()).Get()->InstanceTemplate()->NewInstance(context).ToLocalChecked();
            if(extraInternalFieldValue) obj->SetAlignedPointerInInternalField(1, extraInternalFieldValue);
            return obj;
        }

        Persistent<v8::Object> MakePersistent(v8::Local<v8::Object> value)
        {
            Persistent<v8::Object> persistent(value->GetIsolate(), value);
            persistent.SetWrapperClassId(classId);
            return persistent;
        }

        static Class* GetByClassId(uint16_t id);

        static void Initialize(v8::Isolate* isolate);
        static void Cleanup(v8::Isolate* isolate);
    };

}  // namespace js
