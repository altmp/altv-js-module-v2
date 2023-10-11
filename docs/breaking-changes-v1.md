# Breaking Changes Related to Imports

In version 1 (`v1`), default imports were supported for `alt-server`, `alt-client`, `alt-shared`, `alt`, and `natives`. However, with the introduction of the v2 module (`v2`), default imports are no longer functional. To adapt to the new changes, you should update your import statements to use the `import * as X from "x"` syntax.

## Example

### Before (Incorrect):

```javascript
import alt from "alt-client";
```

### After (Correct):

```javascript
import * as alt from "alt-client";
```

# Profiler

The Profiler class in `v1` is now a namespace in `v2` meaning: You can't create a new `Profiler` class instance. Right now, only `takeHeapSnapshot` is available as static method.

# MemoryBuffer class

In `v1`, the `MemoryBuffer` class had a property named `address`. The memory address which was returned by that property was not returning the value you did expect it to return - therefore it has been removed in v2. However, i still added the property and made it log an error message for the time being.

# Natives

In `v1`, some natives return an array with first element being original return value of the native and other values being refs in native parameters. `v2` follows similar approach, but emits first element if the native only uses refs and doesn't return anything.

## Example

### Before (Incorrect):

```javascript
const [, minVR, maxVR] = natives.getModelDimensions(model);
```

### After (Correct):

```javascript
const [minVR, maxVR] = natives.getModelDimensions(model);
```
