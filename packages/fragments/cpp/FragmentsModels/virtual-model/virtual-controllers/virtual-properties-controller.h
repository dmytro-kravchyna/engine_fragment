#ifndef VIRTUAL_PROPERTIES_CONTROLLER_H
#define VIRTUAL_PROPERTIES_CONTROLLER_H

#include "index_generated.h"


#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <map>
#include <optional>
#include <initializer_list>
#include "runtime/core.h"
#include <three.h>
#include "../../bounding-boxes.h"
#include "../../../../Schema.h"
#include "../../model.h"
#include "../../model/model-types.h"

using namespace js;

// Forward declarations
class VirtualPropertiesController;

class VirtualPropertiesController {
public:
    VirtualPropertiesController(Model model, VirtualBoxController boxes, std::optional<VirtualPropertiesConfig> config = std::nullopt);
    virtual auto addInverseRelation(js::string category, js::string relation, js::string inverseName);
    virtual auto getItemsCount();
    virtual auto getMaxLocalId();
    virtual auto getMetadata();
    virtual js::array<js::number> getItemIdsFromLocalIds(std::optional<Iterable> localIds = std::nullopt);
    virtual auto getLocalIdsFromItemIds(Iterable itemIds);
    virtual auto getBox(js::array<js::number> items, js::any result);
    virtual auto getSpatialStructure();
    virtual auto getItemsChildren(js::array<Identifier> ids);
    virtual auto getGuids();
    virtual auto getLocalIds();
    virtual auto getItemsCategories(js::array<Identifier> ids);
    virtual auto getLocalIdsByGuids(js::array<js::string> guids);
    virtual auto getGuidsByLocalIds(js::array<js::number> localIds);
    virtual auto getAttributeNames();
    virtual auto getAttributeValues();
    virtual auto getAttributesUniqueValues(js::array<AttributesUniqueValuesParams> params);
    virtual auto getAttributeTypes();
    virtual auto getRelationNames();
    virtual auto getItemAttributes(Identifier id);
    virtual auto getItemData(Identifier id, js::any config = []() {
      js::object obj_temp_0;
      return js::any(obj_temp_0);
    }());
    virtual auto getItemsData(js::array<Identifier> ids, Partial config = []() {
      js::object obj_temp_1;
      return js::any(obj_temp_1);
    }());
    virtual auto getItemRelations(Identifier id);
    virtual auto getCategories();
    virtual auto getItemsOfCategories(js::array<RegExp> categories);
    virtual auto getItemsWithGeometry();
    virtual auto getItemsWithGeometryCategories();
    virtual auto getItemsByAttribute(GetItemsByAttributeParams param);
    virtual auto getItemsByQuery(ItemsQueryParams params);
private:
    std::shared_ptr<Model> _model;
    std::shared_ptr<VirtualBoxController> _boxes;
    auto _localIdsToGeometryIds;
    auto _guidToLocalIdMap;
    auto _items;
    std::shared_ptr<Map> _itemDataCache;
    std::shared_ptr<ItemsDataConfig> _itemDataConfig;
    js::typed::Nullable<SpatialTreeItem> _spatialStructure;
    auto _relations;
    virtual auto getAllLocalIds();
    virtual auto getItemsByRelation(GetItemsByRelationParams param);
    virtual auto getTreeItem(SpatialStructure item);
    virtual auto preindexGeometryIds();
    virtual auto convertToLocalId(Identifier id);
    virtual auto getChildrenLocalIds(SpatialTreeItem treeItem, Set collector);
    virtual auto traverseSpatialStructure(js::number localId, Set collector, auto treeItem = this->getSpatialStructure());
};

#endif // VIRTUAL_PROPERTIES_CONTROLLER_H