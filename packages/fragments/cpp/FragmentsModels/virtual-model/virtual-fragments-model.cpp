#include "index_generated.h"
#include "virtual-fragments-model.h"

using namespace js;

VirtualFragmentsModel::VirtualFragmentsModel(js::string modelId, ArrayBuffer data, Connection connection, std::optional<VirtualModelConfig> config) {
    {
            this->_modelId = modelId;
            this->_connection = connection;
            this->_config = []() {
                  js::object obj_temp_0;
                  return js::any(obj_temp_0);
                }();
            this->data = this->setupModel(data);
            this->boxes = std::make_shared<VirtualBoxController>(this->data);
            this->materials = this->setupMaterials(modelId);
            this->_alignments = std::make_shared<AlignmentsController>(this->data);
            this->itemConfig = this->setupItemsConfig();
            this->tiles = this->setupTiles();
            this->properties = this->setupProperties();
            this->raycaster = this->setupRaycaster();
            this->setupBVH();
    }
}

auto VirtualFragmentsModel::getItemsByConfig(std::function<bool(js::number)> condition) {
    {
            return this->_itemsHelper.getItemsByConfig(this, condition);
    }
}

auto VirtualFragmentsModel::getItemsCategories(js::array<js::number> ids) {
    {
            return this->properties.getItemsCategories(ids);
    }
}

auto VirtualFragmentsModel::getItemIdsByLocalIds(js::array<js::number> localIds) {
    {
            return this->properties.getItemIdsFromLocalIds(localIds);
    }
}

auto VirtualFragmentsModel::getItemAttributes(js::number id) {
    {
            return this->properties.getItemAttributes(id);
    }
}

auto VirtualFragmentsModel::getAttributesUniqueValues(js::array<AttributesUniqueValuesParams> config) {
    {
            return this->properties.getAttributesUniqueValues(config);
    }
}

auto VirtualFragmentsModel::getItemsData(js::array<js::number> ids, js::any config) {
    {
            return this->properties.getItemsData(ids, config);
    }
}

auto VirtualFragmentsModel::getItemsOfCategories(js::array<RegExp> categories) {
    {
            return this->properties.getItemsOfCategories(categories);
    }
}

auto VirtualFragmentsModel::getItemsWithGeometry() {
    {
            return this->properties.getItemsWithGeometry();
    }
}

auto VirtualFragmentsModel::getItemsWithGeometryCategories() {
    {
            return this->properties.getItemsWithGeometryCategories();
    }
}

auto VirtualFragmentsModel::getItemsByQuery(ItemsQueryParams params) {
    {
            return this->properties.getItemsByQuery(params);
    }
}

auto VirtualFragmentsModel::getItemRelations(js::number id) {
    {
            return this->properties.getItemRelations(id);
    }
}

auto VirtualFragmentsModel::getSpatialStructure() {
    {
            return this->properties.getSpatialStructure();
    }
}

auto VirtualFragmentsModel::getMaxLocalId() {
    {
            return this->properties.getMaxLocalId();
    }
}

auto VirtualFragmentsModel::getCategories() {
    {
            return this->properties.getCategories();
    }
}

auto VirtualFragmentsModel::getMetadata() {
    {
            return this->properties.getMetadata();
    }
}

auto VirtualFragmentsModel::getLocalIdsByGuids(js::array<js::string> guids) {
    {
            return this->properties.getLocalIdsByGuids(guids);
    }
}

auto VirtualFragmentsModel::getGuidsByLocalIds(js::array<js::number> localIds) {
    {
            return this->properties.getGuidsByLocalIds(localIds);
    }
}

auto VirtualFragmentsModel::getSequenced(ItemInformationType result, js::array<ItemSelectionType> fromItems, std::optional<js::any> inputs) {
    {
            return this->_sequenceHelper.getSequenced(result, fromItems, inputs);
    }
}

auto VirtualFragmentsModel::highlight(js::array<js::number> items, MaterialDefinition highlightMaterial) {
    {
            this->_highlightHelper.highlight(this, items, highlightMaterial);
    }
}

auto VirtualFragmentsModel::getHighlight(js::array<js::number> localIds) {
    {
            return this->_highlightHelper.getHighlight(this, localIds);
    }
}

auto VirtualFragmentsModel::getHighlightItemIds() {
    {
            return this->_highlightHelper.getHighlightItems(this);
    }
}

auto VirtualFragmentsModel::resetHighlight(js::array<js::number> items) {
    {
            this->_highlightHelper.resetHighlight(this, items);
    }
}

auto VirtualFragmentsModel::getCoordinates() {
    {
            return this->_coordinatesHelper.getCoordinates(this);
    }
}

auto VirtualFragmentsModel::getPositions(js::array<js::number> localIds) {
    {
            return this->_coordinatesHelper.getPositions(this, localIds);
    }
}

js::number VirtualFragmentsModel::getGeometriesLength() {
    {
            return this->_geometryHelper.getGeometriesLength(this);
    }
}

auto VirtualFragmentsModel::getGuids() {
    {
            return this->properties.getGuids();
    }
}

auto VirtualFragmentsModel::getLocalIds() {
    {
            return this->properties.getLocalIds();
    }
}

auto VirtualFragmentsModel::getItemsGeometry(js::array<js::number> localIds) {
    {
            const js::any indices = this->properties.getItemIdsFromLocalIds(localIds);
            js::array<js::array<MeshData>> geometries = js::array<js::any>{};
            for (const auto& index : indices) {
                        {
                                        const js::any geometry = this->_geometryHelper.getGeometry(this, index);
                                        geometries.push(geometry);
                        }
            }
            return geometries;
    }
}

auto VirtualFragmentsModel::getItemsVolume(js::array<js::number> localIds) {
    {
            const js::any indices = this->properties.getItemIdsFromLocalIds(localIds);
            js::number volume = js::number(0);
            for (const auto& index : indices) {
                        {
                                        volume += this->_geometryHelper.getVolume(this, index);
                        }
            }
            return volume;
    }
}

auto VirtualFragmentsModel::getAttributeNames() {
    {
            const js::any names = this->properties.getAttributeNames();
            return names;
    }
}

auto VirtualFragmentsModel::getAttributeValues() {
    {
            const js::any values = this->properties.getAttributeValues();
            return values;
    }
}

auto VirtualFragmentsModel::getAttributeTypes() {
    {
            const js::any types = this->properties.getAttributeTypes();
            return types;
    }
}

auto VirtualFragmentsModel::getRelationNames() {
    {
            const js::any names = this->properties.getRelationNames();
            return names;
    }
}

auto VirtualFragmentsModel::getItemsMaterialDefinition(js::array<js::number> localIds) {
    {
            const js::any indices = this->properties.getItemIdsFromLocalIds(localIds);
            return this->materials.getItemsMaterialDefinition(this->data, indices, localIds);
    }
}

auto VirtualFragmentsModel::resetVisible() {
    {
            this->_visibilityHelper.resetVisible(this);
    }
}

auto VirtualFragmentsModel::getItemsByVisibility(bool visible) {
    {
            return this->_visibilityHelper.getItemsByVisibility(this, visible);
    }
}

js::any VirtualFragmentsModel::raycast(js::any ray, js::any frustum) {
    {
            return this->_raycastHelper.raycast(this, ray, frustum);
    }
}

js::array<js::any> VirtualFragmentsModel::snapRaycast(js::any ray, js::any frustum, js::array<SnappingClass> snaps) {
    {
            return this->_raycastHelper.snapRaycast(this, ray, frustum, snaps);
    }
}

js::array<js::number> VirtualFragmentsModel::rectangleRaycast(js::any frustum, bool fullyIncluded) {
    {
            return this->_raycastHelper.rectangleRaycast(this, frustum, fullyIncluded);
    }
}

auto VirtualFragmentsModel::getSection(js::any plane, std::optional<js::array<js::number>> localIds) {
    {
            const js::any indices = this->properties.getItemIdsFromLocalIds(localIds);
            return this->_sectionHelper.getSection(this, plane, indices);
    }
}

auto VirtualFragmentsModel::getAlignments() {
    {
            return this->_alignments.getAlignments();
    }
}

auto VirtualFragmentsModel::getBuffer(bool raw) {
    {
            const js::any bb = this->data.bb;
            const js::any bytes = bb["bytes"]();
            const js::any buffer = bytes["buffer"];
            return (js::null ? js::null : js::null);
    }
}

auto VirtualFragmentsModel::dispose() {
    {
            this->tiles.dispose();
    }
}

auto VirtualFragmentsModel::setVisible(js::array<js::number> localIds, bool visible) {
    {
            this->_visibilityHelper.setVisible(this, localIds, visible);
    }
}

auto VirtualFragmentsModel::toggleVisible(js::array<js::number> localIds) {
    {
            this->_visibilityHelper.toggleVisible(this, localIds);
    }
}

auto VirtualFragmentsModel::getVisible(js::array<js::number> items) {
    {
            return this->_visibilityHelper.getVisible(this, items);
    }
}

auto VirtualFragmentsModel::getItemsChildren(js::array<Identifier> ids) {
    {
            return this->properties.getItemsChildren(ids);
    }
}

auto VirtualFragmentsModel::setupData() {
    {
            this->tiles.generate();
    }
}

auto VirtualFragmentsModel::refreshView(js::any view) {
    {
            this->view = view;
            this->tiles.setupView(view);
    }
}

auto VirtualFragmentsModel::getFullBBox() {
    {
            return this->boxes.fullBox;
    }
}

auto VirtualFragmentsModel::getBBoxes(js::array<js::number> items) {
    {
            const std::shared_ptr<three::Box3> box = std::make_shared<three::Box3>();
            this->properties.getBox(items, box);
            return box;
    }
}

auto VirtualFragmentsModel::traverse(js::array<js::number> itemIds, std::function<void(js::number, js::number)> onItem) {
    {
            this->_itemsHelper.traverse(this, itemIds, onItem);
    }
}

bool VirtualFragmentsModel::update(js::number time) {
    {
            this->tiles.update(time);
            return this->tiles.tilesUpdated;
    }
}

auto VirtualFragmentsModel::setupBVH() {
    {
            three::BufferGeometry.prototype.computeBoundsTree = computeBoundsTree;
            three::BufferGeometry.prototype.disposeBoundsTree = disposeBoundsTree;
            three::Mesh.prototype.raycast = acceleratedRaycast;
    }
}

auto VirtualFragmentsModel::setupProperties() {
    {
            return std::make_shared<VirtualPropertiesController>(this->data, this->boxes, this->_config.properties);
    }
}

auto VirtualFragmentsModel::setupRaycaster() {
    {
            return std::make_shared<RaycastController>(this->data, this->boxes, this->tiles, this->itemConfig);
    }
}

auto VirtualFragmentsModel::setupMaterials(js::string modelId) {
    {
            return std::make_shared<VirtualMaterialController>(modelId, this->_onTransferMaterial);
    }
}

auto VirtualFragmentsModel::setupTiles() {
    {
            const js::any materials = this->materials.update(this->data);
            return std::make_shared<VirtualTilesController>([]() {
                  js::object obj_temp_1;
                  obj_temp_1.set("modelId", this->_modelId);
                  obj_temp_1.set("connection", this->_connection);
                  obj_temp_1.set("model", this->data);
                  obj_temp_1.set("boxes", this->boxes);
                  obj_temp_1.set("items", this->itemConfig);
                  obj_temp_1.set("materials", materials);
                  return js::any(obj_temp_1);
                }());
    }
}

auto VirtualFragmentsModel::setupModel(ArrayBuffer data) {
    {
            const std::shared_ptr<Uint8Array> uintArray = std::make_shared<Uint8Array>(data);
            const std::shared_ptr<ByteBuffer> byteBuffer = std::make_shared<ByteBuffer>(uintArray);
            return Model::getRootAsModel(byteBuffer);
    }
}

auto VirtualFragmentsModel::setupItemsConfig() {
    {
            const js::any itemsCount = this->data.localIdsLength();
            return std::make_shared<ItemConfigController>(itemsCount);
    }
}
