#include "ScriptObject.h"
#include "interfaces/IResource.h"
#include "Class.h"

js::ScriptObject::ScriptObject(v8::Isolate* _isolate, v8::Local<v8::Object> _jsObject, alt::IBaseObject* _object, js::Class* _class)
    : isolate(_isolate), jsObject(_class->MakePersistent(_jsObject)), object(_object), class_(_class)
{
}

js::ScriptObject* js::ScriptObject::Create(v8::Local<v8::Context> context, alt::IBaseObject* object, js::Class* class_)
{
    v8::Isolate* isolate = context->GetIsolate();
    v8::Local<v8::Object> jsObject = class_->Create(context);
    ScriptObject* scriptObject = new ScriptObject(isolate, jsObject, object, class_);
    jsObject->SetAlignedPointerInInternalField(0, scriptObject);
    return scriptObject;
}

js::ScriptObject* js::ScriptObject::Create(v8::Local<v8::Context> context, alt::IBaseObject* object, v8::Local<v8::Function> factory, Class* class_)
{
    v8::Isolate* isolate = context->GetIsolate();
    v8::MaybeLocal<v8::Object> maybeJsObject = factory->NewInstance(context);
    v8::Local<v8::Object> jsObject;
    if(!maybeJsObject.ToLocal(&jsObject)) return nullptr;
    ScriptObject* scriptObject = new ScriptObject(isolate, jsObject, object, class_);
    jsObject->SetAlignedPointerInInternalField(0, scriptObject);
    return scriptObject;
}

js::ScriptObject* js::ScriptObject::Create(v8::Local<v8::Object> jsObject, alt::IBaseObject* object, js::Class* class_)
{
    ScriptObject* scriptObject = new ScriptObject(jsObject->GetIsolate(), jsObject, object, class_);
    jsObject->SetAlignedPointerInInternalField(0, scriptObject);
    return scriptObject;
}

js::ScriptObject* js::ScriptObject::Get(v8::Local<v8::Object> obj)
{
    if(obj->InternalFieldCount() != 1) return nullptr;
    return static_cast<ScriptObject*>(obj->GetAlignedPointerFromInternalField(0));
}

void js::ScriptObject::Destroy(ScriptObject* scriptObject)
{
    scriptObject->Get()->SetAlignedPointerInInternalField(0, nullptr);
    delete scriptObject;
}
