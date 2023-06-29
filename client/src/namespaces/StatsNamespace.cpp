#include "Namespace.h"

static void SetStat(js::FunctionContext& ctx)
{
    if(!ctx.CheckArgCount(2)) return;

    std::string statName;
    if(!ctx.GetArg(0, statName)) return;

    alt::IStatData* stat = alt::ICore::Instance().GetStatData(statName);
    if(!ctx.Check(stat, "Stat does not exist")) return;

    std::string type = stat->GetStatType();
    if(type == "INT" || type == "TEXTLABEL")
    {
        int32_t value;
        if(!ctx.GetArg(1, value)) return;
        stat->SetInt32Value(value);
    }
    else if(type == "INT64")
    {
        int64_t value;
        if(!ctx.GetArg(1, value)) return;
        stat->SetInt64Value(value);
    }
    else if(type == "FLOAT")
    {
        float value;
        if(!ctx.GetArg(1, value)) return;
        stat->SetFloatValue(value);
    }
    else if(type == "BOOL")
    {
        bool value;
        if(!ctx.GetArg(1, value)) return;
        stat->SetBoolValue(value);
    }
    else if(type == "STRING")
    {
        std::string value;
        if(!ctx.GetArg(1, value)) return;
        stat->SetStringValue(value.c_str());
    }
    else if(type == "UINT8")
    {
        uint8_t value;
        if(!ctx.GetArg(1, value)) return;
        stat->SetUInt8Value(value);
    }
    else if(type == "UINT16")
    {
        uint16_t value;
        if(!ctx.GetArg(1, value)) return;
        stat->SetUInt16Value(value);
    }
    else if(type == "UINT32")
    {
        uint32_t value;
        if(!ctx.GetArg(1, value)) return;
        stat->SetUInt32Value(value);
    }
    else if(type == "UINT64" || type == "POS" || type == "DATE" || type == "PACKED" || type == "USERID")
    {
        uint64_t value;
        if(!ctx.GetArg(1, value)) return;
        stat->SetUInt64Value(value);
    }
}

static void GetStat(js::FunctionContext& ctx)
{
    if(!ctx.CheckArgCount(1)) return;

    std::string statName;
    if(!ctx.GetArg(0, statName)) return;

    alt::IStatData* stat = alt::ICore::Instance().GetStatData(statName);
    if(!ctx.Check(stat, "Stat does not exist")) return;

    std::string type = stat->GetStatType();
    if(type == "INT" || type == "TEXTLABEL") ctx.Return(stat->GetInt32Value());
    else if(type == "INT64")
        ctx.Return(stat->GetInt64Value());
    else if(type == "FLOAT")
        ctx.Return(stat->GetFloatValue());
    else if(type == "BOOL")
        ctx.Return(stat->GetBoolValue());
    else if(type == "STRING")
        ctx.Return(stat->GetStringValue());
    else if(type == "UINT8")
        ctx.Return(stat->GetUInt8Value());
    else if(type == "UINT16")
        ctx.Return(stat->GetUInt16Value());
    else if(type == "UINT32")
        ctx.Return(stat->GetUInt32Value());
    else if(type == "UINT64" || type == "POS" || type == "DATE" || type == "PACKED" || type == "USERID")
        ctx.Return(stat->GetUInt64Value());
}

static void ResetStat(js::FunctionContext& ctx)
{
    if(!ctx.CheckArgCount(1)) return;

    std::string statName;
    if(!ctx.GetArg(0, statName)) return;

    alt::IStatData* stat = alt::ICore::Instance().GetStatData(statName);
    if(!ctx.Check(stat, "Stat does not exist")) return;

    stat->Reset();
}

// clang-format off
extern js::Namespace statsNamespace("Stats", [](js::NamespaceTemplate& tpl) {
    tpl.StaticFunction("set", SetStat);
    tpl.StaticFunction("get", GetStat);
    tpl.StaticFunction("reset", ResetStat);
});
