#include "JS.h"
#include "interfaces/IResource.h"

#include <filesystem>

static std::string PrettifyFilePath(js::IResource* resource, std::string path)
{
    if(path.starts_with("file:///")) path = path.substr(8);

    std::filesystem::path fsPath(path);
    if(fsPath.is_absolute())
    {
        std::string resourcePath = resource->GetResource()->GetPath();
        std::replace(path.begin(), path.end(), '\\', '/');
        std::replace(resourcePath.begin(), resourcePath.end(), '\\', '/');
        if(path.starts_with(resourcePath)) return path.substr(resourcePath.length() + 1);
        else
            return path;
    }
    else
        return path;
}

js::SourceLocation js::GetCurrentSourceLocation(IResource* resource, int framesToSkip)
{
    v8::Isolate* isolate = resource->GetIsolate();
    v8::Local<v8::StackTrace> stackTrace = v8::StackTrace::CurrentStackTrace(isolate, framesToSkip + 5);
    for(int i = framesToSkip; i < stackTrace->GetFrameCount(); i++)
    {
        v8::Local<v8::StackFrame> frame = stackTrace->GetFrame(isolate, i);
        if(!frame->IsUserJavaScript()) continue;
        std::string scriptName = CppValue(frame->GetScriptName());
        if(scriptName.empty() || scriptName.starts_with("internal:")) continue;
        return SourceLocation{ PrettifyFilePath(resource, scriptName), frame->GetLineNumber() };
    }
    return SourceLocation{};
}

void js::TryCatch::PrintError()
{
    v8::Isolate* isolate = v8::Isolate::GetCurrent();
    v8::Local<v8::Context> context = isolate->GetEnteredOrMicrotaskContext();
    IResource* resource = IResource::GetFromContext(context);
    v8::Local<v8::Value> exception = tryCatch.Exception();
    v8::Local<v8::Message> message = tryCatch.Message();
    if(exception.IsEmpty() || message.IsEmpty()) return;

    v8::MaybeLocal<v8::String> maybeSourceLine = message->GetSourceLine(context);
    std::string sourceLine = maybeSourceLine.IsEmpty() ? "" : *v8::String::Utf8Value(isolate, maybeSourceLine.ToLocalChecked());
    int32_t line = message->GetLineNumber(context).FromMaybe(0);
    std::string lineStr = line == 0 ? "<unknown>" : std::to_string(line);
    std::string file = *v8::String::Utf8Value(isolate, message->GetScriptOrigin().ResourceName());
    if(file.empty() || file == "undefined") file = "<unknown>";
    else
        file = PrettifyFilePath(resource, file);

    v8::MaybeLocal<v8::Value> stackTrace = tryCatch.StackTrace(context);
    std::string stack = stackTrace.IsEmpty() ? "" : *v8::String::Utf8Value(isolate, stackTrace.ToLocalChecked());
    std::string exceptionStr = *v8::String::Utf8Value(isolate, exception);

    Logger::Error("[JS] Exception caught in resource '" + resource->GetResource()->GetName() + "' in file '" + file + "' at line " + lineStr);
    if(!exceptionStr.empty() && stack.empty()) Logger::Error("[JS]", exceptionStr);
    if(!stack.empty()) Logger::Error("[JS]", stack);

    js::Event::EventArgs args;
    args.Set("error", exceptionStr);
    args.Set("stack", stack);
    js::Event::SendEvent(js::EventType::ERROR, args, resource);
}

js::IResource* js::Value::GetResource()
{
    if(!resource) resource = IResource::GetFromContext(GetContext());
    return resource;
}

js::Type js::Object::GetType(const std::string& key)
{
    if(typeCache.contains(key)) return typeCache.at(key);
    v8::MaybeLocal<v8::Value> maybeVal = object->Get(context, js::JSValue(key));
    v8::Local<v8::Value> val;
    if(!maybeVal.ToLocal(&val)) return js::Type::INVALID;
    js::Type type = js::GetType(val, GetResource());
    typeCache.insert({ key, type });
    return type;
}
