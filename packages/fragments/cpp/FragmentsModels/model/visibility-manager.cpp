#include "index_generated.h"
#include "visibility-manager.h"

using namespace js;

auto VisibilityManager::resetVisible(FragmentsModel model) {
    {
            co_await model["threads"]["invoke"](model["modelId"], "resetVisible"_S);
    }
}

auto VisibilityManager::getItemsByVisibility(FragmentsModel model, bool visible) {
    {
            return model["threads"]["invoke"](model["modelId"], "getItemsByVisibility"_S, js::array<js::any>{visible});
    }
}

auto VisibilityManager::getVisible(FragmentsModel model, js::array<js::number> localIds) {
    {
            return model["threads"]["invoke"](model["modelId"], "getVisible"_S, js::array<js::any>{localIds});
    }
}
