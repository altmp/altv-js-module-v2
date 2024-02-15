#include "Class.h"
#include "cpp-sdk/ICore.h"
#include "CNodeResource.h"

static void Constructor(js::FunctionContext& ctx)
{
    if(!ctx.CheckCtor()) return;
    if(!ctx.CheckArgCount(1, 2)) return;
    CNodeResource* resource = ctx.GetResource<CNodeResource>();

    std::string name;
    if(!ctx.GetArg(0, name)) return;

    alt::Metric::Type type = ctx.GetArg<alt::Metric::Type>(1, alt::Metric::Type::METRIC_TYPE_GAUGE);

    alt::Metric* metric = resource->RegisterMetric(name, type);
    ctx.SetExtraInternalFieldValue(metric);
}

static void NameGetter(js::LazyPropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldValue()) return;
    alt::Metric* metric = ctx.GetExtraInternalFieldValue<alt::Metric>();

    ctx.Return(metric->name);
}

static void ValueGetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldValue()) return;
    alt::Metric* metric = ctx.GetExtraInternalFieldValue<alt::Metric>();

    ctx.Return(metric->value);
}

static void ValueSetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldValue()) return;
    alt::Metric* metric = ctx.GetExtraInternalFieldValue<alt::Metric>();

    uint64_t value;
    if(!ctx.GetValue(value)) return;

    metric->SetValue(value);
}

static void ValidGetter(js::PropertyContext& ctx)
{
    alt::Metric* metric = ctx.GetExtraInternalFieldValue<alt::Metric>();

    ctx.Return(metric != nullptr && metric->exists == true);
}

static void Begin(js::FunctionContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldValue()) return;
    alt::Metric* metric = ctx.GetExtraInternalFieldValue<alt::Metric>();

    metric->Begin();
}

static void Add(js::FunctionContext& ctx)
{
    if (!ctx.CheckArgCount(1)) return;
    if(!ctx.CheckExtraInternalFieldValue()) return;
    alt::Metric* metric = ctx.GetExtraInternalFieldValue<alt::Metric>();

    uint64_t value;
    if(!ctx.GetArg(0, value)) return;

    metric->Add(value);
}

static void Inc(js::FunctionContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldValue()) return;
    alt::Metric* metric = ctx.GetExtraInternalFieldValue<alt::Metric>();

    metric->Inc();
}

static void End(js::FunctionContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldValue()) return;
    alt::Metric* metric = ctx.GetExtraInternalFieldValue<alt::Metric>();

    metric->End();
}

static void Destroy(js::FunctionContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldValue()) return;
    alt::Metric* metric = ctx.GetExtraInternalFieldValue<alt::Metric>();
    CNodeResource* resource = ctx.GetResource<CNodeResource>();

    metric->Destroy();
    resource->UnregisterMetric(metric);

    ctx.SetExtraInternalFieldValue(nullptr);
}

// clang-format off
extern js::Class metricClass("Metric", nullptr, Constructor, [](js::ClassTemplate& tpl)
{
    tpl.LazyProperty("name", NameGetter);

    tpl.Property("value", ValueGetter, ValueSetter);
    tpl.Property("valid", ValidGetter);

    tpl.Method("add", Add);
    tpl.Method("inc", Inc);

    tpl.Method("begin", Begin);
    tpl.Method("end", End);
    tpl.Method("destroy", Destroy);
}, true);
