#pragma once

#include <queue>

#include "v8.h"
#include "helpers/JS.h"

class IExceptionHandler
{
    struct PromiseRejection
    {
        js::Persistent<v8::Promise> promise;
        js::Persistent<v8::Value> value;
        js::SourceLocation location;
        js::StackTrace stackTrace;
    };

    std::vector<PromiseRejection> promiseRejections;

    void OnPromiseRejectedWithoutHandler(v8::PromiseRejectMessage& message);
    void OnPromiseHandlerAdded(v8::PromiseRejectMessage& message);
    void OnPromiseRejectAfterResolve(v8::PromiseRejectMessage& message);
    void OnPromiseResolveAfterResolve(v8::PromiseRejectMessage& message);

protected:
    void ProcessExceptions();
    void Reset();

public:
    void OnPromiseRejected(v8::PromiseRejectMessage& message);
};
