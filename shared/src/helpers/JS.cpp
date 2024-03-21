#include "JS.h"
#include "interfaces/IResource.h"

#include <filesystem>
#include <sstream>

void js::internal::RunEventLoop()
{
    GetCurrentResource()->RunEventLoop();
}

static std::string PrettifyFilePath(js::IResource* resource, std::string path)
{
    if(path.starts_with("file:///")) path = path.substr(8);

    std::filesystem::path fsPath(path);
    if(fsPath.is_absolute())
    {
        std::string resourcePath = resource->GetPath();
        std::replace(path.begin(), path.end(), '\\', '/');
        std::replace(resourcePath.begin(), resourcePath.end(), '\\', '/');
        if(path.starts_with(resourcePath)) return path.substr(resourcePath.length() + 1);
        else
            return path;
    }
    else
        return path;
}

js::SourceLocation js::SourceLocation::GetCurrent(IResource* resource, int framesToSkip)
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

js::StackTrace::StackTrace(const std::vector<Frame>&& _frames, v8::Local<v8::Context> _ctx) : frames(_frames), context(_ctx->GetIsolate(), _ctx) {}

std::string js::StackTrace::ToString(uint32_t offset) const
{
    std::stringstream stream;
    size_t size = frames.size();

    for(size_t i = offset; i < size; i++)
    {
        const Frame& frame = frames[i];
        stream << "  at " << frame.function << " (" << frame.file << ":" << frame.line << ")"
               << "\n";
    }
    return stream.str();
}

js::StackTrace js::StackTrace::GetCurrent(v8::Isolate* isolate, IResource* resource, int framesToSkip)
{
    v8::Local<v8::StackTrace> stackTrace = v8::StackTrace::CurrentStackTrace(isolate, framesToSkip + 5);
    v8::Local<v8::Context> ctx = isolate->GetEnteredOrMicrotaskContext();

    std::vector<Frame> frames;
    for(int i = framesToSkip; i < stackTrace->GetFrameCount(); i++)
    {
        v8::Local<v8::StackFrame> frame = stackTrace->GetFrame(isolate, i);

        auto scriptName = frame->GetScriptName();

        if(scriptName.IsEmpty()) {
            continue;
        }

        Frame frameData;

        frameData.file = PrettifyFilePath(resource, CppValue(scriptName));
        frameData.line = frame->GetLineNumber();
        if(frame->GetFunctionName().IsEmpty()) frameData.function = "[anonymous]";
        else
            frameData.function = CppValue(frame->GetFunctionName());

        frames.push_back(std::move(frameData));
    }

    return StackTrace{ std::move(frames), ctx };
}

void js::StackTrace::Print(v8::Isolate* isolate)
{
    Logger::Error(GetCurrent(isolate).ToString());
}

void js::TryCatch::PrintError(bool skipLocation)
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

    if(!skipLocation) Logger::Error("[JS] Exception caught in resource '" + resource->GetName() + "' in file '" + file + "' at line " + lineStr);
    if(!exceptionStr.empty() && stack.empty())
    {
        Logger::Error("[JS]", exceptionStr);
        Logger::Error("[JS]  ", sourceLine);
    }
    if(!stack.empty()) Logger::Error("[JS]", stack);

    js::Event::EventArgs args;
    args.Set("error", exception);
    args.Set("stack", stack);

    js::Object location;
    location.Set("fileName", file);
    location.Set("lineNumber", line);

    args.Set("location", location);

    js::Event::SendEvent(js::EventType::ERROR, args, resource);
}

js::IResource* js::Value::GetResource()
{
    if(!resource) resource = IResource::GetFromContext(GetContext());
    return resource;
}

js::IResource* js::PersistentValue::GetResource()
{
    if(!resource) resource = IResource::GetFromContext(GetContext());
    return resource;
}

void js::Object::SetMethod(std::string_view key, js::internal::FunctionCallback callback)
{
    v8::Local<v8::Function> method = WrapFunction(callback)->GetFunction(context).ToLocalChecked();
    object->Set(context, JSValue(key), method);
}

void js::Object::SetBoundMethod(std::string_view key, js::internal::FunctionCallback callback)
{
    object->SetLazyDataProperty(context, JSValue(key), Wrapper::BoundFunctionHandler, v8::External::New(v8::Isolate::GetCurrent(), (void*)callback));
}

js::Type js::Object::GetType(std::string_view key)
{
    auto it = typeCache.find(key.data());
    if(it != typeCache.end()) return it->second;
    v8::MaybeLocal<v8::Value> maybeVal = object->Get(context, js::JSValue(key));
    v8::Local<v8::Value> val;
    if(!maybeVal.ToLocal(&val)) return js::Type::INVALID;
    js::Type type = js::GetType(val, GetResource());
    typeCache.insert({ std::string(key), type });
    return type;
}

js::TemporaryGlobalExtension::TemporaryGlobalExtension(v8::Local<v8::Context> _ctx, const std::string& _name, js::internal::FunctionCallback _callback) : ctx(_ctx), name(_name)
{
    ctx->Global()->Set(ctx, JSValue(_name), WrapFunction(_callback)->GetFunction(ctx).ToLocalChecked());
}

js::Promise::~Promise()
{
    if(owned) resource->RemovePromise(this);
}

void js::StringOutputStream::EndOfStream()
{
    resource->PushNextTickCallback(
      [this]()
      {
          this->callback(this->stream.str());
          delete this;
      });
}
