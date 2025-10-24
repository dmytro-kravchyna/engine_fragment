#include "index_generated.h"
#include "highlight-helper.h"

using namespace js;

void HighlightHelper::resetHighlight(VirtualFragmentsModel model, js::array<js::number> items) {
    {
            const js::any itemIds = model["properties"]["getItemIdsFromLocalIds"](items);
            this->resetHighlightForItems(itemIds, model);
            model["tiles"]["restart"]();
    }
}

auto HighlightHelper::getHighlight(VirtualFragmentsModel model, js::array<js::number> localIds) {
    {
            js::array<MaterialDefinition> found = js::array<js::any>{};
            const js::any itemIds = model["properties"]["getItemIdsFromLocalIds"](localIds);
            const js::any fetchEvent = this->getFetchEvent(model, found);
            model["traverse"](itemIds, fetchEvent);
            return found;
    }
}

auto HighlightHelper::getHighlightItems(VirtualFragmentsModel model) {
    {
            js::array<js::number> found = js::array<js::any>{};
            const js::any count = model["itemConfig"]["size"];
            for (js::number itemId = js::number(0); (itemId < count); itemId++) {
                        {
                                        const js::any hasHighlight = model["itemConfig"]["getHighlight"](itemId);
                                        if (!hasHighlight) {
                                                            continue;
                                        }
                                        auto _temp510 = model["properties"]["getLocalIdsFromItemIds"](js::array<js::any>{itemId});
                                        const auto localId = _temp510[0];
                                        found.push(localId);
                        }
            }
            return found;
    }
}

auto HighlightHelper::highlight(VirtualFragmentsModel model, js::array<js::number> items, MaterialDefinition material) {
    {
            const js::any itemIds = model["properties"]["getItemIdsFromLocalIds"](items);
            js::array<MaterialDefinition> materials = js::array<js::any>{};
            const js::any highlightEvent = this->getCheckEvent(model, material, materials);
            model["traverse"](itemIds, highlightEvent);
            const js::any ids = model["materials"]["transfer"](materials);
            const js::any createEvent = this->getCreateEvent(model, ids);
            model["traverse"](itemIds, createEvent);
            model["tiles"]["updateVirtualMeshes"](itemIds);
    }
}

auto HighlightHelper::getFetchEvent(VirtualFragmentsModel model, js::array<MaterialDefinition> found) {
    {
            return [&](js::number itemId) -> auto {
            const js::any id = model["itemConfig"]["getHighlight"](itemId);
            if (id) {
                        {
                                        const js::any result = model["materials"]["fetch"](id);
                                        found.push(result);
                                        return;
                        }
            }
            found.push(js::undefined);
            };
    }
}

auto HighlightHelper::setHighlightProperty(MaterialDefinition newHigh, MaterialDefinition pastHigh, js::string key) {
    {
            if ((newHigh->key === js::undefined && pastHigh->key !== js::undefined)) {
                        {
                                        newHigh->key = pastHigh->key;
                        }
            }
    }
}

auto HighlightHelper::getNewHighFromPast(VirtualFragmentsModel model, js::number past, MaterialDefinition highlightMaterial) {
    {
            const js::any pastHigh = model["materials"]["fetch"](past);
            const js::any newHigh = []() {
                  js::object obj_temp_0;
                  return js::any(obj_temp_0);
                }();
            for (const auto& prop : this->_highlightProps) {
                        {
                                        this->setHighlightProperty(newHigh, pastHigh, prop);
                        }
            }
            return newHigh;
    }
}

auto HighlightHelper::getCheckEvent(VirtualFragmentsModel model, MaterialDefinition highlightMaterial, js::array<MaterialDefinition> materials) {
    {
            return [&](js::number itemId) -> auto {
            const js::any past = model["itemConfig"]["getHighlight"](itemId);
            if (past !== js::undefined) {
                        {
                                        const js::any newHigh = this->getNewHighFromPast(model, past, highlightMaterial);
                                        materials.push(newHigh);
                                        return;
                        }
            }
            materials.push(highlightMaterial);
            };
    }
}

auto HighlightHelper::getCreateEvent(VirtualFragmentsModel model, js::array<js::number> ids) {
    {
            return [&](js::number itemId, js::number position) -> auto {
            model["itemConfig"]["setHighlight"](itemId, ids[position]);
            };
    }
}

auto HighlightHelper::resetHighlightForItems(js::array<js::number> itemIds, VirtualFragmentsModel model) {
    {
            if (!itemIds) {
                        {
                                        model["itemConfig"]["clearHighlight"]();
                                        return;
                        }
            }
            for (const auto& itemId : itemIds) {
                        {
                                        model["itemConfig"]["setHighlight"](itemId, js::number(0));
                        }
            }
    }
}
