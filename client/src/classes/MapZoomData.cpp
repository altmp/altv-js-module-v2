#include "Class.h"
#include "cpp-sdk/ICore.h"
#include "helpers/ClassInstanceCache.h"

static void fZoomScaleGetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldJSValue()) return;
    uint8_t zoomDataId = ctx.GetExtraInternalFieldJSValue<uint8_t>();
    auto zoomData = alt::ICore::Instance().GetMapData(zoomDataId);

    ctx.Return(zoomData->GetZoomScale());
}

static void fZoomScaleSetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldJSValue()) return;
    uint8_t zoomDataId = ctx.GetExtraInternalFieldJSValue<uint8_t>();
    auto zoomData = alt::ICore::Instance().GetMapData(zoomDataId);

    float value;
    if(!ctx.GetValue(value)) return;

    zoomData->SetZoomScale(value);
}

static void fZoomSpeedGetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldJSValue()) return;
    uint8_t zoomDataId = ctx.GetExtraInternalFieldJSValue<uint8_t>();
    auto zoomData = alt::ICore::Instance().GetMapData(zoomDataId);

    ctx.Return(zoomData->GetZoomSpeed());
}

static void fZoomSpeedSetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldJSValue()) return;
    uint8_t zoomDataId = ctx.GetExtraInternalFieldJSValue<uint8_t>();
    auto zoomData = alt::ICore::Instance().GetMapData(zoomDataId);

    float value;
    if(!ctx.GetValue(value)) return;

    zoomData->SetZoomSpeed(value);
}

static void fScrollSpeedGetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldJSValue()) return;
    uint8_t zoomDataId = ctx.GetExtraInternalFieldJSValue<uint8_t>();
    auto zoomData = alt::ICore::Instance().GetMapData(zoomDataId);

    ctx.Return(zoomData->GetScrollSpeed());
}

static void fScrollSpeedSetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldJSValue()) return;
    uint8_t zoomDataId = ctx.GetExtraInternalFieldJSValue<uint8_t>();
    auto zoomData = alt::ICore::Instance().GetMapData(zoomDataId);

    float value;
    if(!ctx.GetValue(value)) return;

    zoomData->SetScrollSpeed(value);
}

static void vTilesXGetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldJSValue()) return;
    uint8_t zoomDataId = ctx.GetExtraInternalFieldJSValue<uint8_t>();
    auto zoomData = alt::ICore::Instance().GetMapData(zoomDataId);

    ctx.Return(zoomData->GetTilesCountX());
}

static void vTilesXSetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldJSValue()) return;
    uint8_t zoomDataId = ctx.GetExtraInternalFieldJSValue<uint8_t>();
    auto zoomData = alt::ICore::Instance().GetMapData(zoomDataId);

    float value;
    if(!ctx.GetValue(value)) return;

    zoomData->SetTilesCountX(value);
}

static void vTilesYGetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldJSValue()) return;
    uint8_t zoomDataId = ctx.GetExtraInternalFieldJSValue<uint8_t>();
    auto zoomData = alt::ICore::Instance().GetMapData(zoomDataId);

    ctx.Return(zoomData->GetTilesCountY());
}

static void vTilesYSetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldJSValue()) return;
    uint8_t zoomDataId = ctx.GetExtraInternalFieldJSValue<uint8_t>();
    auto zoomData = alt::ICore::Instance().GetMapData(zoomDataId);

    float value;
    if(!ctx.GetValue(value)) return;

    zoomData->SetTilesCountY(value);
}

extern js::Class mapZoomDataClass;
static js::ClassInstanceCache cache(mapZoomDataClass);
static void Get(js::FunctionContext& ctx)
{
    if(!ctx.CheckArgCount(1)) return;
    if(!ctx.CheckArgType(0, { js::Type::NUMBER, js::Type::STRING })) return;

    if(ctx.GetArgType(0) == js::Type::NUMBER)
    {
        uint8_t zoomDataId;
        if(!ctx.GetArg(0, zoomDataId)) return;

        auto data = alt::ICore::Instance().GetMapData(zoomDataId);
        if(!ctx.Check(data != nullptr, "No ZoomData exists with this ID")) return;

        ctx.Return(cache.GetOrCreate(ctx.GetResource(), zoomDataId));
    }
    else
    {
        std::string zoomDataAlias;
        if(!ctx.GetArg(0, zoomDataAlias)) return;

        auto data = alt::ICore::Instance().GetMapData(zoomDataAlias);
        if(!ctx.Check(data != nullptr, "No ZoomData exists with this alias")) return;

        uint8_t zoomDataId = alt::ICore::Instance().GetMapDataIDFromAlias(zoomDataAlias);
        ctx.Return(cache.GetOrCreate(ctx.GetResource(), zoomDataId));
    }
}

static void ResetAll(js::FunctionContext& ctx)
{
    alt::ICore::Instance().ResetAllMapData();
}

static void Reset(js::FunctionContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldJSValue()) return;
    uint8_t zoomDataId = ctx.GetExtraInternalFieldJSValue<uint8_t>();

    alt::ICore::Instance().ResetMapData(zoomDataId);
}

// clang-format off
extern js::Class mapZoomDataClass("MapZoomData", [](js::ClassTemplate& tpl)
{
    tpl.Property("fZoomScale", fZoomScaleGetter, fZoomScaleSetter);
    tpl.Property("fZoomSpeed", fZoomSpeedGetter, fZoomSpeedSetter);
    tpl.Property("fScrollSpeed", fScrollSpeedGetter, fScrollSpeedSetter);
    tpl.Property("vTilesX", vTilesXGetter, vTilesXSetter);
    tpl.Property("vTilesY", vTilesYGetter, vTilesYSetter);

    tpl.Method("reset", Reset);

    tpl.StaticFunction("get", Get);
    tpl.StaticFunction("resetAll", ResetAll);
}, true);
