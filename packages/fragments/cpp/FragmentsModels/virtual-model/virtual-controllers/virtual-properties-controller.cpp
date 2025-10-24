#include "index_generated.h"
#include "virtual-properties-controller.h"

using namespace js;

VirtualPropertiesController::VirtualPropertiesController(Model model, VirtualBoxController boxes, std::optional<VirtualPropertiesConfig> config) {
    {
            this->_model = model;
            this->_boxes = boxes;
            this->preindexGeometryIds();
            if ((config && config["extraRelations"])) {
                        {
                                        for (const auto& extra : config["extraRelations"]) {
                                                            {
                                                                                    auto _temp7568 = extra;
                                                                                    const auto category = _temp7568["category"];
                                                                                    const auto relation = _temp7568["relation"];
                                                                                    const auto inverseName = _temp7568["inverseName"];
                                                                                    this->addInverseRelation(category, relation, inverseName);
                                                            }
                                        }
                        }
            }
            const js::any localIds = this->_model.localIdsArray();
            if (localIds) {
                        {
                                        for (js::number i = js::number(0); (i < this->_model.localIdsLength()); i++) {
                                                            {
                                                                                    const js::any category = this->_model.categories(i);
                                                                                    const js::any localId = localIds->i;
                                                                                    js::any itemInfo = this->_items.get(localId);
                                                                                    if (!itemInfo) {
                                                                                                                {
                                                                                                                                                itemInfo = []() {
                                                                                                                                                      js::object obj_temp_2;
                                                                                                                                                      obj_temp_2.set("category", js::null);
                                                                                                                                                      obj_temp_2.set("guid", js::null);
                                                                                                                                                      obj_temp_2.set("geometryIds", js::null);
                                                                                                                                                      obj_temp_2.set("attrs", js::null);
                                                                                                                                                      return js::any(obj_temp_2);
                                                                                                                                                    }();
                                                                                                                                                this->_items.set(localId, itemInfo);
                                                                                                                }
                                                                                    }
                                                                                    itemInfo->category = category;
                                                            }
                                        }
                                        for (js::number i = js::number(0); (i < this->_model.guidsItemsLength()); i++) {
                                                            {
                                                                                    const js::any localId = this->_model.guidsItems(i);
                                                                                    if (localId === js::null) {
                                                                                                                continue;
                                                                                    }
                                                                                    const js::any guid = this->_model.guids(i);
                                                                                    this->_guidToLocalIdMap.set(guid, localId);
                                                                                    js::any itemInfo = this->_items.get(localId);
                                                                                    if (!itemInfo) {
                                                                                                                {
                                                                                                                                                itemInfo = []() {
                                                                                                                                                      js::object obj_temp_3;
                                                                                                                                                      obj_temp_3.set("category", js::null);
                                                                                                                                                      obj_temp_3.set("guid", js::null);
                                                                                                                                                      obj_temp_3.set("geometryIds", js::null);
                                                                                                                                                      obj_temp_3.set("attrs", js::null);
                                                                                                                                                      return js::any(obj_temp_3);
                                                                                                                                                    }();
                                                                                                                                                this->_items.set(localId, itemInfo);
                                                                                                                }
                                                                                    }
                                                                                    itemInfo->guid = guid;
                                                            }
                                        }
                        }
            }
    }
}

auto VirtualPropertiesController::getAllLocalIds() {
    {
            return (this->_model.localIdsArray().has_value() ? this->_model.localIdsArray() : js::array<js::any>{});
    }
}

auto VirtualPropertiesController::addInverseRelation(js::string category, js::string relation, js::string inverseName) {
    {
            const js::any categoriesIds = this->getItemsOfCategories(js::array<js::any>{js::RegExp(("^"_S + js::toString(category) + "$"_S))});
            const js::any psetLocalIds = categoriesIds->category;
            for (const auto& psetId : psetLocalIds) {
                        {
                                        const js::any relations = this->getItemRelations(psetId);
                                        if (!(relations && relations[relation])) {
                                                            continue;
                                        }
                                        const js::any localIds = relations[relation];
                                        for (const auto& itemId : localIds) {
                                                            {
                                                                                    js::any relationsObject = this->_relations.get(itemId);
                                                                                    if (!relationsObject) {
                                                                                                                {
                                                                                                                                                relationsObject = []() {
                                                                                                                                                      js::object obj_temp_4;
                                                                                                                                                      return js::any(obj_temp_4);
                                                                                                                                                    }();
                                                                                                                                                this->_relations.set(itemId, relationsObject);
                                                                                                                }
                                                                                    }
                                                                                    js::any inverse = relationsObject->inverseName;
                                                                                    if (!inverse) {
                                                                                                                {
                                                                                                                                                inverse = js::array<js::any>{};
                                                                                                                                                relationsObject->inverseName = inverse;
                                                                                                                }
                                                                                    }
                                                                                    inverse.push(psetId);
                                                            }
                                        }
                        }
            }
    }
}

auto VirtualPropertiesController::getItemsCount() {
    {
            return this->_model.localIdsLength();
    }
}

auto VirtualPropertiesController::getMaxLocalId() {
    {
            return this->_model.maxLocalId();
    }
}

auto VirtualPropertiesController::getMetadata() {
    {
            const js::any metadata = this->_model.metadata();
            if (!metadata) {
                        {
                                        return js::null;
                        }
            }
            return js::JSON::parse(metadata);
    }
}

js::array<js::number> VirtualPropertiesController::getItemIdsFromLocalIds(std::optional<Iterable> localIds) {
    {
            if (!localIds) {
                        {
                                        return js::array.from(this->_model.meshes().meshesItemsArray());
                        }
            }
            js::array<js::number> itemIds = js::array<js::any>{};
            for (const auto& localId : localIds) {
                        {
                                        const js::any found = this->_localIdsToGeometryIds.get(localId);
                                        if (!found) {
                                                            continue;
                                        }
                                        for (const auto& itemId : found) {
                                                            {
                                                                                    itemIds.push(itemId);
                                                            }
                                        }
                        }
            }
            return itemIds;
    }
}

auto VirtualPropertiesController::getLocalIdsFromItemIds(Iterable itemIds) {
    {
            js::array<js::number> result = js::array<js::any>{};
            const js::any entries = this->_localIdsToGeometryIds.entries();
            for (const auto& js::undefined : entries) {
                        {
                                        for (const auto& itemId : itemIds) {
                                                            {
                                                                                    if (!geometryIds.includes(itemId)) {
                                                                                                                continue;
                                                                                    }
                                                                                    result.push(localId);
                                                            }
                                        }
                        }
            }
            return result;
    }
}

auto VirtualPropertiesController::getBox(js::array<js::number> items, js::any result) {
    {
            for (const auto& itemId : items) {
                        {
                                        const js::any currentBoxesIds = this->_boxes.sampleOf(itemId);
                                        if (currentBoxesIds) {
                                                            {
                                                                                    for (const auto& currentBoxId : currentBoxesIds) {
                                                                                                                {
                                                                                                                                                const js::any currentBox = this->_boxes.get(currentBoxId);
                                                                                                                                                result->union(currentBox);
                                                                                                                }
                                                                                    }
                                                            }
                                        }
                        }
            }
    }
}

auto VirtualPropertiesController::getSpatialStructure() {
    {
            if (this->_spatialStructure) {
                        {
                                        return this->_spatialStructure;
                        }
            }
            const js::any structure = this->_model.spatialStructure();
            if (!structure) {
                        {
                                        return []() {
                                              js::object obj_temp_5;
                                              return js::any(obj_temp_5);
                                            }();
                        }
            }
            this->_spatialStructure = this->getTreeItem(structure);
            return this->_spatialStructure;
    }
}

auto VirtualPropertiesController::getItemsChildren(js::array<Identifier> ids) {
    {
            const std::shared_ptr<Set> result = std::make_shared<Set>();
            for (const auto& id : ids) {
                        {
                                        const js::any localId = this->convertToLocalId(id);
                                        if (localId === js::null) {
                                                            continue;
                                        }
                                        this->traverseSpatialStructure(localId, result);
                        }
            }
            return js::array<js::any>().concat(result);
    }
}

auto VirtualPropertiesController::getGuids() {
    {
            js::array<js::string> guids = js::array<js::any>{};
            for (js::number i = js::number(0); (i < this->_model.guidsLength()); i++) {
                        {
                                        const js::any guid = this->_model.guids(i);
                                        guids.push(guid);
                        }
            }
            return guids;
    }
}

auto VirtualPropertiesController::getLocalIds() {
    {
            const js::any array = this->_model.localIdsArray();
            if (!array) {
                        return js::array<js::any>{};
            }
            return js::array.from(array);
    }
}

auto VirtualPropertiesController::getItemsCategories(js::array<Identifier> ids) {
    {
            js::array<js::typed::Nullable<js::string>> result = js::array<js::any>{};
            for (const auto& id : ids) {
                        {
                                        const js::any localId = this->convertToLocalId(id);
                                        if (localId === js::null) {
                                                            continue;
                                        }
                                        const js::any category = (this->_items.get(localId).category.has_value() ? this->_items.get(localId).category : js::null);
                                        result.push(category);
                        }
            }
            return result;
    }
}

auto VirtualPropertiesController::getLocalIdsByGuids(js::array<js::string> guids) {
    {
            js::array<js::typed::Nullable<js::number>> result = js::array<js::any>{};
            for (const auto& guid : guids) {
                        {
                                        const js::any localId = this->_guidToLocalIdMap.get(guid);
                                        result.push((js::null ? js::null : js::null));
                        }
            }
            return result;
    }
}

auto VirtualPropertiesController::getGuidsByLocalIds(js::array<js::number> localIds) {
    {
            js::array<js::typed::Nullable<js::string>> result = js::array<js::any>{};
            for (const auto& id : localIds) {
                        {
                                        const js::any guid = this->_items.get(id).guid;
                                        result.push((js::null ? js::null : js::null));
                        }
            }
            return result;
    }
}

auto VirtualPropertiesController::getAttributeNames() {
    {
            const std::shared_ptr<Set> names = std::make_shared<Set>();
            for (js::number i = js::number(0); (i < this->_model.uniqueAttributesLength()); i++) {
                        {
                                        const js::any attribute = this->_model.uniqueAttributes(i);
                                        if (!attribute) {
                                                            continue;
                                        }
                                        auto _temp5578 = js::JSON::parse(attribute);
                                        const auto name = _temp5578[0];
                                        names["add"](name);
                        }
            }
            return js::array<js::any>().concat(names);
    }
}

auto VirtualPropertiesController::getAttributeValues() {
    {
            const std::shared_ptr<Set> values = std::make_shared<Set>();
            for (js::number i = js::number(0); (i < this->_model.uniqueAttributesLength()); i++) {
                        {
                                        const js::any attribute = this->_model.uniqueAttributes(i);
                                        if (!attribute) {
                                                            continue;
                                        }
                                        auto _temp4401 = js::JSON::parse(attribute);
                                        const auto value = _temp4401[1];
                                        values["add"](value);
                        }
            }
            return js::array<js::any>().concat(values);
    }
}

auto VirtualPropertiesController::getAttributesUniqueValues(js::array<AttributesUniqueValuesParams> params) {
    {
            const std::shared_ptr<Map> map = std::make_shared<Map>();
            const js::any areCategoriesDefined = params.every([&](auto value) -> auto { return value["categories"] !== js::undefined; });
            const js::any categoriesRegex = params.map([&](auto value) -> auto { return value["categories"]; }).filter([&](auto value) -> auto { return value !== js::undefined; }).flat();
            for (js::number i = js::number(0); (i < this->_model.categoriesLength()); i++) {
                        {
                                        bool valid = true;
                                        if (areCategoriesDefined) {
                                                            {
                                                                                    const js::any category = this->_model.categories(i);
                                                                                    valid = categoriesRegex.some([&](auto regex) -> auto { return regex["test"](category); });
                                                            }
                                        }
                                        if (!valid) {
                                                            continue;
                                        }
                                        const js::any buffer = this->_model.attributes(i);
                                        if (!buffer) {
                                                            continue;
                                        }
                                        const Record attributeSet = []() {
                                              js::object obj_temp_6;
                                              return js::any(obj_temp_6);
                                            }();
                                        for (js::number j = js::number(0); (j < buffer["dataLength"]()); j++) {
                                                            {
                                                                                    const js::any attr = buffer["data"](j);
                                                                                    if (!attr) {
                                                                                                                continue;
                                                                                    }
                                                                                    auto _temp8812 = js::JSON::parse(attr);
                                                                                    const auto name = _temp8812[0];
                                                                                    const auto value = _temp8812[1];
                                                                                    const auto type = _temp8812[2];
                                                                                    attributeSet->name = []() {
                                                                                          js::object obj_temp_7;
                                                                                          obj_temp_7.set("value", value);
                                                                                          obj_temp_7.set("type", type);
                                                                                          return js::any(obj_temp_7);
                                                                                        }();
                                                            }
                                        }
                                        const js::any keys = js::Object::keys(attributeSet);
                                        const js::any category = this->_model.categories(i);
                                        for (const auto& js::undefined : params) {
                                                            {
                                                                                    bool categoryMatch = true;
                                                                                    if (categories) {
                                                                                                                {
                                                                                                                                                categoryMatch = categories.some([&](auto value) -> auto { return value["test"](category); });
                                                                                                                }
                                                                                    }
                                                                                    if (!categoryMatch) {
                                                                                                                continue;
                                                                                    }
                                                                                    bool setPasses = true;
                                                                                    if (attributes) {
                                                                                                                {
                                                                                                                                                auto _temp4203 = attributes;
                                                                                                                                                const auto aggregation = _temp4203["aggregation"];
                                                                                                                                                const auto queries = _temp4203["queries"];
                                                                                                                                                js::array<bool> queryResults = js::array<js::any>{};
                                                                                                                                                for (const auto& js::undefined : queries) {
                                                                                                                                                                                    {
                                                                                                                                                                                                                            const js::any key = keys.find([&](auto key) -> auto { return name["test"](key); });
                                                                                                                                                                                                                            if (!(key && attributeSet->key->value !== js::undefined)) {
                                                                                                                                                                                                                                                                        break;
                                                                                                                                                                                                                            }
                                                                                                                                                                                                                            bool pass = false;
                                                                                                                                                                                                                            auto _temp681 = attributeSet->key;
                                                                                                                                                                                                                            const auto keyValue = _temp681["value"];
                                                                                                                                                                                                                            const auto keyType = _temp681["type"];
                                                                                                                                                                                                                            if (js::instanceof_op(value, "js::RegExp")) {
                                                                                                                                                                                                                                                                        {
                                                                                                                                                                                                                                                                                                                        pass = (js::typeof_op(keyValue) === "string"_S && value["test"](keyValue));
                                                                                                                                                                                                                                                                        }
                                                                                                                                                                                                                            } else {
                                                                                                                                                                                                                                                                        {
                                                                                                                                                                                                                                                                                                                        pass = keyValue === value;
                                                                                                                                                                                                                                                                        }
                                                                                                                                                                                                                            }
                                                                                                                                                                                                                            if (type !== js::undefined) {
                                                                                                                                                                                                                                                                        {
                                                                                                                                                                                                                                                                                                                        pass = ((pass && js::typeof_op(keyType) === "string"_S) && type["test"](keyType));
                                                                                                                                                                                                                                                                        }
                                                                                                                                                                                                                            }
                                                                                                                                                                                                                            if (negate) {
                                                                                                                                                                                                                                                                        pass = !pass;
                                                                                                                                                                                                                            }
                                                                                                                                                                                                                            queryResults.push(pass);
                                                                                                                                                                                    }
                                                                                                                                                }
                                                                                                                                                setPasses = (js::null ? js::null : js::null);
                                                                                                                }
                                                                                    }
                                                                                    if (setPasses) {
                                                                                                                {
                                                                                                                                                const js::any key = keys.find([&](auto key) -> auto { return get["test"](key); });
                                                                                                                                                if (!(key && attributeSet->key->value !== js::undefined)) {
                                                                                                                                                                                    continue;
                                                                                                                                                }
                                                                                                                                                const js::any mapKey = (resultKey.has_value() ? resultKey : key);
                                                                                                                                                js::any values = map["get"](mapKey);
                                                                                                                                                if (!values) {
                                                                                                                                                                                    {
                                                                                                                                                                                                                            values = std::make_shared<Set>();
                                                                                                                                                                                                                            map["set"](mapKey, values);
                                                                                                                                                                                    }
                                                                                                                                                }
                                                                                                                                                values["add"](attributeSet->key->value);
                                                                                                                }
                                                                                    }
                                                            }
                                        }
                        }
            }
            const js::any result = []() {
                  js::object obj_temp_8;
                  return js::any(obj_temp_8);
                }();
            for (const auto& js::undefined : map) {
                        {
                                        result->name = js::array.from(values);
                        }
            }
            return result;
    }
}

auto VirtualPropertiesController::getAttributeTypes() {
    {
            const std::shared_ptr<Set> types = std::make_shared<Set>();
            for (js::number i = js::number(0); (i < this->_model.uniqueAttributesLength()); i++) {
                        {
                                        const js::any attribute = this->_model.uniqueAttributes(i);
                                        if (!attribute) {
                                                            continue;
                                        }
                                        auto _temp2107 = js::JSON::parse(attribute);
                                        const auto type = _temp2107[2];
                                        types["add"](type);
                        }
            }
            return js::array<js::any>().concat(types);
    }
}

auto VirtualPropertiesController::getRelationNames() {
    {
            const std::shared_ptr<Set> names = std::make_shared<Set>();
            for (js::number i = js::number(0); (i < this->_model.relationNamesLength()); i++) {
                        {
                                        const js::any name = this->_model.relationNames(i);
                                        if (!name) {
                                                            continue;
                                        }
                                        names["add"](name);
                        }
            }
            return js::array<js::any>().concat(names);
    }
}

auto VirtualPropertiesController::getItemAttributes(Identifier id) {
    {
            const js::any isLocalId = js::typeof_op(id) === "number"_S;
            const js::any localId = (js::null ? js::null : js::null);
            if (localId === js::null) {
                        {
                                        return js::null;
                        }
            }
            const js::any index = this->_model.localIdsArray().indexOf(localId);
            if ((index === js::undefined || index === -js::number(1))) {
                        {
                                        return js::null;
                        }
            }
            const js::any buffer = this->_model.attributes(index);
            if (!buffer) {
                        {
                                        return js::null;
                        }
            }
            const Record data = []() {
                  js::object obj_temp_9;
                  return js::any(obj_temp_9);
                }();
            for (js::number j = js::number(0); (j < buffer["dataLength"]()); j++) {
                        {
                                        const js::any attr = buffer["data"](j);
                                        if (!attr) {
                                                            {
                                                                                    continue;
                                                            }
                                        }
                                        auto _temp1686 = js::JSON::parse(attr);
                                        const auto name = _temp1686[0];
                                        const auto value = _temp1686[1];
                                        const auto type = _temp1686[2];
                                        data->name = []() {
                                              js::object obj_temp_10;
                                              obj_temp_10.set("value", value);
                                              obj_temp_10.set("type", type);
                                              return js::any(obj_temp_10);
                                            }();
                        }
            }
            return data;
    }
}

auto VirtualPropertiesController::getItemData(Identifier id, js::any config) {
    {
            const js::any allAttributes = this->_itemDataConfig.attributesDefault;
            const js::any attributesConfig = this->_itemDataConfig.attributes;
            const js::any relationsConfig = (this->_itemDataConfig.relations.has_value() ? this->_itemDataConfig.relations : []() {
                  js::object obj_temp_11;
                  return js::any(obj_temp_11);
                }());
            auto _temp272 = this->_itemDataConfig.relationsDefault;
            auto attributes = _temp272["attributes"];
            auto relations = _temp272["relations"];
            auto _temp6549 = config;
            const auto parentName = _temp6549["parentName"];
            const auto rel = _temp6549["rel"];
            if ((!parentName && !rel)) {
                        {
                                        attributes = true;
                                        relations = true;
                        }
            } else {
                        {
                                        const js::any hasRelConfig = (rel && js::in_op(rel, relationsConfig));
                                        const js::any hasParentConfig = (parentName && js::in_op(parentName, relationsConfig));
                                        if (hasRelConfig) {
                                                            {
                                                                                    const js::any toProcess = relationsConfig->rel;
                                                                                    if (toProcess) {
                                                                                                                {
                                                                                                                                                attributes = toProcess->attributes;
                                                                                                                                                relations = toProcess->relations;
                                                                                                                }
                                                                                    }
                                                            }
                                        } else {
                                                            if (hasParentConfig) {
                                                                                    {
                                                                                                                const js::any toProcess = relationsConfig->parentName;
                                                                                                                if (toProcess) {
                                                                                                                                                {
                                                                                                                                                                                    attributes = toProcess->attributes;
                                                                                                                                                                                    relations = toProcess->relations;
                                                                                                                                                }
                                                                                                                }
                                                                                    }
                                                            }
                                        }
                        }
            }
            if ((!attributes && !relations)) {
                        {
                                        return []() {
                                              js::object obj_temp_12;
                                              return js::any(obj_temp_12);
                                            }();
                        }
            }
            if (this->_itemDataCache.has(id)) {
                        {
                                        return this->_itemDataCache.get(id);
                        }
            }
            const js::any localId = (js::null ? js::null : js::null);
            const js::any category = (js::null ? js::null : js::null);
            const js::any guid = (js::null ? js::null : js::null);
            const ItemData data = []() {
                  js::object obj_temp_13;
                  obj_temp_13.set("_category", []() {
                  js::object obj_temp_14;
                  obj_temp_14.set("value", category);
                  return js::any(obj_temp_14);
                }());
                  obj_temp_13.set("_localId", []() {
                  js::object obj_temp_15;
                  obj_temp_15.set("value", localId);
                  return js::any(obj_temp_15);
                }());
                  obj_temp_13.set("_guid", []() {
                  js::object obj_temp_16;
                  obj_temp_16.set("value", guid);
                  return js::any(obj_temp_16);
                }());
                  return js::any(obj_temp_13);
                }();
            this->_itemDataCache.set(id, data);
            if ((attributes && localId !== js::null)) {
                        {
                                        const js::any itemAttrs = this->getItemAttributes(id);
                                        for (const auto& js::undefined : js::Object::entries((itemAttrs.has_value() ? itemAttrs : []() {
                                              js::object obj_temp_17;
                                              return js::any(obj_temp_17);
                                            }()))) {
                                                            {
                                                                                    if (allAttributes) {
                                                                                                                {
                                                                                                                                                if (!attributesConfig.includes(key)) {
                                                                                                                                                                                    {
                                                                                                                                                                                                                            data->key = value;
                                                                                                                                                                                    }
                                                                                                                                                }
                                                                                                                }
                                                                                    } else {
                                                                                                                if (attributesConfig.includes(key)) {
                                                                                                                                                {
                                                                                                                                                                                    data->key = value;
                                                                                                                                                }
                                                                                                                }
                                                                                    }
                                                            }
                                        }
                        }
            }
            if (relations) {
                        {
                                        const js::any itemRels = this->getItemRelations(id);
                                        for (const auto& js::undefined : js::Object::entries((itemRels.has_value() ? itemRels : []() {
                                              js::object obj_temp_18;
                                              return js::any(obj_temp_18);
                                            }()))) {
                                                            {
                                                                                    for (const auto& localId : localIds) {
                                                                                                                {
                                                                                                                                                const js::any itemData = this->getItemData(localId, []() {
                                                                                                                                                      js::object obj_temp_19;
                                                                                                                                                      obj_temp_19.set("parentName", rel);
                                                                                                                                                      obj_temp_19.set("rel", key);
                                                                                                                                                      return js::any(obj_temp_19);
                                                                                                                                                    }());
                                                                                                                                                if (js::Object::keys(itemData).length === js::number(0)) {
                                                                                                                                                                                    {
                                                                                                                                                                                                                            continue;
                                                                                                                                                                                    }
                                                                                                                                                }
                                                                                                                                                const js::any info = data->key;
                                                                                                                                                if (js::array.isArray(info)) {
                                                                                                                                                                                    {
                                                                                                                                                                                                                            info.push(itemData);
                                                                                                                                                                                    }
                                                                                                                                                } else {
                                                                                                                                                                                    {
                                                                                                                                                                                                                            data->key = js::array<js::any>{itemData};
                                                                                                                                                                                    }
                                                                                                                                                }
                                                                                                                }
                                                                                    }
                                                            }
                                        }
                        }
            }
            return data;
    }
}

auto VirtualPropertiesController::getItemsData(js::array<Identifier> ids, Partial config) {
    {
            this->_itemDataCache.clear();
            js::array<ItemData> result = js::array<js::any>{};
            const js::any _ids = (js::null ? js::null : js::null);
            if (!_ids) {
                        return result;
            }
            this->_itemDataConfig = []() {
                  js::object obj_temp_20;
                  return js::any(obj_temp_20);
                }();
            for (const auto& id : _ids) {
                        {
                                        result.push(this->getItemData(id));
                        }
            }
            this->_itemDataCache.clear();
            this->_itemDataConfig = []() {
                  js::object obj_temp_21;
                  obj_temp_21.set("relationsDefault", []() {
                  js::object obj_temp_22;
                  obj_temp_22.set("attributes", false);
                  obj_temp_22.set("relations", false);
                  return js::any(obj_temp_22);
                }());
                  obj_temp_21.set("attributesDefault", true);
                  return js::any(obj_temp_21);
                }();
            return result;
    }
}

auto VirtualPropertiesController::getItemRelations(Identifier id) {
    {
            const js::any isLocalId = js::typeof_op(id) === "number"_S;
            const js::any localId = (js::null ? js::null : js::null);
            if (localId === js::null) {
                        {
                                        return js::null;
                        }
            }
            const js::any relations = (this->_relations.get(localId).has_value() ? this->_relations.get(localId) : []() {
                  js::object obj_temp_23;
                  return js::any(obj_temp_23);
                }());
            const js::any index = this->_model.relationsItemsArray().indexOf(localId);
            if ((index === js::undefined || index === -js::number(1))) {
                        {
                                        return (js::null ? js::null : js::null);
                        }
            }
            const js::any buffer = this->_model.relations(index);
            if (!buffer) {
                        {
                                        return (js::null ? js::null : js::null);
                        }
            }
            for (js::number j = js::number(0); (j < buffer["dataLength"]()); j++) {
                        {
                                        const js::any attr = buffer["data"](j);
                                        if (!attr) {
                                                            {
                                                                                    continue;
                                                            }
                                        }
                                        auto _temp8565 = js::JSON::parse(attr);
                                        const auto name = _temp8565[0];
                                        const auto localIds = _temp8565.slice(1);
                                        relations[name] = localIds;
                        }
            }
            return relations;
    }
}

auto VirtualPropertiesController::getCategories() {
    {
            const std::shared_ptr<Set> categories = std::make_shared<Set>();
            for (js::number index = js::number(0); (index < this->_model.categoriesLength()); index++) {
                        {
                                        const js::any category = this->_model.categories(index);
                                        if (!category) {
                                                            continue;
                                        }
                                        categories["add"](category);
                        }
            }
            return js::array<js::any>().concat(categories);
    }
}

auto VirtualPropertiesController::getItemsOfCategories(js::array<RegExp> categories) {
    {
            const js::any result = []() {
                  js::object obj_temp_24;
                  return js::any(obj_temp_24);
                }();
            const js::any allLocalIds = this->_model.localIdsArray();
            if (!allLocalIds) {
                        {
                                        return result;
                        }
            }
            for (js::number index = js::number(0); (index < this->_model.categoriesLength()); index++) {
                        {
                                        const js::any currentCategory = this->_model.categories(index);
                                        if (!currentCategory) {
                                                            continue;
                                        }
                                        for (const auto& categoryRegex : categories) {
                                                            {
                                                                                    if (categoryRegex->test(currentCategory)) {
                                                                                                                {
                                                                                                                                                if (!result->currentCategory) {
                                                                                                                                                                                    {
                                                                                                                                                                                                                            result->currentCategory = js::array<js::any>{};
                                                                                                                                                                                    }
                                                                                                                                                }
                                                                                                                                                result->currentCategory.push(allLocalIds->index);
                                                                                                                                                break;
                                                                                                                }
                                                                                    }
                                                            }
                                        }
                        }
            }
            return result;
    }
}

auto VirtualPropertiesController::getItemsWithGeometry() {
    {
            const js::any meshes = this->_model.meshes(std::make_shared<Meshes>());
            js::array<js::number> localIds = js::array<js::any>{};
            if (!meshes) {
                        {
                                        return localIds;
                        }
            }
            const js::any indices = meshes["meshesItemsArray"]();
            if (!indices) {
                        {
                                        return localIds;
                        }
            }
            for (const auto& index : indices) {
                        {
                                        const js::any localId = this->_model.localIds(index);
                                        if (localId === js::null) {
                                                            {
                                                                                    continue;
                                                            }
                                        }
                                        localIds.push(localId);
                        }
            }
            return localIds;
    }
}

auto VirtualPropertiesController::getItemsWithGeometryCategories() {
    {
            const js::any localIds = this->getItemsWithGeometry();
            const js::any categories = this->getItemsCategories(localIds);
            return categories;
    }
}

auto VirtualPropertiesController::getItemsByAttribute(GetItemsByAttributeParams param) {
    {
            const js::any allAttributesLength = this->_model.attributesLength();
            js::array<js::number> res = js::array<js::any>{};
            for (js::number i = js::number(0); (i < allAttributesLength); i++) {
                        {
                                        const js::any localId = this->_model.localIds(i);
                                        if (localId === js::null) {
                                                            continue;
                                        }
                                        if ((itemIds.length() && !itemIds.includes(localId))) {
                                                            continue;
                                        }
                                        const js::any attribute = this->_model.attributes(i);
                                        if (!attribute) {
                                                            continue;
                                        }
                                        const js::any dataLength = attribute["dataLength"]();
                                        bool itemPasses = false;
                                        for (js::number j = js::number(0); (j < dataLength); j++) {
                                                            {
                                                                                    const js::any data = attribute["data"](j);
                                                                                    if (!data) {
                                                                                                                continue;
                                                                                    }
                                                                                    auto _temp8521 = js::JSON::parse(data);
                                                                                    const auto attrName = _temp8521[0];
                                                                                    const auto val = _temp8521[1];
                                                                                    const auto typeValue = _temp8521[2];
                                                                                    if (name["test"](attrName)) {
                                                                                                                {
                                                                                                                                                js::any pass = (value === js::undefined && type === js::undefined);
                                                                                                                                                if (!pass) {
                                                                                                                                                                                    {
                                                                                                                                                                                                                            if (value !== js::undefined) {
                                                                                                                                                                                                                                                                        {
                                                                                                                                                                                                                                                                                                                        if (js::array.isArray(value)) {
                                                                                                                                                                                                                                                                                                                                                                            {
                                                                                                                                                                                                                                                                                                                                                                                                                                    pass = value.some([&](auto regex) -> auto { return (js::typeof_op(val) === "string"_S && regex["test"](val)); });
                                                                                                                                                                                                                                                                                                                                                                            }
                                                                                                                                                                                                                                                                                                                        } else {
                                                                                                                                                                                                                                                                                                                                                                            if (js::instanceof_op(value, "js::RegExp")) {
                                                                                                                                                                                                                                                                                                                                                                                                                                    {
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                pass = (js::typeof_op(val) === "string"_S && value["test"](val));
                                                                                                                                                                                                                                                                                                                                                                                                                                    }
                                                                                                                                                                                                                                                                                                                                                                            } else {
                                                                                                                                                                                                                                                                                                                                                                                                                                    {
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                pass = val === value;
                                                                                                                                                                                                                                                                                                                                                                                                                                    }
                                                                                                                                                                                                                                                                                                                                                                            }
                                                                                                                                                                                                                                                                                                                        }
                                                                                                                                                                                                                                                                        }
                                                                                                                                                                                                                            }
                                                                                                                                                                                                                            if (type !== js::undefined) {
                                                                                                                                                                                                                                                                        {
                                                                                                                                                                                                                                                                                                                        pass = ((pass && js::typeof_op(typeValue) === "string"_S) && type["test"](typeValue));
                                                                                                                                                                                                                                                                        }
                                                                                                                                                                                                                            }
                                                                                                                                                                                    }
                                                                                                                                                }
                                                                                                                                                if (pass) {
                                                                                                                                                                                    {
                                                                                                                                                                                                                            itemPasses = true;
                                                                                                                                                                                                                            break;
                                                                                                                                                                                    }
                                                                                                                                                }
                                                                                                                }
                                                                                    }
                                                            }
                                        }
                                        if ((js::null ? js::null : js::null)) {
                                                            {
                                                                                    res.push(localId);
                                                            }
                                        }
                        }
            }
            return res;
    }
}

auto VirtualPropertiesController::getItemsByRelation(GetItemsByRelationParams param) {
    {
            js::array<js::number> res = js::array<js::any>{};
            const js::any sources = (sourceItemIds.has_value() ? sourceItemIds : this->getAllLocalIds());
            for (const auto& srcId : sources) {
                        {
                                        const js::any rels = this->getItemRelations(srcId);
                                        const js::any linked = rels[name];
                                        if (!linked) {
                                                            continue;
                                        }
                                        if (targetItemIds) {
                                                            {
                                                                                    for (const auto& trgId : linked) {
                                                                                                                {
                                                                                                                                                if (targetItemIds->has(trgId)) {
                                                                                                                                                                                    {
                                                                                                                                                                                                                            res.push(srcId);
                                                                                                                                                                                                                            break;
                                                                                                                                                                                    }
                                                                                                                                                }
                                                                                                                }
                                                                                    }
                                                            }
                                        } else {
                                                            {
                                                                                    res.push(srcId);
                                                            }
                                        }
                        }
            }
            return res;
    }
}

auto VirtualPropertiesController::getItemsByQuery(ItemsQueryParams params) {
    {
            auto _temp6846 = params;
            const auto categories = _temp6846["categories"];
            const auto attributes = _temp6846["attributes"];
            const auto relation = _temp6846["relation"];
            js::any candidateIds = (js::null ? js::null : js::null);
            if (candidateIds.length() === js::number(0)) {
                        return js::array<js::any>{};
            }
            if (attributes) {
                        {
                                        const js::any aggregation = (attributes["aggregation"].has_value() ? attributes["aggregation"] : "exclusive"_S);
                                        js::array<js::array<js::number>> ids = js::array<js::any>{};
                                        for (const auto& attribute : attributes["queries"]) {
                                                            {
                                                                                    if ((attributes && Boolean(attribute["name"]))) {
                                                                                                                {
                                                                                                                                                const js::any localIds = this->getItemsByAttribute([]() {
                                                                                                                                                      js::object obj_temp_25;
                                                                                                                                                      obj_temp_25.set("itemIds", candidateIds);
                                                                                                                                                      return js::any(obj_temp_25);
                                                                                                                                                    }());
                                                                                                                                                ids.push(localIds);
                                                                                                                }
                                                                                    }
                                                            }
                                        }
                                        const std::shared_ptr<Set> set = std::make_shared<Set>();
                                        if (aggregation === "inclusive"_S) {
                                                            {
                                                                                    for (const auto& collection : ids) {
                                                                                                                {
                                                                                                                                                for (const auto& id : collection) {
                                                                                                                                                                                    {
                                                                                                                                                                                                                            set["add"](id);
                                                                                                                                                                                    }
                                                                                                                                                }
                                                                                                                }
                                                                                    }
                                                            }
                                        } else {
                                                            {
                                                                                    const std::shared_ptr<Map> map = std::make_shared<Map>();
                                                                                    for (const auto& collection : ids) {
                                                                                                                {
                                                                                                                                                for (const auto& id : collection) {
                                                                                                                                                                                    {
                                                                                                                                                                                                                            const js::any count = map["get"](id);
                                                                                                                                                                                                                            if (count === js::undefined) {
                                                                                                                                                                                                                                                                        {
                                                                                                                                                                                                                                                                                                                        map["set"](id, js::number(1));
                                                                                                                                                                                                                                                                        }
                                                                                                                                                                                                                            } else {
                                                                                                                                                                                                                                                                        {
                                                                                                                                                                                                                                                                                                                        map["set"](id, (count + js::number(1)));
                                                                                                                                                                                                                                                                        }
                                                                                                                                                                                                                            }
                                                                                                                                                                                    }
                                                                                                                                                }
                                                                                                                }
                                                                                    }
                                                                                    for (const auto& js::undefined : map) {
                                                                                                                {
                                                                                                                                                if (count === ids.length()) {
                                                                                                                                                                                    {
                                                                                                                                                                                                                            set["add"](id);
                                                                                                                                                                                    }
                                                                                                                                                }
                                                                                                                }
                                                                                    }
                                                            }
                                        }
                                        candidateIds = js::array<js::any>().concat(set);
                        }
            }
            if (candidateIds.length() === js::number(0)) {
                        return js::array<js::any>{};
            }
            if ((relation && Boolean(relation["name"]))) {
                        {
                                        auto _temp706 = relation;
                                        const auto name = _temp706["name"];
                                        const auto query = _temp706["query"];
                                        const js::any targetIds = (js::null ? js::null : js::null);
                                        candidateIds = this->getItemsByRelation([]() {
                                              js::object obj_temp_26;
                                              obj_temp_26.set("name", name);
                                              obj_temp_26.set("targetItemIds", targetIds);
                                              obj_temp_26.set("sourceItemIds", candidateIds);
                                              return js::any(obj_temp_26);
                                            }());
                        }
            }
            return js::array.from(std::make_shared<Set>(candidateIds));
    }
}

auto VirtualPropertiesController::getTreeItem(SpatialStructure item) {
    {
            const SpatialTreeItem tree = []() {
                  js::object obj_temp_27;
                  obj_temp_27.set("category", item->category());
                  obj_temp_27.set("localId", item->localId());
                  return js::any(obj_temp_27);
                }();
            js::array<SpatialTreeItem> children = js::array<js::any>{};
            for (js::number i = js::number(0); (i < item->childrenLength()); i++) {
                        {
                                        const js::any child = item->children(i);
                                        if (!child) {
                                                            {
                                                                                    continue;
                                                            }
                                        }
                                        children.push(this->getTreeItem(child));
                        }
            }
            if ((children.length() > js::number(0))) {
                        {
                                        tree["children"] = children;
                        }
            }
            return tree;
    }
}

auto VirtualPropertiesController::preindexGeometryIds() {
    {
            const js::any geometries = this->_model.meshes();
            const js::any length = geometries["meshesItemsLength"]();
            for (js::number i = js::number(0); (i < length); i++) {
                        {
                                        const js::any localIdIndex = geometries["meshesItems"](i);
                                        const js::any localId = this->_model.localIds(localIdIndex);
                                        if (localId === js::null) {
                                                            continue;
                                        }
                                        if (!this->_localIdsToGeometryIds.has(localId)) {
                                                            {
                                                                                    this->_localIdsToGeometryIds.set(localId, js::array<js::any>{});
                                                            }
                                        }
                                        this->_localIdsToGeometryIds.get(localId).push(i);
                        }
            }
    }
}

auto VirtualPropertiesController::convertToLocalId(Identifier id) {
    {
            const js::any isLocalId = js::typeof_op(id) === "number"_S;
            if (isLocalId) {
                        return id;
            }
            const js::any localId = this->_guidToLocalIdMap.get(id);
            if (localId === js::undefined) {
                        return js::null;
            }
            return localId;
    }
}

auto VirtualPropertiesController::getChildrenLocalIds(SpatialTreeItem treeItem, Set collector) {
    {
            if (treeItem->localId !== js::null) {
                        {
                                        collector["add"](treeItem->localId);
                        }
            }
            if (treeItem->children) {
                        {
                                        for (const auto& child : treeItem->children) {
                                                            {
                                                                                    this->getChildrenLocalIds(child, collector);
                                                            }
                                        }
                        }
            }
    }
}

auto VirtualPropertiesController::traverseSpatialStructure(js::number localId, Set collector, auto treeItem) {
    {
            if (!treeItem) {
                        return;
            }
            if ((treeItem->localId === localId && treeItem->children)) {
                        {
                                        for (const auto& child : treeItem->children) {
                                                            {
                                                                                    this->getChildrenLocalIds(child, collector);
                                                            }
                                        }
                                        return;
                        }
            }
            if (treeItem->children) {
                        {
                                        for (const auto& child : treeItem->children) {
                                                            {
                                                                                    this->traverseSpatialStructure(localId, collector, child);
                                                            }
                                        }
                        }
            }
    }
}
