#include "index_generated.h"
#include "items-manager.h"

using namespace js;

auto ItemsManager::getItem(FragmentsModel model, Identifier id) {
    {
            return std::make_shared<Item>(model, id);
    }
}

auto ItemsManager::getItemsData(FragmentsModel model, js::array<Identifier> ids, std::optional<Partial> config) {
    {
            return model["threads"]["invoke"](model["modelId"], "getItemsData"_S, js::array<js::any>{ids, config});
    }
}

auto ItemsManager::getItemsChildren(FragmentsModel model, js::array<Identifier> ids) {
    {
            return model["threads"]["invoke"](model["modelId"], "getItemsChildren"_S, js::array<js::any>{ids});
    }
}
