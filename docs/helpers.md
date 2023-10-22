# Helpers

To make working with JS values a little easier, there are wrappers available for "complex" JS types, such as Arrays, Objects and Functions,
which provide an API that wraps the native V8 API but makes it a lot easier to work with.

## Value

This is the interface that all value helpers share. It provides only the `IsValid()` method,
which returns whether the underlying JS object is valid. (Empty handle or not)

## Object

The `js::Object` class wraps `v8::Object` values.

API overview:
```cpp
// Creates with an automatically created underlying JS object
js::Object obj;

// Creates an object from an existing JS object
v8::Local<v8::Object> jsObj;
js::Object objFromValue(jsObj);

// Gets a value from the object with the specified key (falls back to default constructor if conversion failed)
// Fictional JS object: `{ myKey: 23, myOtherKey: "my key!" }`
int myKey = obj.Get<int>("myKey");
std::string myOtherKey = obj.Get<std::string>("myOtherKey");
js::Logger::Info(myKey, "|", myOtherKey); // Logs `23 | my key!`

// Sets a value on the object with the specified key
// Allows passing any type convertible via `js::JSValue`
objVal.Set("myKey", 42);
objVal.Set("myOtherKey", "my key!");
v8::Local<v8::Value> jsVal;
objVal.Set("anotherKey", jsVal);

// Gets the underlying v8 value
v8::Local<v8::Object> v8Obj = obj.Get();
```

## Array

The `js::Array` class wraps `v8::Array` values.

API overview:
```cpp
// Creates with an automatically created underlying JS array
js::Array array;

// Optionally, a size for the array can be passed
js::Array arrayWithSize(64); // .length == 64

// Creates an array from an existing JS array
v8::Local<v8::Array> jsArray;
js::Array arrayFromValue(jsArray);

// Gets a value from the array at the specified index (falls back to default constructor if conversion failed)
// Fictional JS array: `[ "test123", 53 ]`
std::string firstVal = array.Get<std::string>(0);
int secondVal = array.Get<int>(1);
js::Logger::Info(firstVal, "|", secondVal); // Logs `test123 | 53`

// Sets a value in the array at the specified index
// Allows passing any type convertible via `js::JSValue`
array.Set(0, 187);
array.Set(1, "test value");
v8::Local<v8::Value> jsVal;
array.Set(2, jsVal);

// Alternatively, if its desired to just push a value to the array end
array.Push("value");

// Gets the underlying v8 value
v8::Local<v8::Array> v8Array = array.Get();
```

## Function

The `js::Function` class wraps `v8::Function` values.

API overview:
```cpp
// Creates a function from an existing JS function
v8::Local<v8::Function> jsFunc;
js::Function func(jsFunc);

// Calls the function with the specified arguments (returns an empty optional if the call failed or the return value can't be converted to the type)
// The template parameter specifies the type of the return value, if omitted defaults to void (no return value)
// Fictional JS function: `function myFunction(someNumber, someString) { return someNumber + 10; }`
std::optional<int32_t> result = func.Call<int32_t>(25, "Some string");
if(!result) return;
int32_t resultVal = result.value();
js::Logger::Info(resultVal); // Logs `35`

// Optionally, the `this` value for the function call can also be specified as the first argument
v8::Local<v8::Object> thisObject;
func.Call(thisObject, 25, "Some string");

// Gets the underlying v8 value
v8::Local<v8::Function> v8Function = func.Get();
```

## Promise

The `js::Promise` class wraps `v8::Promise::Resolver` values.

API overview:
```cpp
// Creates a new promise
js::Promise* promise = resource->CreatePromise();

// Pass the promise to some async operation
std::function<void()> imaginaryLambda = [promise]() {
    // ... do something
    delete promise;
};

// Resolve the promise with the given value
promise->Resolve("success!");

// Reject the promise with the given value
promise->Reject("no success :(");

// Gets the underlying v8 value
v8::Local<v8::Promise> v8Promise = promise->Get();
```
