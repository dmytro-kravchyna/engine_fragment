#ifndef VIRTUAL_FRAGMENTS_MODEL_H
#define VIRTUAL_FRAGMENTS_MODEL_H

#include "index_generated.h"


#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <map>
#include <optional>
#include <initializer_list>
#include "runtime/core.h"
#include "runtime/async.h"
#include <three.h>
#include <flatbuffers.h>
#include <pako.h>
#include <three-mesh-bvh.h>
#include "./virtual-controllers.h"
#include "../model/model-types.h"
#include "../bounding-boxes.h"
#include "../multithreading/connection.h"
#include "../../../Schema.h"
#include "./virtual-helpers.h"

using namespace js;

// Forward declarations
class VirtualFragmentsModel;

class VirtualFragmentsModel {
public:
    std::shared_ptr<Model> data;
    js::any view;
    std::shared_ptr<RaycastController> raycaster;
    std::shared_ptr<ItemConfigController> itemConfig;
    std::shared_ptr<VirtualPropertiesController> properties;
    std::shared_ptr<VirtualMaterialController> materials;
    std::shared_ptr<VirtualTilesController> tiles;
    std::shared_ptr<VirtualBoxController> boxes;
    VirtualFragmentsModel(js::string modelId, ArrayBuffer data, Connection connection, std::optional<VirtualModelConfig> config = std::nullopt);
    virtual auto getItemsByConfig(std::function<bool(js::number)> condition);
    virtual auto getItemsCategories(js::array<js::number> ids);
    virtual auto getItemIdsByLocalIds(js::array<js::number> localIds);
    virtual auto getItemAttributes(js::number id);
    virtual auto getAttributesUniqueValues(js::array<AttributesUniqueValuesParams> config);
    virtual auto getItemsData(js::array<js::number> ids, js::any config);
    virtual auto getItemsOfCategories(js::array<RegExp> categories);
    virtual auto getItemsWithGeometry();
    virtual auto getItemsWithGeometryCategories();
    virtual auto getItemsByQuery(ItemsQueryParams params);
    virtual auto getItemRelations(js::number id);
    virtual auto getSpatialStructure();
    virtual auto getMaxLocalId();
    virtual auto getCategories();
    virtual auto getMetadata();
    virtual auto getLocalIdsByGuids(js::array<js::string> guids);
    virtual auto getGuidsByLocalIds(js::array<js::number> localIds);
    virtual auto getSequenced(ItemInformationType result, js::array<ItemSelectionType> fromItems, std::optional<js::any> inputs = std::nullopt);
    virtual auto highlight(js::array<js::number> items, MaterialDefinition highlightMaterial);
    virtual auto getHighlight(js::array<js::number> localIds);
    virtual auto getHighlightItemIds();
    virtual auto resetHighlight(js::array<js::number> items);
    virtual auto getCoordinates();
    virtual auto getPositions(js::array<js::number> localIds);
    virtual js::number getGeometriesLength();
    virtual auto getGuids();
    virtual auto getLocalIds();
    virtual auto getItemsGeometry(js::array<js::number> localIds);
    virtual auto getItemsVolume(js::array<js::number> localIds);
    virtual auto getAttributeNames();
    virtual auto getAttributeValues();
    virtual auto getAttributeTypes();
    virtual auto getRelationNames();
    virtual auto getItemsMaterialDefinition(js::array<js::number> localIds);
    virtual auto resetVisible();
    virtual auto getItemsByVisibility(bool visible);
    virtual js::any raycast(js::any ray, js::any frustum);
    virtual js::array<js::any> snapRaycast(js::any ray, js::any frustum, js::array<SnappingClass> snaps);
    virtual js::array<js::number> rectangleRaycast(js::any frustum, bool fullyIncluded);
    virtual auto getSection(js::any plane, std::optional<js::array<js::number>> localIds = std::nullopt);
    virtual auto getAlignments();
    virtual auto getBuffer(bool raw);
    virtual auto dispose();
    virtual auto setVisible(js::array<js::number> localIds, bool visible);
    virtual auto toggleVisible(js::array<js::number> localIds);
    virtual auto getVisible(js::array<js::number> items);
    virtual auto getItemsChildren(js::array<Identifier> ids);
    virtual auto setupData();
    virtual auto refreshView(js::any view);
    virtual auto getFullBBox();
    virtual auto getBBoxes(js::array<js::number> items);
    virtual auto traverse(js::array<js::number> itemIds, std::function<void(js::number, js::number)> onItem);
    virtual bool update(js::number time);
private:
    auto _raycastHelper;
    auto _coordinatesHelper;
    auto _highlightHelper;
    auto _visibilityHelper;
    auto _geometryHelper;
    auto _sectionHelper;
    auto _itemsHelper;
    auto _sequenceHelper;
    std::shared_ptr<VirtualModelConfig> _config;
    js::string _modelId;
    std::shared_ptr<AlignmentsController> _alignments;
    std::shared_ptr<Connection> _connection;
    virtual auto setupBVH();
    virtual auto setupProperties();
    virtual auto setupRaycaster();
    virtual auto setupMaterials(js::string modelId);
    virtual auto setupTiles();
    virtual auto setupModel(ArrayBuffer data);
    auto _onTransferMaterial;
    virtual auto setupItemsConfig();
};

#endif // VIRTUAL_FRAGMENTS_MODEL_H