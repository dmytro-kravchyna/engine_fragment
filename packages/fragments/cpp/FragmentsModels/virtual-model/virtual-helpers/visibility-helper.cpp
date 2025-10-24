#include "index_generated.h"
#include "visibility-helper.h"

using namespace js;

auto VisibilityHelper::resetVisible(VirtualFragmentsModel model) {
    {
            model["itemConfig"]["clearVisible"]();
            model["tiles"]["restart"]();
    }
}

auto VisibilityHelper::getVisible(VirtualFragmentsModel model, js::array<js::number> items) {
    {
            const js::any itemIds = model["properties"]["getItemIdsFromLocalIds"](items);
            js::array<bool> result = js::array<js::any>{};
            for (const auto& id : itemIds) {
                        {
                                        const js::any isVisible = model["itemConfig"]["visible"](id);
                                        result.push(isVisible);
                        }
            }
            return result;
    }
}

auto VisibilityHelper::getItemsByVisibility(VirtualFragmentsModel model, bool visible) {
    {
            const js::any visibleCondition = this->getVisibleCondition(model, visible);
            const js::any result = model["getItemsByConfig"](visibleCondition);
            const js::any localIds = model["properties"]["getLocalIdsFromItemIds"](result);
            return localIds;
    }
}

auto VisibilityHelper::toggleVisible(VirtualFragmentsModel model, js::array<js::number> localIds) {
    {
            const js::any itemIds = model["properties"]["getItemIdsFromLocalIds"](localIds);
            const js::any toggleEvent = this->getToggleEvent(model);
            model["traverse"](itemIds, toggleEvent);
            model["tiles"]["updateVirtualMeshes"](itemIds);
    }
}

void VisibilityHelper::setVisible(VirtualFragmentsModel model, js::array<js::number> localIds, bool visible) {
    {
            const js::any itemIds = model["properties"]["getItemIdsFromLocalIds"](localIds);
            const js::any setEvent = this->getSetEvent(model, visible);
            model["traverse"](itemIds, setEvent);
            model["tiles"]["updateVirtualMeshes"](itemIds);
    }
}

auto VisibilityHelper::getSetEvent(VirtualFragmentsModel model, bool visible) {
    {
            return [&](js::number itemId) -> auto {
            model["itemConfig"]["setVisible"](itemId, visible);
            };
    }
}

auto VisibilityHelper::getVisibleCondition(VirtualFragmentsModel model, bool visible) {
    {
            return [&](js::number itemId) -> auto {
            const js::any currentVisible = model["itemConfig"]["visible"](itemId);
            return currentVisible === visible;
            };
    }
}

auto VisibilityHelper::getToggleEvent(VirtualFragmentsModel model) {
    {
            return [&](js::number itemId) -> auto {
            const js::any isVisible = model["itemConfig"]["visible"](itemId);
            model["itemConfig"]["setVisible"](itemId, !isVisible);
            };
    }
}
