// clang-format off
const fs = require("fs");

// This is ugly as fuck but it works

/*
template<class Class, typename Ret, typename Arg1, typename Arg2, Ret (Class::*Method)(Arg1, Arg2)>
static void MethodHandler(const v8::FunctionCallbackInfo<v8::Value>& info)
{
    Class* obj = dynamic_cast<Class*>(GetThisObjectFromInfo(info));
    if(obj == nullptr)
    {
        info.GetIsolate()->ThrowException(v8::Exception::Error(JSValue("Invalid base object")));
        return;
    }
    if constexpr(std::is_same_v<void, Ret>)
    {
        (obj->*Method)(GetArg<CleanArg<Arg1>>(info, 0), GetArg<CleanArg<Arg2>>(info, 1));
    }
    else
    {
        info.GetReturnValue().Set(JSValue((obj->*Method)(GetArg<CleanArg<Arg1>>(info, 0), GetArg<CleanArg<Arg2>>(info, 1))));
    }
}
*/
const template = `
template<class Class, typename Ret, {TEMPLATE_TYPES}, Ret (Class::*Method)({METHOD_TYPES}) {CONST}>
static void MethodHandler(const v8::FunctionCallbackInfo<v8::Value>& info)
{
    Class* obj = dynamic_cast<Class*>(GetThisObjectFromInfo(info));
    if(obj == nullptr)
    {
        info.GetIsolate()->ThrowException(v8::Exception::Error(JSValue("Invalid base object")));
        return;
    }
    try
    {
        if constexpr(std::is_same_v<void, Ret>)
        {
            (obj->*Method)({METHOD_ARGS});
        }
        else
        {
            info.GetReturnValue().Set(JSValue((obj->*Method)({METHOD_ARGS})));
        }
    }
    catch(BadArgException& e)
    {
        info.GetIsolate()->ThrowException(v8::Exception::Error(JSValue(e.what())));
    }
}`;
const templateTypeTemplate = `typename Arg{INDEX}`;
const maxCount = 16;

let resultStr = "";
for (let i = 1; i < maxCount + 1; i++) {
    let templateTypes = "";
    let methodTypes = "";
    let methodArgs = "";
    for (let j = 0; j < i; j++) {
        let tpl = templateTypeTemplate;
        templateTypes += tpl.replace("{INDEX}", j);
        methodTypes += `Arg${j}`;
        methodArgs += `GetArg<CleanArg<Arg${j}>>(info, ${j})`;
        if (j < i - 1) {
            templateTypes += ", ";
            methodTypes += ", ";
            methodArgs += ", ";
        }
    }

    let nonConstTempl = template;
    nonConstTempl = nonConstTempl.replace("{TEMPLATE_TYPES}", templateTypes);
    nonConstTempl = nonConstTempl.replace("{METHOD_TYPES}", methodTypes);
    nonConstTempl = nonConstTempl.replace("{METHOD_ARGS}", methodArgs);
    nonConstTempl = nonConstTempl.replace("{METHOD_ARGS}", methodArgs);
    nonConstTempl = nonConstTempl.replace("{CONST}", "");

    let constTempl = template;
    constTempl = constTempl.replace("{TEMPLATE_TYPES}", templateTypes);
    constTempl = constTempl.replace("{METHOD_TYPES}", methodTypes);
    constTempl = constTempl.replace("{METHOD_ARGS}", methodArgs);
    constTempl = constTempl.replace("{METHOD_ARGS}", methodArgs);
    constTempl = constTempl.replace("{CONST}", "const");

    resultStr += nonConstTempl + constTempl;
}

fs.writeFileSync("wrappers.cpp", resultStr);

/*
template<class Class, typename Ret, typename Arg1, typename Arg2, Ret (Class::*Method)(Arg1, Arg2)>
void Method(const std::string& name)
{
    Get()->PrototypeTemplate()->Set(js::JSValue(name), v8::FunctionTemplate::New(GetIsolate(), Wrapper::MethodHandler<Class, Ret, Arg1, Arg2, Method>));
}
*/
const overloadTemplate = `
template<class Class, typename Ret, {TEMPLATE_TYPES}, Ret (Class::*Method)({METHOD_TYPES}) {CONST}>
void Method(const std::string& name)
{
#ifdef DEBUG_BINDINGS
    RegisterKey("Method", name);
#endif
    Get()->PrototypeTemplate()->Set(js::JSValue(name), v8::FunctionTemplate::New(GetIsolate(), Wrapper::MethodHandler<Class, Ret, {METHOD_TYPES}, Method>));
}`;

resultStr = "";
for (let i = 1; i < maxCount + 1; i++) {
    let templateTypes = "";
    let methodTypes = "";
    for (let j = 0; j < i; j++) {
        let tpl = templateTypeTemplate;
        templateTypes += tpl.replace("{INDEX}", j);
        methodTypes += `Arg${j}`;
        if (j < i - 1) {
            templateTypes += ", ";
            methodTypes += ", ";
        }
    }

    let nonConstTempl = overloadTemplate;
    nonConstTempl = nonConstTempl.replace("{TEMPLATE_TYPES}", templateTypes);
    nonConstTempl = nonConstTempl.replace("{METHOD_TYPES}", methodTypes);
    nonConstTempl = nonConstTempl.replace("{METHOD_TYPES}", methodTypes);
    nonConstTempl = nonConstTempl.replace("{CONST}", "");

    let constTempl = overloadTemplate;
    constTempl = constTempl.replace("{TEMPLATE_TYPES}", templateTypes);
    constTempl = constTempl.replace("{METHOD_TYPES}", methodTypes);
    constTempl = constTempl.replace("{METHOD_TYPES}", methodTypes);
    constTempl = constTempl.replace("{CONST}", "const");

    resultStr += nonConstTempl + constTempl;
}

fs.writeFileSync("overloads.cpp", resultStr);
