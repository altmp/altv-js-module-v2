#pragma once

#include <array>
#include <type_traits>
#include <queue>

#include "v8.h"
#include "cpp-sdk/SDK.h"

#include "Bindings.h"
#include "Class.h"
#include "Module.h"
#include "IScriptObjectHandler.h"
#include "ICompatibilityHandler.h"
#include "IBindingExportHandler.h"
#include "Event.h"
#include "Logger.h"
#include "helpers/Hash.h"
#include "helpers/ClassInstanceCache.h"
#include "helpers/Buffer.h"

namespace js
{
    class IResource : public IScriptObjectHandler, public ICompatibilityHandler, public IBindingExportHandler
    {
    public:
        using NextTickCallback = std::function<void()>;

    protected:
        static constexpr int ContextInternalFieldIdx = 1;

        static void RequireBindingNamespaceWrapper(FunctionContext& ctx);

        v8::Isolate* isolate;
        Persistent<v8::Context> context;
        std::unordered_map<Buffer*, Persistent<v8::Object>> ownedBuffers;
        bool rawEmitEnabled = false;
        std::queue<NextTickCallback> nextTickCallbacks;

        std::vector<Promise*> promises;

        void Initialize()
        {
            context.Get(isolate)->SetAlignedPointerInEmbedderData(ContextInternalFieldIdx, this);
            ICompatibilityHandler::Initialize();
            IScriptObjectHandler::Initialize(context.Get(isolate));
        }

        virtual void Reset()
        {
            Binding::CleanupForResource(this);
            Module::CleanupForResource(this);
            ClassInstanceCache::ClearForResource(this);
            IScriptObjectHandler::Reset();
            ICompatibilityHandler::Reset();
            IBindingExportHandler::Reset();

            for(Promise* promise : promises) delete promise;
            promises.clear();

            isolate = nullptr;

            context.Reset();
            ownedBuffers.clear();
            rawEmitEnabled = false;
            nextTickCallbacks = {};
        }

        void InitializeBinding(Binding* binding);

        void ProcessNextTickCallbacks()
        {
            while(!nextTickCallbacks.empty())
            {
                NextTickCallback& callback = nextTickCallbacks.front();
                callback();
                nextTickCallbacks.pop();
            }
        }

    public:
        class Scope
        {
            v8::Locker locker;
            v8::HandleScope handleScope;
            v8::Isolate::Scope isolateScope;
            v8::Context::Scope contextScope;

        public:
            Scope(IResource* _resource) : locker(_resource->GetIsolate()), handleScope(_resource->GetIsolate()), isolateScope(_resource->GetIsolate()), contextScope(_resource->GetContext())
            {
            }
            ~Scope() = default;
        };

        IResource(v8::Isolate* _isolate) : isolate(_isolate) {}
        virtual ~IResource() = default;

        template<class T>
        T* As()
        {
            return dynamic_cast<T*>(this);
        }

        v8::Isolate* GetIsolate() const
        {
            return isolate;
        }
        v8::Local<v8::Context> GetContext() const
        {
            return context.Get(isolate);
        }

        virtual void RunEventLoop() = 0;
        virtual const std::string& GetName() const = 0;
        virtual const std::string& GetPath() const = 0;
        virtual alt::IResource* GetResource() const = 0;

        void InitializeBindings(Binding::Scope scope, Module& altModule);

        v8::Local<v8::Object> CreateVector3(alt::Vector3f vec)
        {
            v8::Local<v8::Function> vector3 = GetBindingExport<v8::Function>(BindingExport::VECTOR3_CLASS);
            if(vector3.IsEmpty()) return v8::Local<v8::Object>();

            std::array<v8::Local<v8::Value>, 3> args = { js::JSValue(vec[0]), js::JSValue(vec[1]), js::JSValue(vec[2]) };
            return vector3->NewInstance(GetContext(), args.size(), args.data()).ToLocalChecked();
        }
        v8::Local<v8::Object> CreateVector2(alt::Vector2f vec)
        {
            v8::Local<v8::Function> vector2 = GetBindingExport<v8::Function>(BindingExport::VECTOR2_CLASS);
            if(vector2.IsEmpty()) return v8::Local<v8::Object>();

            std::array<v8::Local<v8::Value>, 2> args = { js::JSValue(vec[0]), js::JSValue(vec[1]) };
            return vector2->NewInstance(GetContext(), args.size(), args.data()).ToLocalChecked();
        }
        v8::Local<v8::Object> CreateRGBA(alt::RGBA rgba)
        {
            v8::Local<v8::Function> rgbaClass = GetBindingExport<v8::Function>(BindingExport::RGBA_CLASS);
            if(rgbaClass.IsEmpty()) return v8::Local<v8::Object>();

            std::array<v8::Local<v8::Value>, 4> args = { js::JSValue(rgba.r), js::JSValue(rgba.g), js::JSValue(rgba.b), js::JSValue(rgba.a) };
            return rgbaClass->NewInstance(GetContext(), args.size(), args.data()).ToLocalChecked();
        }
        v8::Local<v8::Object> CreateQuaternion(alt::Quaternion quaternion)
        {
            v8::Local<v8::Function> quaternionClass = GetBindingExport<v8::Function>(BindingExport::QUATERNION_CLASS);
            if(quaternionClass.IsEmpty()) return v8::Local<v8::Object>();

            std::array<v8::Local<v8::Value>, 4> args = { js::JSValue(quaternion.x), js::JSValue(quaternion.y), js::JSValue(quaternion.z), js::JSValue(quaternion.w) };
            return quaternionClass->NewInstance(GetContext(), args.size(), args.data()).ToLocalChecked();
        }
        bool IsVector3(v8::Local<v8::Value> val)
        {
            v8::Local<v8::Function> vector3 = GetBindingExport<v8::Function>(BindingExport::VECTOR3_CLASS);
            if(vector3.IsEmpty()) return false;

            return val->IsObject() && val.As<v8::Object>()->InstanceOf(GetContext(), vector3).ToChecked();
        }
        bool IsVector2(v8::Local<v8::Value> val)
        {
            v8::Local<v8::Function> vector2 = GetBindingExport<v8::Function>(BindingExport::VECTOR2_CLASS);
            if(vector2.IsEmpty()) return false;

            return val->IsObject() && val.As<v8::Object>()->InstanceOf(GetContext(), vector2).ToChecked();
        }
        bool IsRGBA(v8::Local<v8::Value> val)
        {
            v8::Local<v8::Function> rgbaClass = GetBindingExport<v8::Function>(BindingExport::RGBA_CLASS);
            if(rgbaClass.IsEmpty()) return false;

            return val->IsObject() && val.As<v8::Object>()->InstanceOf(GetContext(), rgbaClass).ToChecked();
        }
        bool IsQuaternion(v8::Local<v8::Value> val)
        {
            v8::Local<v8::Function> quaternionClass = GetBindingExport<v8::Function>(BindingExport::QUATERNION_CLASS);
            if(quaternionClass.IsEmpty()) return false;

            return val->IsObject() && val.As<v8::Object>()->InstanceOf(GetContext(), quaternionClass).ToChecked();
        }
        bool IsBaseObject(v8::Local<v8::Value> val);
        bool IsBuffer(v8::Local<v8::Value> val);

        void AddOwnedBuffer(Buffer* buffer, v8::Local<v8::Object> obj);
        void RemoveOwnedBuffer(Buffer* buffer)
        {
            ownedBuffers.erase(buffer);
        }
        auto& GetOwnedBuffers()
        {
            return ownedBuffers;
        }

        bool IsRawEmitEnabled() const
        {
            return rawEmitEnabled;
        }

        void ToggleRawEmit(bool toggle)
        {
            rawEmitEnabled = toggle;
        }

        void PushNextTickCallback(NextTickCallback&& callback)
        {
            nextTickCallbacks.push(std::move(callback));
        }

        Promise* CreatePromise()
        {
            Promise* promise = new Promise(this);
            promises.push_back(promise);
            return promise;
        }
        void RemovePromise(Promise* promise)
        {
            auto it = std::find(promises.begin(), promises.end(), promise);
            if(it != promises.end()) promises.erase(it);
        }

        template<class ResourceType = js::IResource>
        static ResourceType* GetFromContext(v8::Local<v8::Context> context)
        {
            return dynamic_cast<ResourceType*>(static_cast<IResource*>(context->GetAlignedPointerFromEmbedderData(ContextInternalFieldIdx)));
        }
        template<class ResourceType = js::IResource>
        static ResourceType* GetCurrent()
        {
            v8::Isolate* isolate = v8::Isolate::GetCurrent();
            if(!isolate) return nullptr;
            v8::Local<v8::Context> context = isolate->GetEnteredOrMicrotaskContext();
            if(context.IsEmpty()) return nullptr;
            return GetFromContext<ResourceType>(context);
        }
    };
}  // namespace js
