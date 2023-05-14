# Bindings

To create API bindings for the module there are two different ways to do it, in this article
both will be explained. But as a requisite, the different types of available bindings will be explained.

## Binding types

There are 3 different types of "objects" that bindings can be written for, these would be:

### Modules

Modules are as the name would suggest the same as JavaScript modules, they can be imported and then be used by scripts,
for example the shared module that can be found in `shared/modules/SharedModule.cpp` is the base module for the `@altv/shared`
import (which is inherited by `@altv/server` and `@altv/client`).

These modules implement global functions like `alt.log` which are not associated to any object.

They are created by specifying a new `js::Module` instance globally, which needs a name and callback passed.

The name passed there is only for *internal use* and not the actual name of the module when imported.

The callback is called when getting the *template* for the module, which specifies which functions / properties
it has.

### Namespace
TODO

### Class
TODO

## Template functions

The different types of binding types also have different functions available for specifying the API in their
template, these different functions will be explained here.

### `Template`

All specific templates inherit from the base `Template` class.

### `Template`.`StaticProperty`

This sets a static property on the template, for classes this would be e.g. `Player.getByID` so any function
that is related to the class, but not to any specific instance of it.

For modules and namespaces, this is what is used to specify normal properties on them like `alt.log`.

Automatic bindings are not available for static properties, so they always need to be manually binded.

These can also just be a simple value, instead of a getter / setter pair.

The getter can be omitted, which makes the property read-only.

Usage:
```cpp
static void GetterCallback(js::PropertyContext& ctx) {}
static void SetterCallback(js::PropertyContext& ctx) {}

tpl.StaticProperty("propertyName", GetterCallback, SetterCallback);    // Getter / Setter
tpl.StaticProperty("propertyName2", GetterCallback);                   // Getter (Read-only)
tpl.StaticProperty("propertyName3", 3452);                             // Static value
```
```js
myTemplate.propertyName = 23;      // Calls setter with value `23`
alt.log(myTemplate.propertyName2); // Calls getter and logs return value
alt.log(myTemplate.propertyName3); // Logs the value `3452`
```

### `Template`.`StaticDynamicProperty`
TODO

### `Template`.`StaticLazyProperty`

This sets a lazy static property on the template, these are most the same as `StaticProperty`
with the only exception that this function only accepts a getter, and that this getter is only called once.

On the first access of this property the specified getter is called, and the return value of it is stored on the
object. Every subsequent access just returns that value and does not call the getter again.

So this class is useful for any values that never change and should be preferred for those, as getting that "cached"
value is a lot faster than calling the getter again.

Usage:
```cpp
static void GetterCallback(js::LazyPropertyContext& ctx) {}

tpl.StaticLazyProperty("propertyName", GetterCallback);
```
```js
alt.log(myTemplate.propertyName); // Calls getter and logs return value
alt.log(myTemplate.propertyName); // Does not call the getter again and logs the value of the previous return value
```

### `Template`.`StaticFunction`

This sets a static function on the template, it is similiar to `StaticProperty` as it is not
related to any specific instance of a class.

The only difference that instead of a property which calls a getter / setter, it is a normal function which
can also be called with multiple arguments.

Usage:
```cpp
static void FunctionCallback(js::FunctionContext& ctx) {}

tpl.StaticFunction("functionName", FunctionCallback);
```
```js
myTemplate.functionName("arg1", 23, []); // Calls the function callback with specified arguments
```

### `NamespaceTemplate`

The template used for namespaces, this template has (at this point) no functions
other than the inherited functions from the `Template` base class.

### `ModuleTemplate`

The template used for modules, this template provides functions for adding namespaces
and binding exports to the module.

### `ModuleTemplate`.`Namespace`

This sets a namespace on the template, which acts like an object which can be accessed on the module
often used to provide functions for specific systems like `Timers` or `Events`.

It has multiple overloads for different purposes.

Usage:
```cpp
static js::Namespace myNamespace("MyNamespace", [](js::NamespaceTemplate& tpl) {
    tpl.StaticProperty("myProperty", "test");
});

tpl.Namespace(myNamespace);                          // Sets a namespace on the module from a previously specified namespace template
tpl.Namespace("MyCustomNamespaceName", myNamespace); // Does the same as above, but uses the name passed instead of the namespace name
tpl.Namespace("MyOtherNamespace");                   // Just creates an empty namespace on the module, this is used for namespaces which are only extended from JS bindings
```
```js
alt.log(myTemplate.MyNamespace.myProperty); // Logs `test`
```

### `ModuleTemplate`.`StaticBindingExport`

This sets a value on the template, which is retreived from a binding export specified in the JS bindings.

This can be of any type like a property, class or function, but the binding export name passed here has to be registered in a JS binding,
otherwise this value will always be undefined.

Usage:
```cpp
tpl.StaticBindingExport("myBinding", "myBindingExport:myValue"); // Sets the value of the `myBindingExport:myValue` binding export
```

### `ClassTemplate`
TODO

## Automatic bindings

When appropriate, bindings can be automatically generated from the C++ method itself.

These automatic bindings can only be generated for classes from the alt:V C++ SDK and their respective JS classes.

To add such a method or property it looks like this: (Example taken from the `Player` class in shared)
```cpp
tpl.Property<&alt::IPlayer::GetHealth>("health");
```

To add this kind of binding, there is no other code needed than that single line, because the C++ function will automatically
be wrapped and the arguments will be converted from C++ to JS when calling it and back to JS when returning a value.

For special cases, like overloads for example it is still needed to write manual bindings, but as this is only rarely the case
most methods and properties can be added to the API via these automatic bindings. The implementation of these automatic bindings
can be found in `shared/helpers/CallContext.h`.

Very simply put, the argument and return types are extracted from the function pointer passed as a template and will be converted to
their C++ / JS counterpart when called and call the respective method on the `this` object of the object it is called on.

## Manual bindings
TODO

### `CallContext`
TODO

### `FunctionContext`
TODO

### `PropertyContext`
TODO

### `LazyPropertyContext`
TODO

### `DynamicPropertyContext`
TODO
