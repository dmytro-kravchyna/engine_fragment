#include "index_generated.h"
#include "items-helper.h"

using namespace js;

auto ItemsHelper::traverse(VirtualFragmentsModel model, js::array<js::number> itemIds, std::function<void(js::number, js::number)> onItem) {
    {
            if (itemIds) {
                        {
                                        this->traverseItems(itemIds, onItem);
                                        return;
                        }
            }
            this->traverseAllItems(model, onItem);
    }
}

auto ItemsHelper::getItemsByConfig(VirtualFragmentsModel model, std::function<bool(js::number)> condition) {
    {
            js::array<js::number> found = js::array<js::any>{};
            const js::any count = model["data"]["localIdsLength"]();
            for (js::number itemId = js::number(0); (itemId < count); itemId++) {
                        {
                                        const js::any conditionPass = condition(itemId);
                                        if (!conditionPass) {
                                                            continue;
                                        }
                                        found.push(itemId);
                        }
            }
            return found;
    }
}

auto ItemsHelper::traverseItems(js::array<js::number> itemIds, std::function<void(js::number, js::number)> onItem) {
    {
            const js::any itemsCount = itemIds.length();
            for (js::number id = js::number(0); (id < itemsCount); id++) {
                        {
                                        onItem(itemIds->id, id);
                        }
            }
    }
}

auto ItemsHelper::traverseAllItems(VirtualFragmentsModel model, std::function<void(js::number, js::number)> onItem) {
    {
            const js::any itemsCount = model["itemConfig"]["size"];
            for (js::number id = js::number(0); (id < itemsCount); id++) {
                        {
                                        onItem(id, id);
                        }
            }
    }
}
