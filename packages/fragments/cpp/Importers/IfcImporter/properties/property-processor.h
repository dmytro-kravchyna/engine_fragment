#ifndef PROPERTY_PROCESSOR_H
#define PROPERTY_PROCESSOR_H

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
#include <web-ifc.h>
#include <flatbuffers.h>
#include "../../../../Schema.h"
#include "./types.h"
#include "../...h"
#include "../../../../Utils.h"
#include "../types.h"

using namespace js;

// Forward declarations
class IfcPropertyProcessor;

// Interface PropertiesProcessData
class IPropertiesProcessData {
public:
    virtual ~IPropertiesProcessData() = default;
    // TODO: Interface members
};
class IfcPropertyProcessor {
public:
    auto wasm;
    js::any webIfcSettings;
    js::array<js::number> expressIDs;
    js::array<js::string> classes;
    virtual auto getIfcApi();
    IfcPropertyProcessor(IfcImporter _serializer, Builder _builder);
    virtual auto process(PropertiesProcessData data);
    virtual auto setLengthUnitsFactor();
    virtual auto serializeAttributes(js::number expressID, RawEntityAttrs attrs);
    virtual auto getAttributesVector();
    virtual auto getUniqueAttributesVector();
    virtual auto getRelNamesVector();
    virtual auto getGuidsVector();
    virtual auto processRelations(js::array<js::number> rels);
    virtual auto getRelationsVector(auto clean = false);
    virtual auto getCategoriesVector();
    virtual auto getMetadataOffset();
    virtual auto getSpatialStructureOffset();
    virtual auto clean();
private:
    auto _lengthUnitsFactor;
    js::array<js::number> _attributesOffsets;
    std::shared_ptr<Record> _relationsMap;
    js::array<js::string> _guids;
    js::array<js::number> _guidsItems;
    auto _uniqueAttributes;
    auto _uniqueRelNames;
    js::typed::Nullable<unknown> _ifcApi;
    virtual auto getSchema(auto modelId = js::number(0));
    virtual auto processItems(js::array<js::number> items);
    virtual auto addRelation(js::number expressID, js::string relName, js::array<js::number> ids);
    virtual auto getStoreyElevation(js::number placement, js::any height);
    virtual auto getEntityDecomposition(js::number expressID, js::array<js::string> inverseAttributes);
};

#endif // PROPERTY_PROCESSOR_H