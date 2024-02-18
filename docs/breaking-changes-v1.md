# Profiler

The Profiler class in `v1` is now a namespace in `v2` meaning: You can't create a new `Profiler` class instance. Right now, only `takeHeapSnapshot` is available as static method.

# MemoryBuffer class

In `v1`, the `MemoryBuffer` class had a property named `address`. The memory address which was returned by that property was not returning the value you did expect it to return - therefore it has been removed in v2. However, i still added the property and made it log an error message for the time being.
