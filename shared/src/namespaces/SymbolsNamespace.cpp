#include "Namespace.h"

template<js::Symbol symbol>
void SymbolGetter(js::LazyPropertyContext& ctx)
{
    ctx.Return(js::GetSymbol(symbol));
}

// clang-format off
extern js::Namespace symbolsNamespace("Symbols", [](js::NamespaceTemplate& tpl) {
    tpl.StaticLazyProperty("serialize", SymbolGetter<js::Symbol::SERIALIZE>);
});
