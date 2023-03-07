#include "ScriptObject.h"
#include "interfaces/IResource.h"
#include "Class.h"

js::ScriptObject* js::ScriptObject::Create(v8::Local<v8::Context> context, alt::IBaseObject* object, js::Class* class_)
{
    v8::Isolate* isolate = context->GetIsolate();
    v8::Local<v8::Object> jsObject = class_->GetTemplate(isolate).Get()->GetFunction(context).ToLocalChecked()->NewInstance(context).ToLocalChecked();
    ScriptObject* scriptObject = new ScriptObject(isolate, jsObject, object);
    jsObject->SetAlignedPointerInInternalField(0, scriptObject);
    return scriptObject;
}

js::ScriptObject* js::ScriptObject::Create(v8::Local<v8::Object> jsObject, alt::IBaseObject* object)
{
    ScriptObject* scriptObject = new ScriptObject(jsObject->GetIsolate(), jsObject, object);
    jsObject->SetAlignedPointerInInternalField(0, scriptObject);
    return scriptObject;
}

void js::ScriptObject::Destroy(ScriptObject* scriptObject)
{
    scriptObject->Get()->SetAlignedPointerInInternalField(0, nullptr);
    delete scriptObject;
}
