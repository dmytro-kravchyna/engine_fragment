#ifndef FRAGMENTS_MODEL_H
#define FRAGMENTS_MODEL_H

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
#include "./model-types.h"
#include "../utils.h"
#include "../multithreading/fragments-connection.h"
#include "./mesh-manager.h"
#include "./alignments-manager.h"
#include "../../../Utils.h"
#include "./setup-manager.h"
#include "./box-manager.h"
#include "./coordinates-manager.h"
#include "./items-manager.h"
#include "./view-manager.h"
#include "./raycast-manager.h"
#include "./visibility-manager.h"
#include "./highlight-manager.h"
#include "./section-manager.h"
#include "./data-manager.h"
#include "./sequence-manager.h"

using namespace js;

// Forward declarations
class FragmentsModel;

class FragmentsModel {
public:
    auto attrsChanges;
    auto relsChanges;
    std::shared_ptr<FragmentsConnection> threads;
    auto tiles;
    auto object;
    auto graphicsQuality;
    FragmentsModel(js::string modelId, MeshManager meshManager, FragmentsConnection threads);
    virtual auto dispose();
    virtual auto getSpatialStructure();
    virtual auto getLocalIdsByGuids(js::array<js::string> guids);
    virtual auto getCategories();
    virtual auto getItemsWithGeometryCategories();
    virtual auto getItemsWithGeometry();
    virtual auto getItemsIdsWithGeometry();
    virtual auto getMetadata();
    virtual auto getGuidsByLocalIds(js::array<js::number> localIds);
    virtual auto getBuffer(auto raw = false);
    virtual auto getItemsOfCategories(js::array<RegExp> categories);
    virtual auto getGuids();
    virtual auto getLocalIds();
    virtual auto getItemsByQuery(ItemsQueryParams params);
    virtual auto getItemsMaterialDefinition(js::array<js::number> localIds);
    virtual auto getItemsGeometry(js::array<js::number> localIds);
    virtual auto getItemsVolume(js::array<js::number> localIds);
    virtual auto getAttributeNames();
    virtual auto getAttributeValues();
    virtual auto getAttributesUniqueValues(js::array<AttributesUniqueValuesParams> params);
    virtual auto getAttributeTypes();
    virtual auto getRelationNames();
    virtual auto getMaxLocalId();
    virtual auto getItem(Identifier id);
    virtual auto getItemsChildren(js::array<Identifier> ids);
    virtual auto getItemsData(js::array<Identifier> ids, std::optional<Partial> config = std::nullopt);
    virtual auto getPositions(std::optional<js::array<js::number>> localIds = std::nullopt);
    virtual auto getCoordinates();
    virtual auto getCoordinationMatrix();
    virtual auto getMergedBox(js::array<js::number> localIds);
    virtual auto getBoxes(std::optional<js::array<js::number>> localIds = std::nullopt);
    virtual auto getAlignments();
    virtual auto getHorizontalAlignments();
    virtual auto getVerticalAlignments();
    virtual auto getAlignmentStyles();
    virtual auto useCamera(js::any camera);
    virtual auto rectangleRaycast(RectangleRaycastData data);
    virtual auto raycast(RaycastData data);
    virtual auto raycastWithSnapping(SnappingRaycastData data);
    virtual auto setVisible(js::typed::Nullable<js::array<js::number>> localIds, bool visible);
    virtual auto toggleVisible(std::optional<js::array<js::number>> localIds = std::nullopt);
    virtual auto getItemsByVisibility(bool visible);
    virtual auto getVisible(js::array<js::number> localIds);
    virtual auto resetVisible();
    virtual auto highlight(js::typed::Nullable<js::array<js::number>> localIds, MaterialDefinition highlightMaterial);
    virtual auto getHighlight(std::optional<js::array<js::number>> localIds = std::nullopt);
    virtual auto resetHighlight(std::optional<js::array<js::number>> localIds = std::nullopt);
    virtual auto getHighlightItemIds();
    virtual auto getSection(js::any plane, std::optional<js::array<js::number>> localIds = std::nullopt);
    virtual auto getSequenced(T result, js::array<U> fromItems, std::optional<js::any> inputs = std::nullopt);
    virtual auto handleRequest(js::any request);
    virtual auto _finishProcessing();
    virtual auto _refreshView();
    virtual auto _setup(ArrayBuffer data, std::optional<bool> raw = std::nullopt, std::optional<VirtualModelConfig> config = std::nullopt);
private:
    auto _boxManager;
    auto _itemsManager;
    auto _coordinatesManager;
    auto _setupManager;
    auto _viewManager;
    auto _raycastManager;
    auto _visibilityManager;
    auto _highlightManager;
    auto _sectionManager;
    auto _dataManager;
    auto _sequenceManager;
    auto _bbox;
    std::shared_ptr<AlignmentsManager> _alignmentsManager;
    std::shared_ptr<MeshManager> _meshManager;
    auto _isProcessing;
    auto _isLoaded;
    auto _frozen;
    auto _isSetup;
};

#endif // FRAGMENTS_MODEL_H