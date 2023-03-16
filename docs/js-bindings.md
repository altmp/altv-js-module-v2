# JS bindings

The JS bindings can be found in the `shared/js`, `server/js` and `client/js` folders. These bindings are read and put into the output `shared/src/BindingsMap.cpp` file
by the `tools/generate-bindings.js` script.

That script is executed before building and reads all the JS bindings and inserts them into a C++ map in the output file. The path, name, JS source and scope
of the binding is stored and can then be accessed at runtime from C++ by using `Binding::Get`.

When a resource is started, all the bindings are compiled and evaluated in the Context of that resource, and the exports of them are stored.

## Adding a new binding

To add a new binding simply create a JS file in one of the previously mentioned paths and write the needed logic for the binding.

The access the API there is a global `alt` available in the bindings which can be used.

For logging in the top level of the binding, use the global `debugLog` function, for other places that are called in the lifecycle
of the resource after bindings are first evaluated, the normal `alt.log` can be used.

After the next compilation of the project, the binding will automatically be compiled and evaluated on resource start and show the errors if there are any.

## Binding names

Bindings are named via `<scope>/<filePath>` with the scope being either `shared`, `server` or `client` and the file path being the path to the file beginning from the respective `js` folder.

For example, if you have the file `shared/js/myTest/test.js` then you would get that binding via `Binding::Get("shared/myTest/test.js")`.

> NOTE: Bindings can use the exports of other bindings via the global `requireBinding` JS function. It only takes the path as an argument.
> The path for this works the same as in C++ and it returns an object of the exports of the specified binding.

## Binding exports

If you want to access an export of a binding to use them somewhere else in the code you have to first register the export to save it and make it available later,
get the export from the resource and afterwards use it however needed. These steps will be explained in the following sections.

### Registering a binding export

To register a binding for later use, go to the `js::IResource::RegisterBindingExports` function and add the needed export by calling `RegisterBindingExport` there.

This function takes the unique name of the export as first argument (which is later used to access it),
the file that exports it ([Binding names](#binding-names)) as second argument,
and the third argument is the name of the export in JS.

Example:
```cpp
//                      Unique name           File path          Export name
RegisterBindingExport("funcs:myExport", "shared/myTest/test.js", "myExport");
```

### Getting and using a binding export

To get a previously registered binding somewhere in the code, use `IResource::GetBindingExport` (called on the current resource pointer) with the unique name of the export.
This function also optionally has a template argument to get the export in the right type, which defaults to `v8::Value`.

> NOTE: The type passed to the template argument has to inherit from `v8::Value`, e.g. `v8::Boolean` or `v8::String`.

Example:
```cpp
js::IResource* resource = GetCurrentResource(); // Fictional function, get the current resource pointer via e.g. `ctx.GetResource()`
v8::Local<v8::Function> myExportedFunction = resource->GetBindingExport<v8::Function>("funcs:myExport");
if(myExportedFunction.IsEmpty()) return; // Check if the binding exists, accessing an empty local otherwise crashes.
// Do whatever the export is needed for
```
> NOTE: Remember that classes have the `v8::Function` type as there is no `v8::Class`.

Or if using the [value helpers](helpers.md) is desired instead:
```cpp
js::IResource* resource = GetCurrentResource();
js::Function myExportedFunction = resource->GetBindingExport<v8::Function>("funcs:myExport"); // Implicit conversion to helper type
if(!myExportedFunction.IsValid()) return;
```
