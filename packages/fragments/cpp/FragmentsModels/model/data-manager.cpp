#include "index_generated.h"
#include "data-manager.h"

using namespace js;

auto DataManager::dispose(FragmentsModel model, MeshManager meshes, AlignmentsManager alignments) {
    {
            meshes["list"]["delete"](model["modelId"]);
            co_await this->requestModelDelete(model);
            model["threads"]["delete"](model["modelId"]);
            this->deleteAllTiles(model);
            meshes["materials"]["dispose"](model["modelId"]);
            alignments["dispose"]();
    }
}

auto DataManager::getBuffer(FragmentsModel model, bool raw) {
    {
            return model["threads"]["invoke"](model["modelId"], "getBuffer"_S, js::array<js::any>{raw});
    }
}

auto DataManager::getCategories(FragmentsModel model) {
    {
            return model["threads"]["invoke"](model["modelId"], "getCategories"_S);
    }
}

auto DataManager::getMaxLocalId(FragmentsModel model) {
    {
            return model["threads"]["invoke"](model["modelId"], "getMaxLocalId"_S);
    }
}

auto DataManager::getLocalIdsByGuids(FragmentsModel model, js::array<js::string> guids) {
    {
            return model["threads"]["invoke"](model["modelId"], "getLocalIdsByGuids"_S, js::array<js::any>{guids});
    }
}

auto DataManager::getSpatialStructure(FragmentsModel model) {
    {
            return model["threads"]["invoke"](model["modelId"], "getSpatialStructure"_S);
    }
}

auto DataManager::getItemsWithGeometry(FragmentsModel model) {
    {
            const js::any localIds = co_await model["threads"]["invoke"](model["modelId"], "getItemsWithGeometry"_S, js::array<js::any>{});
            const js::any items = localIds.map([&](auto id) -> auto { return model["getItem"](id); });
            return items;
    }
}

auto DataManager::getItemsWithGeometryCategories(FragmentsModel model) {
    {
            return model["threads"]["invoke"](model["modelId"], "getItemsWithGeometryCategories"_S, js::array<js::any>{});
    }
}

auto DataManager::getItemsIdsWithGeometry(FragmentsModel model) {
    {
            return model["threads"]["invoke"](model["modelId"], "getItemsWithGeometry"_S, js::array<js::any>{});
    }
}

auto DataManager::getItemsOfCategories(FragmentsModel model, js::array<RegExp> categories) {
    {
            js::array<js::any> args = js::array<js::any>{categories};
            const js::any data = co_await model["threads"]["invoke"](model["modelId"], "getItemsOfCategories"_S, args);
            return data;
    }
}

auto DataManager::getItemsByQuery(FragmentsModel model, ItemsQueryParams params) {
    {
            js::array<js::any> args = js::array<js::any>{params};
            const js::any localIds = co_await model["threads"]["invoke"](model["modelId"], "getItemsByQuery"_S, args);
            return localIds;
    }
}

auto DataManager::getMetadata(FragmentsModel model) {
    {
            return model["threads"]["invoke"](model["modelId"], "getMetadata"_S, js::array<js::any>{});
    }
}

auto DataManager::getGuidsByLocalIds(FragmentsModel model, js::array<js::number> localIds) {
    {
            return model["threads"]["invoke"](model["modelId"], "getGuidsByLocalIds"_S, js::array<js::any>{localIds});
    }
}

auto DataManager::requestModelDelete(FragmentsModel model) {
    {
            co_await model["threads"]["fetch"]([]() {
                  js::object obj_temp_0;
                  obj_temp_0.set("class", MultiThreadingRequestClass::DELETE_MODEL);
                  obj_temp_0.set("modelId", model["modelId"]);
                  return js::any(obj_temp_0);
                }());
    }
}

auto DataManager::deleteAllTiles(FragmentsModel model) {
    {
            for (const auto& js::undefined : model["tiles"]) {
                        {
                                        model["tiles"]["delete"](tileId);
                        }
            }
    }
}
