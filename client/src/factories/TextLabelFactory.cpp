#include "FactoryHandler.h"
#include "interfaces/IResource.h"

// clang-format off
static js::FactoryHandler textLabelFactory(alt::IBaseObject::Type::TEXT_LABEL, [](js::Object& args) -> alt::IBaseObject* {
    alt::IResource* resource = args.GetResource()->GetResource();

    std::string text;
    if(!args.Get("text", text)) return nullptr;

    std::string fontName;
    if(!args.Get("fontName", fontName)) return nullptr;

    float fontSize;
    if(!args.Get("fontSize", fontSize)) return nullptr;

    alt::Vector3f pos;
    if(!args.Get("pos", pos)) return nullptr;

    auto rot = args.Get<alt::Vector3f>("rot", {0, 0, 0});
    auto color = args.Get<alt::RGBA>("color", {255, 255, 255, 255});
    auto outlineColor = args.Get<alt::RGBA>("outlineColor", {0, 0, 0, 255});

    float outlineWidth = args.Get("outlineWidth", 0.0f);
    float scale = args.Get("fontScale", 1.f);
    bool useStreaming = args.Get("useStreaming", false);
    uint32_t streamingDistance = args.Get("streamingDistance", 0);

    return alt::ICore::Instance().CreateTextLabel(text, fontName, fontSize, scale, pos, rot, color, outlineWidth, outlineColor, useStreaming, streamingDistance, resource);
});
