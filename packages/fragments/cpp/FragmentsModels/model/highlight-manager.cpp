#include "index_generated.h"
#include "highlight-manager.h"

using namespace js;

auto HighlightManager::getHighlight(FragmentsModel model, std::optional<js::array<js::number>> localIds) {
    {
            const js::any materials = co_await model["threads"]["invoke"](model["modelId"], "getHighlight"_S, js::array<js::any>{localIds});
            MaterialManager::resetColors(materials);
            return materials;
    }
}

auto HighlightManager::highlight(FragmentsModel model, js::typed::Nullable<js::array<js::number>> localIds, MaterialDefinition highlightMaterial) {
    {
            co_await model["threads"]["invoke"](model["modelId"], "highlight"_S, js::array<js::any>{localIds, highlightMaterial});
    }
}

auto HighlightManager::getHighlightItemIds(FragmentsModel model) {
    {
            return model["threads"]["invoke"](model["modelId"], "getHighlightItemIds"_S);
    }
}

auto HighlightManager::resetHighlight(FragmentsModel model, std::optional<js::array<js::number>> localIds) {
    {
            co_await model["threads"]["invoke"](model["modelId"], "resetHighlight"_S, js::array<js::any>{localIds});
    }
}
