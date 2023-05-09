#include "Class.h"
#include "cpp-sdk/ICore.h"

// clang-format off
extern js::Class baseObjectClass;
extern js::Class sharedVirtualEntityGroupClass("SharedVirtualEntityGroup", &baseObjectClass, nullptr, [](js::ClassTemplate& tpl)
{
    tpl.LazyProperty<&alt::IVirtualEntityGroup::GetID>("id");
    tpl.LazyProperty<&alt::IVirtualEntityGroup::GetStreamingRangeLimit>("maxStreamedEntityCount");
});
