#pragma once

#include <unordered_map>

#include "helpers/JS.h"

#include "v8.h"
#include "cpp-sdk/SDK.h"

namespace js
{
    class IResource;

    enum class EventType
    {
        NONE,

        RESOURCE_START,
        RESOURCE_STOP,

        SIZE
    };

    class Event
    {
    public:
        using EventArgs = Object;
        using EventArgsCallback = std::function<void(const alt::CEvent*, EventArgs&)>;

    private:
        alt::CEvent::Type type;
        EventArgsCallback argsCb;

        static std::unordered_map<alt::CEvent::Type, Event*>& GetEventHandlerMap()
        {
            static std::unordered_map<alt::CEvent::Type, Event*> eventHandlerMap;
            return eventHandlerMap;
        }
        static Event* GetEventHandler(alt::CEvent::Type type)
        {
            auto& eventHandlerMap = GetEventHandlerMap();
            auto it = eventHandlerMap.find(type);
            if(it == eventHandlerMap.end()) return nullptr;
            return it->second;
        }
        static void CallEventBinding(bool custom, int type, EventArgs& args, IResource* resource);

        static void CancelEventCallback(const v8::FunctionCallbackInfo<v8::Value>& info);

    public:
        Event(alt::CEvent::Type _type, EventArgsCallback _argsCb) : type(_type), argsCb(_argsCb)
        {
            GetEventHandlerMap().insert({ type, this });
        }

        static void SendEvent(const alt::CEvent* ev, IResource* resource);
        static void SendEvent(EventType type, EventArgs& args, IResource* resource);
        static void RegisterEvents(IResource* resource);
    };
}  // namespace js
