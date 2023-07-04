#pragma once

#include "cpp-sdk/objects/IBaseObject.h"
#include "helpers/JS.h"
#include "Class.h"

#include <unordered_map>
#include <vector>

namespace js
{
    class IResource;

    class ClassInstanceCache
    {
    public:
        using Identifier = uint32_t;

    private:
        using InstanceMap = std::unordered_map<IResource*, std::unordered_map<Identifier, js::Persistent<v8::Object>>>;

        static std::vector<ClassInstanceCache*>& All()
        {
            static std::vector<ClassInstanceCache*> all;
            return all;
        }

        Class* class_;
        InstanceMap instanceMap;

        v8::Local<v8::Object> Get(IResource* resource, Identifier identifier)
        {
            v8::Isolate* isolate = v8::Isolate::GetCurrent();
            return instanceMap[resource][identifier].Get(isolate);
        }

        void Add(IResource* resource, Identifier identifier, v8::Local<v8::Object> instance)
        {
            instanceMap[resource].insert({ identifier, js::Persistent<v8::Object>(instance->GetIsolate(), instance) });
        }

    public:
        ClassInstanceCache(Class& class_) : class_(&class_)
        {
            All().push_back(this);
        }

        v8::Local<v8::Object> GetOrCreate(IResource* resource, Identifier identifier, v8::Local<v8::Value> internalFieldValue = v8::Local<v8::Value>());

        static void ClearForResource(IResource* resource)
        {
            for(auto& cache : All()) cache->instanceMap.erase(resource);
        }
    };
}  // namespace js
