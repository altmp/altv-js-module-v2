# Adding events

When a new event is added to the C++ SDK, it has to be manually added to the events handled by the module, this process is relatively easy though.

A part of the implementation for every event has to be done in C++ to transform the data of the event into JS values, and the other part of it
is done in JS to add the event to the API.

## C++

To add a new event, create a new file (or add it to an already existing file, if appropriate) in the `src/events` folder of the scope of the event
(events only available on server should be in `server`, if available on sides in `shared` etc.) and create a new `js::Event` instance there in the
global scope of the file.

The first argument to the constructor is the type of the event, that can be found in the `alt::CEvent::Type` enum.

The second argument is the callback that is called when that event is received, to transform its data to the JS representation of it.

That callback receives the event pointer as first argument and the JS args object as second argument, to which we will add the JS values of the event data.
To get started, `static_cast` the event received there to the appropriate event from the `cpp-sdk/events` folder, so we can access its data, and then add
that data to the JS args by calling `args.Set("NameOfArg", e->GetSomeData())`.

Example:
```cpp
static js::Event consoleCommandEvent(alt::CEvent::Type::CONSOLE_COMMAND_EVENT, [](const alt::CEvent* ev, js::Event::EventArgs& args)
{
    auto e = static_cast<const alt::CConsoleCommandEvent*>(ev); // Cast it to the correct class
    args.Set("command", e->GetName()); // Add the command name to the arguments
    args.Set("args", e->GetArgs());    // Add the command args to the arguments
});
```

### Argument naming

To keep argument names consistent in the API, here are a few rules for naming the arguments.

1. Argument names have to use camelCase
2. Argument names should (if appropriate) be the same name as in the C++ SDK
3. If an event is related to a player, the argument that holds the player should be named `player`

## JS

Now, to make the event available via the API, go to the `js/events` folder of the correct scope, and as above add a new file or add onto an existing file.

Here we need to require the event class from our JS bindings, by calling `const { Event } = requireBinding("shared/events.js")`

And can then register the event by calling `Event.register(EventType, "EventName")`

> NOTE: The event type is available via the `alt.Enums.EventType` enum and is named the same way as the enum type in C++.

Example:
```js
const { Event } = requireBinding("shared/events.js");

Event.register(alt.Enums.EventType.CONSOLE_COMMAND_EVENT, "ConsoleCommand");
```

Now the event will be available in the API by calling `alt.Events.onConsoleCommand`

### Event naming

To keep the event names consistent, here are a few rules on how to name the events.

1. Event names have to use PascalCase. (Actually in the end it's camelCase, because the `on` is appendend automatically when its added to the API)
2. If the event name includes a verb, it should be at the end. (E.g. `VehicleEnter` instead of `EnterVehicle`) (Exceptions allowed where the verb is not in infinitive form)

## Custom events

If we want to add events that are not sent by alt:V, then these are also easy to add.

First of all, we don't need to add the `js::Event` handler as with alt:V events, because we are handling this data ourselves with a custom event.

When we want to register a custom event, we simply go to the C++ `js::EventType` enum and add a new event type there after the last type added, but before the `SIZE` type.

Then we can register the event in the JS side by calling `Event.register` with `true` as the third argument.

To invoke our custom event, we need to call `Event.invoke` also with `true` as the third argument.

Example:
```js
const { Event } = requireBinding("shared/events.js");

Event.register(alt.Enums.CustomEventType.MY_CUSTOM_EVENT, "CustomEvent"); // Assuming we added `MY_CUSTOM_EVENT` to the js::EventType enum in C++

alt.onSomeOtherEvent(({ someState }) => {
    if(someState) Event.invoke(alt.Enums.CustomEventType.MY_CUSTOM_EVENT, { myData: 5 }, true);
});
```

Alternatively, if the event should be invoked from C++, use the `js::Event::SendEvent` function.

Example:
```cpp
js::EventArgs args;
args.Set("myData", 5);
alt::Event::SendEvent(js::EventType::MY_CUSTOM_EVENT, args, resource);
```

As a real example on how a custom event is implemented, check [this commit](https://github.com/LeonMrBonnie/altv-js-module-v2/commit/df577247a03fae10059b653452d8121998c41e37).
