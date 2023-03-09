#include "ScriptObject.h"
#include "interfaces/IResource.h"
#include "Class.h"

js::ScriptObject* js::ScriptObject::Create(v8::Local<v8::Context> context, alt::IBaseObject* object, js::Class* class_)
{
    v8::Isolate* isolate = context->GetIsolate();
    v8::Local<v8::Object> jsObject = class_->GetTemplate(isolate).Get()->GetFunction(context).ToLocalChecked()->NewInstance(context).ToLocalChecked();
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
