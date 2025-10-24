#include "index_generated.h"
#include "property-processor.h"

using namespace js;

auto IfcPropertyProcessor::getIfcApi() {
    {
            if (!this->_ifcApi) {
                        {
                                        const std::shared_ptr<web-ifc::IfcAPI> ifcApi = std::make_shared<web-ifc::IfcAPI>();
                                        ifcApi->SetWasmPath(this->wasm.path, this->wasm.absolute);
                                        co_await ifcApi->Init();
                                        ifcApi->SetLogLevel(web-ifc::LogLevel.LOG_LEVEL_OFF);
                                        this->_ifcApi = ifcApi;
                        }
            }
            return this->_ifcApi;
    }
}

auto IfcPropertyProcessor::getSchema(auto modelId) {
    {
            const js::any ifcApi = co_await this->getIfcApi();
            const js::any schema = ifcApi->GetModelSchema(modelId);
            if (!schema) {
                        {
                                        throw js::any(js::Error("Fragments: IFC Schema not found"_S));
                        }
            }
            if (schema["startsWith"]("IFC2X3"_S)) {
                        {
                                        return "IFC2X3"_S;
                        }
            }
            if ((schema["startsWith"]("IFC4"_S) && schema.replace("IFC4"_S, ""_S) === ""_S)) {
                        {
                                        return "IFC4"_S;
                        }
            }
            if (schema["startsWith"]("IFC4X"_S)) {
                        {
                                        return "IFC4X3"_S;
                        }
            }
            return schema;
    }
}

IfcPropertyProcessor::IfcPropertyProcessor(IfcImporter _serializer, Builder _builder) {
    {
    }
}

auto IfcPropertyProcessor::process(PropertiesProcessData data) {
    {
            const js::any ifcApi = co_await this->getIfcApi();
            if (data->readFromCallback) {
                        {
                                        ifcApi->OpenModelFromCallback(data->readCallback, this->webIfcSettings);
                        }
            } else {
                        if (data->bytes) {
                                        {
                                                            co_await ifcApi->OpenModel(data->bytes, this->webIfcSettings);
                                        }
                        } else {
                                        {
                                                            throw js::any(js::Error("Fragments: No data provided"_S));
                                        }
                        }
            }
            if (this->_serializer.replaceStoreyElevation) {
                        {
                                        co_await this->setLengthUnitsFactor();
                        }
            }
            const js::any modelClasses = ifcApi->GetAllTypesOfModel(js::number(0)).map([&](auto entry) -> auto { return entry["typeID"]; });
            const js::any schema = co_await this->getSchema();
            const js::any schemaNamespace = WEBIFC::getName(schema);
            if (!schemaNamespace) {
                        {
                                        throw js::any(js::Error("Fragments: Model schema not recognized."_S));
                        }
            }
            const js::any itemsWithGeom = data->geometryProcessedLocalIDs;
            co_await this->processItems(itemsWithGeom);
            const std::shared_ptr<Set> visitedItems = std::make_shared<Set>(itemsWithGeom);
            data->progressCallback(js::number(0.6), []() {
                  js::object obj_temp_0;
                  obj_temp_0.set("process", "attributes"_S);
                  obj_temp_0.set("state", "start"_S);
                  obj_temp_0.set("entitiesProcessed", itemsWithGeom.length());
                  return js::any(obj_temp_0);
                }());
            const std::shared_ptr<Set> classes = std::make_shared<Set>(js::array<js::any>().concat(this->_serializer.classes.abstract).concat(this->_serializer.classes.elements));
            const js::any toProcess = modelClasses.filter([&](auto type) -> auto { return classes["has"](type); });
            const js::number categoryPercentage = (js::number(0.15) / toProcess.length());
            for (const auto& js::undefined : toProcess->entries()) {
                        {
                                        const js::any classEntities = ifcApi->GetLineIDsWithType(js::number(0), entityClass);
                                        if (classEntities->size() === js::number(0)) {
                                                            continue;
                                        }
                                        js::array<js::number> items = js::array<js::any>{};
                                        for (js::number index = js::number(0); (index < classEntities->size()); index++) {
                                                            {
                                                                                    const js::any id = classEntities->get(index);
                                                                                    if (visitedItems->has(id)) {
                                                                                                                continue;
                                                                                    }
                                                                                    items.push(id);
                                                            }
                                        }
                                        if (items.length() === js::number(0)) {
                                                            continue;
                                        }
                                        co_await this->processItems(items);
                                        data->progressCallback(((categoryPercentage * (index + js::number(1))) + js::number(0.6)), []() {
                                              js::object obj_temp_1;
                                              obj_temp_1.set("process", "attributes"_S);
                                              obj_temp_1.set("state", (js::null ? js::null : js::null));
                                              obj_temp_1.set("class", ifcCategoryMap->entityClass);
                                              obj_temp_1.set("entitiesProcessed", items.length());
                                              return js::any(obj_temp_1);
                                            }());
                        }
            }
            const std::shared_ptr<Set> relations = std::make_shared<Set>(js::array<js::any>().concat(this->_serializer.relations.keys()));
            const js::any relsToProcess = modelClasses.filter([&](auto type) -> auto { return relations["has"](type); });
            const js::number relsPercentage = (js::number(0.15) / relsToProcess.length());
            for (const auto& js::undefined : relsToProcess->entries()) {
                        {
                                        const js::any state = [&]() -> auto {
                                        if (index === js::number(0)) {
                                                            return "start"_S;
                                        }
                                        if ((index + js::number(1)) === relsToProcess.length()) {
                                                            return "finish"_S;
                                        }
                                        return "inProgress"_S;
                                        }();
                                        co_await this->processRelations(js::array<js::any>{rel});
                                        data->progressCallback(((relsPercentage * (index + js::number(1))) + js::number(0.75)), []() {
                                              js::object obj_temp_2;
                                              obj_temp_2.set("process", "relations"_S);
                                              obj_temp_2.set("state", state);
                                              obj_temp_2.set("class", ifcCategoryMap->rel);
                                              return js::any(obj_temp_2);
                                            }());
                        }
            }
            auto _temp9405 = this->getRelationsVector();
            const auto relIndicesVector = _temp9405["relIndicesVector"];
            const auto relsVector = _temp9405["relsVector"];
            auto _temp1865 = this->getGuidsVector();
            const auto guidsVector = _temp1865["guidsVector"];
            const auto guidsItemsVector = _temp1865["guidsItemsVector"];
            const js::any metadataOffset = co_await this->getMetadataOffset();
            const js::any attributesVector = this->getAttributesVector();
            const js::any uniqueAttributesVector = this->getUniqueAttributesVector();
            const js::any relNamesVector = this->getRelNamesVector();
            const js::any localIdsVector = ../../../../Schema::Model.createLocalIdsVector(this->_builder, this->expressIDs);
            const js::any categoriesVector = this->getCategoriesVector();
            const js::any spatialStrutureOffset = co_await this->getSpatialStructureOffset();
            this->clean();
            return []() {
                  js::object obj_temp_3;
                  obj_temp_3.set("relIndicesVector", relIndicesVector);
                  obj_temp_3.set("relsVector", relsVector);
                  obj_temp_3.set("guidsVector", guidsVector);
                  obj_temp_3.set("guidsItemsVector", guidsItemsVector);
                  obj_temp_3.set("metadataOffset", metadataOffset);
                  obj_temp_3.set("attributesVector", attributesVector);
                  obj_temp_3.set("localIdsVector", localIdsVector);
                  obj_temp_3.set("categoriesVector", categoriesVector);
                  obj_temp_3.set("spatialStrutureOffset", spatialStrutureOffset);
                  obj_temp_3.set("uniqueAttributesVector", uniqueAttributesVector);
                  obj_temp_3.set("relNamesVector", relNamesVector);
                  return js::any(obj_temp_3);
                }();
    }
}

auto IfcPropertyProcessor::processItems(js::array<js::number> items) {
    {
            const js::any ifcApi = co_await this->getIfcApi();
            for (js::number index = js::number(0); (index < items.length()); index++) {
                        {
                                        const js::any expressID = items[index];
                                        try {
                                                            const js::any attrs = co_await ifcApi->properties->getItemProperties(js::number(0), expressID);
                                                            if (!attrs) {
                                                                                    continue;
                                                            }
                                                            const js::any className = ifcCategoryMap->attrs["type"];
                                                            this->classes.push(className);
                                                            this->expressIDs.push(expressID);
                                                            co_await this->serializeAttributes(expressID, attrs);
                                        } catch (const js::any& e) {
                                                            js::console.log(("Problem reading properties for "_S + js::toString(expressID)));
                                                            js::console.log(e);
                                                            co_await std::make_shared<Promise>([&](auto resolve) -> auto {
                                                            setTimeout(resolve, js::number(100));
                                                            });
                                                            continue;
                                        }
                        }
            }
    }
}

auto IfcPropertyProcessor::addRelation(js::number expressID, js::string relName, js::array<js::number> ids) {
    {
            if (!this->_relationsMap[expressID]) {
                        this->_relationsMap[expressID] = []() {
                              js::object obj_temp_4;
                              return js::any(obj_temp_4);
                            }();
            }
            if (!this->_relationsMap[expressID][relName]) {
                        this->_relationsMap[expressID][relName] = js::array<js::any>{};
            }
            for (const auto& id : ids) {
                        {
                                        this->_relationsMap[expressID][relName].push(id);
                        }
            }
            if (this->_serializer.includeRelationNames) {
                        {
                                        this->_uniqueRelNames.add(relName);
                        }
            }
    }
}

auto IfcPropertyProcessor::getStoreyElevation(js::number placement, js::any height) {
    {
            const js::any ifcApi = co_await this->getIfcApi();
            const js::any localPlacementAttrs = co_await ifcApi->properties->getItemProperties(js::number(0), placement);
            js::typed::Nullable<RawEntityAttrs> relPlacementAttrs;
            if (((localPlacementAttrs->RelativePlacement && js::in_op("value"_S, localPlacementAttrs->RelativePlacement)) && js::typeof_op(localPlacementAttrs->RelativePlacement->value) === "number"_S)) {
                        {
                                        relPlacementAttrs = co_await ifcApi->properties->getItemProperties(js::number(0), localPlacementAttrs->RelativePlacement->value);
                        }
            }
            js::typed::Nullable<RawEntityAttrs> locationAttrs;
            if (((relPlacementAttrs->Location && js::in_op("value"_S, relPlacementAttrs->Location)) && js::typeof_op(relPlacementAttrs->Location->value) === "number"_S)) {
                        {
                                        locationAttrs = co_await ifcApi->properties->getItemProperties(js::number(0), relPlacementAttrs->Location->value);
                        }
            }
            if ((((locationAttrs->Coordinates && js::array.isArray(locationAttrs->Coordinates)) && js::in_op("value"_S, locationAttrs->Coordinates->js::number(2))) && js::typeof_op(locationAttrs->Coordinates->js::number(2)->value) === "number"_S)) {
                        {
                                        height["value"] += locationAttrs->Coordinates->js::number(2)->value;
                        }
            }
            if (((localPlacementAttrs->PlacementRelTo && js::in_op("value"_S, localPlacementAttrs->PlacementRelTo)) && js::typeof_op(localPlacementAttrs->PlacementRelTo->value) === "number"_S)) {
                        {
                                        co_await this->getStoreyElevation(localPlacementAttrs->PlacementRelTo->value, height);
                        }
            }
    }
}

auto IfcPropertyProcessor::setLengthUnitsFactor() {
    {
            const js::any ifcApi = co_await this->getIfcApi();
            const js::any unitAssignmentIds = ifcApi->GetLineIDsWithType(js::number(0), web-ifc::IFCUNITASSIGNMENT);
            if (unitAssignmentIds->size() === js::number(0)) {
                        return;
            }
            for (js::number i = js::number(0); (i < unitAssignmentIds->size()); i++) {
                        {
                                        const js::any assignmentId = unitAssignmentIds->get(i);
                                        const js::any assignmentAttrs = co_await ifcApi->properties->getItemProperties(js::number(0), assignmentId);
                                        for (const auto& unitHandle : assignmentAttrs->Units) {
                                                            {
                                                                                    const js::any unit = co_await ifcApi->properties->getItemProperties(js::number(0), unitHandle->value);
                                                                                    const js::any value = unit["UnitType"]["value"];
                                                                                    if (value !== "LENGTHUNIT"_S) {
                                                                                                                continue;
                                                                                    }
                                                                                    js::number factor = js::number(1);
                                                                                    js::number unitValue = js::number(1);
                                                                                    if (unit["Name"]["value"] === "METRE"_S) {
                                                                                                                unitValue = js::number(1);
                                                                                    }
                                                                                    if (unit["Name"]["value"] === "FOOT"_S) {
                                                                                                                unitValue = js::number(0.3048);
                                                                                    }
                                                                                    if (unit["Prefix"]["value"] === "MILLI"_S) {
                                                                                                                {
                                                                                                                                                factor = js::number(0.001);
                                                                                                                }
                                                                                    } else {
                                                                                                                if (unit["Prefix"]["value"] === "CENTI"_S) {
                                                                                                                                                {
                                                                                                                                                                                    factor = js::number(0.01);
                                                                                                                                                }
                                                                                                                } else {
                                                                                                                                                if (unit["Prefix"]["value"] === "DECI"_S) {
                                                                                                                                                                                    {
                                                                                                                                                                                                                            factor = js::number(0.1);
                                                                                                                                                                                    }
                                                                                                                                                }
                                                                                                                }
                                                                                    }
                                                                                    this->_lengthUnitsFactor = (unitValue * factor);
                                                            }
                                        }
                        }
            }
    }
}

auto IfcPropertyProcessor::serializeAttributes(js::number expressID, RawEntityAttrs attrs) {
    {
            js::array<js::number> attrOffsets = js::array<js::any>{};
            js::typed::Nullable<js::string> guid = js::null;
            if ((((((this->_serializer.replaceStoreyElevation && attrs["type"]) && js::typeof_op(attrs["type"]) === "number"_S) && attrs["type"] === web-ifc::IFCBUILDINGSTOREY) && attrs["Elevation"]) && js::in_op("value"_S, attrs["Elevation"]))) {
                        {
                                        const js::any height = []() {
                                              js::object obj_temp_5;
                                              obj_temp_5.set("value", js::number(0));
                                              return js::any(obj_temp_5);
                                            }();
                                        if (((attrs["ObjectPlacement"] && js::in_op("value"_S, attrs["ObjectPlacement"])) && js::typeof_op(attrs["ObjectPlacement"]["value"]) === "number"_S)) {
                                                            {
                                                                                    co_await this->getStoreyElevation(attrs["ObjectPlacement"]["value"], height);
                                                            }
                                        }
                                        attrs["Elevation"]["value"] = (height["value"] * this->_lengthUnitsFactor);
                        }
            }
            js::number index = js::number(0);
            for (const auto& js::undefined : js::Object::entries(attrs)) {
                        {
                                        if (js::typeof_op(attrValue) === "number"_S) {
                                                            continue;
                                        }
                                        if (((this->_serializer.attributesToExclude.has(attrName) || attrValue === js::null) || attrValue === js::undefined)) {
                                                            {
                                                                                    index++;
                                                                                    continue;
                                                            }
                                        }
                                        if (js::array.isArray(attrValue)) {
                                                            {
                                                                                    const js::any noHandles = attrValue.filter([&](auto handle) -> auto { return handle["type"] !== js::number(5); });
                                                                                    if ((noHandles.length() > js::number(0))) {
                                                                                                                {
                                                                                                                                                const js::any noHandlesValue = noHandles.map([&](auto handle) -> auto { return handle["value"]; });
                                                                                                                                                js::array<js::any> attrData = js::array<js::any>{attrName, noHandlesValue};
                                                                                                                                                const js::any dataTypeName = (js::null ? js::null : js::null);
                                                                                                                                                attrData.push((js::null ? js::null : js::null));
                                                                                                                                                const js::any hash = js::JSON::stringify(attrData);
                                                                                                                                                const js::any attrOffset = this->_builder.createSharedString(hash);
                                                                                                                                                attrOffsets.push(attrOffset);
                                                                                                                }
                                                                                    }
                                                                                    const js::any handles = attrValue.filter([&](auto handle) -> auto { return handle["type"] === js::number(5); });
                                                                                    const js::any ids = handles.map([&](auto handle) -> auto { return handle["value"]; });
                                                                                    this->addRelation(expressID, attrName, ids);
                                                                                    index++;
                                                                                    continue;
                                                            }
                                        }
                                        auto _temp8262 = attrValue;
                                        const auto value = _temp8262["value"];
                                        const auto type = _temp8262["type"];
                                        if (type === js::number(5)) {
                                                            {
                                                                                    if (js::typeof_op(value) !== "number"_S) {
                                                                                                                continue;
                                                                                    }
                                                                                    this->addRelation(expressID, attrName, js::array<js::any>{value});
                                                            }
                                        } else {
                                                            {
                                                                                    if ((attrName === "GlobalId"_S && js::typeof_op(value) === "string"_S)) {
                                                                                                                {
                                                                                                                                                guid = value;
                                                                                                                                                index++;
                                                                                                                                                continue;
                                                                                                                }
                                                                                    }
                                                                                    js::array<js::any> attrData = js::array<js::any>{attrName, value};
                                                                                    const js::any dataTypeName = (js::null ? js::null : js::null);
                                                                                    attrData.push((js::null ? js::null : js::null));
                                                                                    const js::any hash = js::JSON::stringify(attrData);
                                                                                    const js::any attrOffset = this->_builder.createSharedString(hash);
                                                                                    attrOffsets.push(attrOffset);
                                                                                    if (this->_serializer.includeUniqueAttributes) {
                                                                                                                {
                                                                                                                                                this->_uniqueAttributes.add(hash);
                                                                                                                }
                                                                                    }
                                                            }
                                        }
                                        index++;
                        }
            }
            const js::any dataVector = ../../../../Schema::Attribute.createDataVector(this->_builder, attrOffsets);
            const js::any attributeOffset = ../../../../Schema::Attribute.createAttribute(this->_builder, dataVector);
            this->_attributesOffsets.push(attributeOffset);
            if (guid) {
                        {
                                        this->_guids.push(guid);
                                        this->_guidsItems.push(expressID);
                        }
            }
    }
}

auto IfcPropertyProcessor::getAttributesVector() {
    {
            const js::any attributesVector = ../../../../Schema::Model.createAttributesVector(this->_builder, this->_attributesOffsets);
            return attributesVector;
    }
}

auto IfcPropertyProcessor::getUniqueAttributesVector() {
    {
            js::array<js::number> offsets = js::array<js::any>{};
            for (const auto& hash : this->_uniqueAttributes) {
                        {
                                        const js::any offset = this->_builder.createSharedString(hash);
                                        offsets.push(offset);
                        }
            }
            const js::any uniqueAttributesVector = ../../../../Schema::Model.createUniqueAttributesVector(this->_builder, offsets);
            return uniqueAttributesVector;
    }
}

auto IfcPropertyProcessor::getRelNamesVector() {
    {
            js::array<js::number> offsets = js::array<js::any>{};
            for (const auto& name : this->_uniqueRelNames) {
                        {
                                        const js::any offset = this->_builder.createSharedString(name);
                                        offsets.push(offset);
                        }
            }
            const js::any relationNamesVector = ../../../../Schema::Model.createRelationNamesVector(this->_builder, offsets);
            return relationNamesVector;
    }
}

auto IfcPropertyProcessor::getGuidsVector() {
    {
            js::array<js::number> guidOffsets = js::array<js::any>{};
            for (const auto& guid : this->_guids) {
                        {
                                        const js::any offset = this->_builder.createString(guid);
                                        guidOffsets.push(offset);
                        }
            }
            const js::any guidsVector = ../../../../Schema::Model.createGuidsVector(this->_builder, guidOffsets);
            const js::any guidsItemsVector = ../../../../Schema::Model.createGuidsItemsVector(this->_builder, this->_guidsItems);
            return []() {
                  js::object obj_temp_6;
                  obj_temp_6.set("guidsVector", guidsVector);
                  obj_temp_6.set("guidsItemsVector", guidsItemsVector);
                  return js::any(obj_temp_6);
                }();
    }
}

auto IfcPropertyProcessor::processRelations(js::array<js::number> rels) {
    {
            const js::any ifcApi = co_await this->getIfcApi();
            for (const auto& entityClass : rels) {
                        {
                                        const js::any relNames = this->_serializer.relations.get(entityClass);
                                        if (!relNames) {
                                                            continue;
                                        }
                                        auto _temp6279 = relNames;
                                        const auto forRelating = _temp6279["forRelating"];
                                        const auto forRelated = _temp6279["forRelated"];
                                        const js::any classEntities = ifcApi->GetLineIDsWithType(js::number(0), entityClass);
                                        if (classEntities->size() === js::number(0)) {
                                                            continue;
                                        }
                                        for (js::number index = js::number(0); (index < classEntities->size()); index++) {
                                                            {
                                                                                    const js::any expressID = classEntities->get(index);
                                                                                    const js::any attrs = co_await ifcApi->properties->getItemProperties(js::number(0), expressID);
                                                                                    if (!attrs) {
                                                                                                                continue;
                                                                                    }
                                                                                    const js::any attrKeys = js::Object::keys(attrs);
                                                                                    const js::any relatingKey = attrKeys.find([&](auto attr) -> auto { return attr["startsWith"]("Relating"_S); });
                                                                                    const js::any relatedKey = attrKeys.find([&](auto attr) -> auto { return attr["startsWith"]("Related"_S); });
                                                                                    if (!(relatingKey && relatedKey)) {
                                                                                                                continue;
                                                                                    }
                                                                                    const js::any relatingID = attrs[relatingKey]["value"];
                                                                                    const js::any relatedIDs = attrs[relatedKey].map([&](js::any param) -> auto { return value; });
                                                                                    this->addRelation(relatingID, forRelating, relatedIDs);
                                                                                    for (const auto& relatedID : relatedIDs) {
                                                                                                                {
                                                                                                                                                this->addRelation(relatedID, forRelated, js::array<js::any>{relatingID});
                                                                                                                }
                                                                                    }
                                                            }
                                        }
                        }
            }
    }
}

auto IfcPropertyProcessor::getRelationsVector(auto clean) {
    {
            js::array<js::number> rels = js::array<js::any>{};
            js::array<js::number> ids = js::array<js::any>{};
            for (const auto& js::undefined : js::Object::entries(this->_relationsMap)) {
                        {
                                        if ((clean && !this->expressIDs.includes(Number(expressID)))) {
                                                            continue;
                                        }
                                        js::array<js::number> definitions = js::array<js::any>{};
                                        for (const auto& js::undefined : js::Object::entries(entityRels)) {
                                                            {
                                                                                    js::any rels = _rels;
                                                                                    if (clean) {
                                                                                                                {
                                                                                                                                                rels = _rels::filter([&](auto id) -> auto { return this->expressIDs.includes(id); });
                                                                                                                                                if (rels.length() === js::number(0)) {
                                                                                                                                                                                    continue;
                                                                                                                                                }
                                                                                                                }
                                                                                    }
                                                                                    const js::any hash = js::JSON::stringify(js::array<js::any>().concat(js::array<js::any>{attrName}).concat(rels));
                                                                                    const js::any offset = this->_builder.createSharedString(hash);
                                                                                    definitions.push(offset);
                                                            }
                                        }
                                        if ((clean && definitions.length() === js::number(0))) {
                                                            continue;
                                        }
                                        ids.push(Number(expressID));
                                        const js::any dataVector = ../../../../Schema::Relation.createDataVector(this->_builder, definitions);
                                        const js::any relOffset = ../../../../Schema::Relation.createRelation(this->_builder, dataVector);
                                        rels.push(relOffset);
                        }
            }
            const js::any relsVector = ../../../../Schema::Model.createRelationsVector(this->_builder, rels);
            const js::any relIndicesVector = ../../../../Schema::Model.createRelationsItemsVector(this->_builder, ids);
            return []() {
                  js::object obj_temp_7;
                  obj_temp_7.set("relIndicesVector", relIndicesVector);
                  obj_temp_7.set("relsVector", relsVector);
                  return js::any(obj_temp_7);
                }();
    }
}

auto IfcPropertyProcessor::getCategoriesVector() {
    {
            const js::any classesOffset = this->classes.map([&](auto name) -> auto { return this->_builder.createSharedString(name); });
            const js::any categoriesVector = ../../../../Schema::Model.createCategoriesVector(this->_builder, classesOffset);
            return categoriesVector;
    }
}

auto IfcPropertyProcessor::getMetadataOffset() {
    {
            const js::any ifcApi = co_await this->getIfcApi();
            const js::any schema = ifcApi->GetModelSchema(js::number(0));
            const js::any metadata = []() {
                  js::object obj_temp_8;
                  obj_temp_8.set("schema", schema);
                  return js::any(obj_temp_8);
                }();
            const js::any metadataOffset = this->_builder.createString(js::JSON::stringify(metadata));
            return metadataOffset;
    }
}

auto IfcPropertyProcessor::getEntityDecomposition(js::number expressID, js::array<js::string> inverseAttributes) {
        {
                js::array<js::number> offsets = js::array<js::any>{};
                    for (const auto& attrName : inverseAttributes) {
                                    {
                                                    const js::any relations = this->_relationsMap[expressID][attrName];
                                                    if (!relations) {
                                                                        continue;
                                                    }
                                                    const js::any entityGroups = []() {
                                                          js::object obj_temp_9;
                                                          return js::any(obj_temp_9);
                                                        }();
                                                    for (const auto& expressID : relations) {
                                                                        {
                                                                                                const js::any entityIndex = this->expressIDs.indexOf(expressID);
                                                                                                if (entityIndex === -js::number(1)) {
                                                                                                                            continue;
                                                                                                }
                                                                                                const js::any entityClass = this->classes[entityIndex];
                                                                                                if (!entityClass) {
                                                                                                                            continue;
                                                                                                }
                                                                                                if (!entityGroups->entityClass) {
                                                                                                                            entityGroups->entityClass = js::array<js::any>{};
                                                                                                }
                                                                                                entityGroups->entityClass.push(expressID);
                                                                        }
                                                    }
                                                        for (auto& category_pair : js::Object::entries(entityGroups)) {
                                                                            auto category = category_pair.first;
                                                                                {
                                                                                                            const js::any entities = entityGroups->category;
                                                                                                            const js::any childrenOffsets = entities.map([&](auto id) -> auto { return this->getEntityDecomposition(id, inverseAttributes); });
                                                                                                            const js::any childrenVector = ../../../../Schema::SpatialStructure.createChildrenVector(this->_builder, childrenOffsets);
                                                                                                            const js::any categoryOffset = this->_builder.createSharedString(category);
                                                                                                            ../../../../Schema::SpatialStructure.startSpatialStructure(this->_builder);
                                                                                                            ../../../../Schema::SpatialStructure.addCategory(this->_builder, categoryOffset);
                                                                                                            ../../../../Schema::SpatialStructure.addChildren(this->_builder, childrenVector);
                                                                                                            const js::any offset = ../../../../Schema::SpatialStructure.endSpatialStructure(this->_builder);
                                                                                                            offsets.push(offset);
                                                                                }
                                                        }
                                    }
                    }
                    const js::any childrenVector = ../../../../Schema::SpatialStructure.createChildrenVector(this->_builder, offsets);
                    ../../../../Schema::SpatialStructure.startSpatialStructure(this->_builder);
                    ../../../../Schema::SpatialStructure.addLocalId(this->_builder, expressID);
                    ../../../../Schema::SpatialStructure.addChildren(this->_builder, childrenVector);
                    const js::any offset = ../../../../Schema::SpatialStructure.endSpatialStructure(this->_builder);
                    return offset;
        }
}

auto IfcPropertyProcessor::getSpatialStructureOffset() {
        {
                    const js::any ifcApi = co_await this->getIfcApi();
                    const js::any ifcClass = web-ifc::IFCPROJECT;
                    js::array<js::any> classEntities = js::array<js::any>().concat(ifcApi->GetLineIDsWithType(js::number(0), ifcClass));
                    const js::any childrenOffsets = classEntities.map([&](auto id) -> auto { return this->getEntityDecomposition(id, js::array<js::string>{"IsDecomposedBy"_S, "ContainsElements"_S}); });
                    const js::any categoryOffset = this->_builder.createSharedString("IFCPROJECT"_S);
                    const js::any childrenVector = ../../../../Schema::SpatialStructure.createChildrenVector(this->_builder, childrenOffsets);
                    ../../../../Schema::SpatialStructure.startSpatialStructure(this->_builder);
                    ../../../../Schema::SpatialStructure.addCategory(this->_builder, categoryOffset);
                    ../../../../Schema::SpatialStructure.addChildren(this->_builder, childrenVector);
                    const js::any offset = ../../../../Schema::SpatialStructure.endSpatialStructure(this->_builder);
                    return offset;
        }
}

auto IfcPropertyProcessor::clean() {
        {
                    this->_ifcApi.Dispose();
                    this->_ifcApi = js::null;
                    this->_guids = js::array<js::any>{};
                    this->_guidsItems = js::array<js::any>{};
                    this->_attributesOffsets = js::array<js::any>{};
                    this->_relationsMap = []() {
                          js::object obj_temp_10;
                          return js::any(obj_temp_10);
                        }();
                    this->_uniqueAttributes.clear();
                    this->_uniqueRelNames.clear();
                    this->expressIDs = js::array<js::any>{};
                    this->classes = js::array<js::any>{};
        }
}
