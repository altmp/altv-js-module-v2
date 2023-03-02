# JS bindings

The JS bindings can be found in the `shared/js`, `server/js` and `client/js` folders. These bindings are read and put into the output `tools/out/JSBindings.h` file
by the `tools/generate-bindings.js` script.

That script is executed before building and reads all the JS bindings and inserts them into a C++ map in the output file. The path, name, JS source and scope
of the binding is stored and can then be accessed at runtime from C++ by using `JSBindings::Get`.

If a file is duplicate on shared/client/server, the files are merged by the script so that we can specify a file on shared and extend it on both sides without
having to use e.g. `alt.isClient` checks.
