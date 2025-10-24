#include "index_generated.h"
#include "fragments-model.h"

using namespace js;

FragmentsModel::FragmentsModel(js::string modelId, MeshManager meshManager, FragmentsConnection threads) {
    {
            this->object.name = modelId;
            this->object.up.set(js::number(0), js::number(0), js::number(1));
            this->_meshManager = meshManager;
            this->threads = threads;
            this->_alignmentsManager = std::make_shared<AlignmentsManager>(this);
            this->tiles.onItemSet.add([&](auto param) -> auto { return this->object.add(mesh); });
            this->tiles.onBeforeDelete.add([&](auto param) -> auto {
            this->object.remove(mesh);
            mesh["geometry"]["dispose"]();
            MiscHelper::forEach(mesh["material"], [&](auto mat) -> auto { return mat["dispose"](); });
            });
    }
}

auto FragmentsModel::dispose() {
    {
            this->_isLoaded = false;
            co_await this->_dataManager.dispose(this, this->_meshManager, this->_alignmentsManager);
    }
}

auto FragmentsModel::getSpatialStructure() {
    {
            return this->_dataManager.getSpatialStructure(this);
    }
}

auto FragmentsModel::getLocalIdsByGuids(js::array<js::string> guids) {
    {
            return this->_dataManager.getLocalIdsByGuids(this, guids);
    }
}

auto FragmentsModel::getCategories() {
    {
            return this->_dataManager.getCategories(this);
    }
}

auto FragmentsModel::getItemsWithGeometryCategories() {
    {
            return this->_dataManager.getItemsWithGeometryCategories(this);
    }
}

auto FragmentsModel::getItemsWithGeometry() {
    {
            return this->_dataManager.getItemsWithGeometry(this);
    }
}

auto FragmentsModel::getItemsIdsWithGeometry() {
    {
            return this->_dataManager.getItemsIdsWithGeometry(this);
    }
}

auto FragmentsModel::getMetadata() {
    {
            return this->_dataManager.getMetadata(this);
    }
}

auto FragmentsModel::getGuidsByLocalIds(js::array<js::number> localIds) {
    {
            return this->_dataManager.getGuidsByLocalIds(this, localIds);
    }
}

auto FragmentsModel::getBuffer(auto raw) {
    {
            return this->_dataManager.getBuffer(this, raw);
    }
}

auto FragmentsModel::getItemsOfCategories(js::array<RegExp> categories) {
    {
            return this->_dataManager.getItemsOfCategories(this, categories);
    }
}

auto FragmentsModel::getGuids() {
    {
            const js::any guids = co_await this->threads.invoke(this->modelId, "getGuids"_S, js::array<js::any>{});
            return guids;
    }
}

auto FragmentsModel::getLocalIds() {
    {
            const js::any localIds = co_await this->threads.invoke(this->modelId, "getLocalIds"_S, js::array<js::any>{});
            return localIds;
    }
}

auto FragmentsModel::getItemsByQuery(ItemsQueryParams params) {
    {
            return this->_dataManager.getItemsByQuery(this, params);
    }
}

auto FragmentsModel::getItemsMaterialDefinition(js::array<js::number> localIds) {
    {
            const js::any result = co_await this->threads.invoke(this->modelId, "getItemsMaterialDefinition"_S, js::array<js::any>{localIds});
            return result;
    }
}

auto FragmentsModel::getItemsGeometry(js::array<js::number> localIds) {
    {
            const js::any geometries = co_await this->threads.invoke(this->modelId, "getItemsGeometry"_S, js::array<js::any>{localIds});
            return geometries;
    }
}

auto FragmentsModel::getItemsVolume(js::array<js::number> localIds) {
    {
            const js::any volume = co_await this->threads.invoke(this->modelId, "getItemsVolume"_S, js::array<js::any>{localIds});
            return volume;
    }
}

auto FragmentsModel::getAttributeNames() {
    {
            const js::any names = co_await this->threads.invoke(this->modelId, "getAttributeNames"_S, js::array<js::any>{});
            return names;
    }
}

auto FragmentsModel::getAttributeValues() {
    {
            const js::any values = co_await this->threads.invoke(this->modelId, "getAttributeValues"_S, js::array<js::any>{});
            return values;
    }
}

auto FragmentsModel::getAttributesUniqueValues(js::array<AttributesUniqueValuesParams> params) {
    {
            const js::any values = co_await this->threads.invoke(this->modelId, "getAttributesUniqueValues"_S, js::array<js::any>{params});
            return values;
    }
}

auto FragmentsModel::getAttributeTypes() {
    {
            const js::any types = co_await this->threads.invoke(this->modelId, "getAttributeTypes"_S, js::array<js::any>{});
            return types;
    }
}

auto FragmentsModel::getRelationNames() {
    {
            const js::any names = co_await this->threads.invoke(this->modelId, "getRelationNames"_S, js::array<js::any>{});
            return names;
    }
}

auto FragmentsModel::getMaxLocalId() {
    {
            return this->_dataManager.getMaxLocalId(this);
    }
}

auto FragmentsModel::getItem(Identifier id) {
    {
            return this->_itemsManager.getItem(this, id);
    }
}

auto FragmentsModel::getItemsChildren(js::array<Identifier> ids) {
    {
            return this->_itemsManager.getItemsChildren(this, ids);
    }
}

auto FragmentsModel::getItemsData(js::array<Identifier> ids, std::optional<Partial> config) {
    {
            return this->_itemsManager.getItemsData(this, ids, config);
    }
}

auto FragmentsModel::getPositions(std::optional<js::array<js::number>> localIds) {
    {
            return this->_coordinatesManager.getPositions(this, localIds);
    }
}

auto FragmentsModel::getCoordinates() {
    {
            return this->_coordinatesManager.getCoordinates(this);
    }
}

auto FragmentsModel::getCoordinationMatrix() {
    {
            return this->_coordinatesManager.getCoordinationMatrix(this);
    }
}

auto FragmentsModel::getMergedBox(js::array<js::number> localIds) {
    {
            return this->_boxManager.getMergedBox(this, localIds);
    }
}

auto FragmentsModel::getBoxes(std::optional<js::array<js::number>> localIds) {
    {
            return this->_boxManager.getBoxes(this, localIds);
    }
}

auto FragmentsModel::getAlignments() {
    {
            return this->_alignmentsManager.getAlignments();
    }
}

auto FragmentsModel::getHorizontalAlignments() {
    {
            return this->_alignmentsManager.getHorizontalAlignments();
    }
}

auto FragmentsModel::getVerticalAlignments() {
    {
            return this->_alignmentsManager.getVerticalAlignments();
    }
}

auto FragmentsModel::getAlignmentStyles() {
    {
            return this->_alignmentsManager.getAlignmentStyles();
    }
}

auto FragmentsModel::useCamera(js::any camera) {
    {
            this->_viewManager.useCamera(camera);
    }
}

auto FragmentsModel::rectangleRaycast(RectangleRaycastData data) {
    {
            return this->_raycastManager.rectangleRaycast(this, this->_meshManager, data);
    }
}

auto FragmentsModel::raycast(RaycastData data) {
    {
            return this->_raycastManager.raycast(this, data);
    }
}

auto FragmentsModel::raycastWithSnapping(SnappingRaycastData data) {
    {
            return this->_raycastManager.raycastWithSnapping(this, data);
    }
}

auto FragmentsModel::setVisible(js::typed::Nullable<js::array<js::number>> localIds, bool visible) {
    {
            js::array<js::any> args = js::array<js::any>{localIds, visible};
            co_await this->threads.invoke(this->modelId, "setVisible"_S, args);
    }
}

auto FragmentsModel::toggleVisible(std::optional<js::array<js::number>> localIds) {
    {
            js::array<js::any> args = js::array<js::any>{localIds};
            co_await this->threads.invoke(this->modelId, "toggleVisible"_S, args);
    }
}

auto FragmentsModel::getItemsByVisibility(bool visible) {
    {
            return this->_visibilityManager.getItemsByVisibility(this, visible);
    }
}

auto FragmentsModel::getVisible(js::array<js::number> localIds) {
    {
            return this->_visibilityManager.getVisible(this, localIds);
    }
}

auto FragmentsModel::resetVisible() {
    {
            return this->_visibilityManager.resetVisible(this);
    }
}

auto FragmentsModel::highlight(js::typed::Nullable<js::array<js::number>> localIds, MaterialDefinition highlightMaterial) {
    {
            return this->_highlightManager.highlight(this, localIds, highlightMaterial);
    }
}

auto FragmentsModel::getHighlight(std::optional<js::array<js::number>> localIds) {
    {
            return this->_highlightManager.getHighlight(this, localIds);
    }
}

auto FragmentsModel::resetHighlight(std::optional<js::array<js::number>> localIds) {
    {
            return this->_highlightManager.resetHighlight(this, localIds);
    }
}

auto FragmentsModel::getHighlightItemIds() {
    {
            return this->_highlightManager.getHighlightItemIds(this);
    }
}

auto FragmentsModel::getSection(js::any plane, std::optional<js::array<js::number>> localIds) {
    {
            return this->_sectionManager.getSection(this, plane, localIds);
    }
}

auto FragmentsModel::getSequenced(T result, js::array<U> fromItems, std::optional<js::any> inputs) {
    {
            return this->_sequenceManager.getSequenced(this, result, fromItems, inputs);
    }
}

auto FragmentsModel::handleRequest(js::any request) {
    {
            co_await this->_meshManager.requests.handleRequest(this->_meshManager, request);
    }
}

auto FragmentsModel::_finishProcessing() {
    {
            this->_isProcessing = false;
    }
}

auto FragmentsModel::_refreshView() {
    {
            if (this->frozen) {
                        return;
            }
            this->_isProcessing = true;
            co_await this->_viewManager.refreshView(this, this->_meshManager);
    }
}

auto FragmentsModel::_setup(ArrayBuffer data, std::optional<bool> raw, std::optional<VirtualModelConfig> config) {
    {
            if (this->_isSetup) {
                        return;
            }
            co_await this->_setupManager.setup(this, this->_bbox, data, raw, config);
            this->_isLoaded = true;
            this->_isProcessing = true;
            this->_isSetup = true;
    }
}
