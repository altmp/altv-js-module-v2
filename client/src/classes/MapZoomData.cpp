#include "Class.h"
#include "cpp-sdk/ICore.h"

static void Constructor(js::FunctionContext& ctx)
{
    if(!ctx.CheckCtor()) return;
    if(!ctx.CheckArgCount(1)) return;
    if(!ctx.CheckArgType(0, { js::Type::NUMBER, js::Type::STRING })) return;

    if(ctx.GetArgType(0) == js::Type::NUMBER)
    {
        uint8_t zoomDataId;
        if(!ctx.GetArg(0, zoomDataId)) return;

        auto data = alt::ICore::Instance().GetMapData(zoomDataId);
        if(!ctx.Check(data != nullptr, "zoomData with this id not found")) return;

        ctx.SetExtraInternalFieldValue();
    }
    else
    {
        std::string zoomDataAlias;
        if(!ctx.GetArg(0, zoomDataAlias)) return;

        auto data = alt::ICore::Instance().GetMapData(zoomDataAlias);
        if(!ctx.Check(data != nullptr, "zoomData with this id not found")) return;

        uint8_t id = alt::ICore::Instance().GetMapDataIDFromAlias(zoomDataAlias);
        ctx.SetExtraInternalFieldValue(id);
    }
}

static void fZoomScaleGetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldValue()) return;
    alt::IMapData* zoomData = ctx.GetExtraInternalFieldValue<alt::IMapData>();

    ctx.Return(zoomData->GetZoomScale());
}

static void fZoomScaleSetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldValue()) return;
    alt::IMapData* zoomData = ctx.GetExtraInternalFieldValue<alt::IMapData>();

    float value;
    if(!ctx.GetValue(value)) return;

    zoomData->SetZoomScale(value);
}

static void fZoomSpeedGetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldValue()) return;
    alt::IMapData* zoomData = ctx.GetExtraInternalFieldValue<alt::IMapData>();

    ctx.Return(zoomData->GetZoomSpeed());
}

static void fZoomSpeedSetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldValue()) return;
    alt::IMapData* zoomData = ctx.GetExtraInternalFieldValue<alt::IMapData>();

    float value;
    if(!ctx.GetValue(value)) return;

    zoomData->SetZoomSpeed(value);
}

static void fScrollSpeedGetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldValue()) return;
    alt::IMapData* zoomData = ctx.GetExtraInternalFieldValue<alt::IMapData>();

    ctx.Return(zoomData->GetScrollSpeed());
}

static void fScrollSpeedSetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldValue()) return;
    alt::IMapData* zoomData = ctx.GetExtraInternalFieldValue<alt::IMapData>();

    float value;
    if(!ctx.GetValue(value)) return;

    zoomData->SetScrollSpeed(value);
}

static void vTilesXGetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldValue()) return;
    alt::IMapData* zoomData = ctx.GetExtraInternalFieldValue<alt::IMapData>();

    ctx.Return(zoomData->GetTilesCountX());
}

static void vTilesXSetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldValue()) return;
    alt::IMapData* zoomData = ctx.GetExtraInternalFieldValue<alt::IMapData>();

    float value;
    if(!ctx.GetValue(value)) return;

    zoomData->SetTilesCountX(value);
}

static void vTilesYGetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldValue()) return;
    alt::IMapData* zoomData = ctx.GetExtraInternalFieldValue<alt::IMapData>();

    ctx.Return(zoomData->GetTilesCountY());
}

static void vTilesYSetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldValue()) return;
    alt::IMapData* zoomData = ctx.GetExtraInternalFieldValue<alt::IMapData>();

    float value;
    if(!ctx.GetValue(value)) return;

    zoomData->SetTilesCountY(value);
}

static void Get(js::FunctionContext& ctx)
{
    if(!ctx.CheckArgCount(1)) return;
    if(!ctx.CheckArgType(0, { js::Type::NUMBER, js::Type::STRING })) return;

    if(ctx.GetArgType(0) == js::Type::NUMBER)
    {
        uint8_t zoomData;
        if(!ctx.GetArg(0, zoomData)) return;

        ctx.Return(mapZoomDataClass.Create(ctx.GetIsolate()->GetEnteredOrMicrotaskContext(), zoomData));
    }
}

static void ResetAll(js::FunctionContext& ctx)
{
    alt::ICore::Instance().ResetAllMapData();
}

static void Reset(js::FunctionContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldValue()) return;
    alt::IMapData* zoomData = ctx.GetExtraInternalFieldValue<alt::IMapData>();

    alt::ICore::Instance().ResetMapData(zoomData);
}

// clang-format off
extern js::Class mapZoomDataClass("MapZoomData", nullptr, Constructor, [](js::ClassTemplate& tpl)
{
    tpl.Property("fZoomScale", fZoomScaleGetter, fZoomScaleSetter);
    tpl.Property("fZoomSpeed", fZoomSpeedGetter, fZoomSpeedSetter);
    tpl.Property("fScrollSpeed", fScrollSpeedGetter, fScrollSpeedSetter);
    tpl.Property("vTilesX", vTilesXGetter, vTilesXSetter);
    tpl.Property("vTilesY", vTilesYGetter, vTilesYSetter);

    tpl.StaticFunction("get", Get);
    tpl.StaticFunction("resetAll", ResetAll);

    tpl.Method("reset", Reset);
});
