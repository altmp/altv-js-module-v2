# JS bindings

The JS bindings can be found in the `shared/js`, `server/js` and `client/js` folders. These bindings are read and put into the output `build/BindingsMap.cpp` file
by the `tools/generate-bindings.js` script.

That script is executed before building and reads all the JS bindings and inserts them into a C++ map in the output file. The path, name, JS source and scope
of the binding is stored and can then be accessed at runtime from C++ by using `Binding::Get`.

When a resource is started, all the bindings are compiled and evaluated in the Context of that resource, and the binding exports of them are stored.

## Adding a new binding

To add a new binding simply create a JS file in one of the previously mentioned paths and write the needed logic for the binding.

The access the API there is a global `alt` available in the bindings which can be used.

To use logging in a bindings file, make sure that file calls `requireBinding("shared/logging.js")` before, so that alt.log is available.

After the next compilation of the project, the binding will automatically be compiled and evaluated on resource start and show the errors if there are any.

### Compatibility bindings

Bindings that should only be run in v1 compatibility mode should go into the `compatibility` subfolder in their respective scope.

The module automatically checks whether a binding is in this folder and compatibility mode is enabled, and if it is not, the binding is not loaded.

## Binding names

Bindings are named via `<scope>/<filePath>` with the scope being either `shared`, `server` or `client` and the file path being the path to the file beginning from the respective `js` folder.

For example, if you have the file `shared/js/myTest/test.js` then you would get that binding via `Binding::Get("shared/myTest/test.js")`.

> NOTE: Bindings can use the exports of other bindings via the global `requireBinding` JS function. It only takes the path as an argument.
> The path for this works the same as in C++ and it returns an object of the exports of the specified binding.

## Binding exports

If you want to access an export of a binding to use them somewhere else in the code you have to first register the export to save it and make it available later,
get the export from the resource and afterwards use it however needed. These steps will be explained in the following sections.

### Registering a binding export

To register a binding export for later use, call the `cppBindings.registerExport` function in the binding.

It takes the enum value of the export as the first argument, and the value as the second argument.

So we have to add an enum value to the `BindingExport` enum, like shown here: (found in `shared/src/IBindingExportHandler.h`)
```cpp
enum class BindingExport : uint8_t
{
    // Functions
    ON_EVENT,
    TICK,
    // ... and so on

    MY_EXPORT, // Our own enum value added here!

    SIZE,
};
```

> NOTE: Generally the order of the enum is not important, but the `SIZE` element has to always be the last!

Then the enum value is available on the `cppBindings.BindingExport` object in our binding, which we can then use to register our export:

Example:
```js
function myExport() {
    // do something
}
cppBindings.registerExport(cppBindings.BindingExport.MY_EXPORT, myExport);
```

### Getting and using a binding export

To get a previously registered binding somewhere in the code, use `IResource::GetBindingExport` (called on the current resource pointer) with the unique name of the export.
This function also optionally has a template argument to get the export in the right type, which defaults to `v8::Value`.

> NOTE: The type passed to the template argument has to inherit from `v8::Value`, e.g. `v8::Boolean` or `v8::String`.

Example:
```cpp
js::IResource* resource = GetCurrentResource(); // Fictional function, get the current resource pointer via e.g. `ctx.GetResource()`
v8::Local<v8::Function> myExportedFunction = resource->GetBindingExport<v8::Function>(js::BindingExport::MY_EXPORT);
if(myExportedFunction.IsEmpty()) return; // Check if the binding exists, accessing an empty local otherwise crashes.
// Do whatever the export is needed for
```
> NOTE: Remember that classes have the `v8::Function` type as there is no `v8::Class`.

Or if using the [value helpers](helpers.md) is desired instead:
```cpp
js::IResource* resource = GetCurrentResource();
js::Function myExportedFunction = resource->GetBindingExport<v8::Function>(js::BindingExport::MY_EXPORT); // Implicit conversion to helper type
if(!myExportedFunction.IsValid()) return;
```
