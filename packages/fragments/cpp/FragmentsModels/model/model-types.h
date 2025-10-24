#ifndef MODEL_TYPES_H
#define MODEL_TYPES_H

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
#include "../lod.h"
#include "../../../Schema.h"
#include "./fragments-model.h"

using namespace js;

// Interface AttrsDeleteChange
class IAttrsDeleteChange {
public:
    virtual ~IAttrsDeleteChange() = default;
    // TODO: Interface members
};
// Interface AttrsAddChange
class IAttrsAddChange {
public:
    virtual ~IAttrsAddChange() = default;
    // TODO: Interface members
};
// Interface AttrsModifyChange
class IAttrsModifyChange {
public:
    virtual ~IAttrsModifyChange() = default;
    // TODO: Interface members
};
// Interface RelsModifyChange
class IRelsModifyChange {
public:
    virtual ~IRelsModifyChange() = default;
    // TODO: Interface members
};
// Interface Attributes
class IAttributes {
public:
    virtual ~IAttributes() = default;
    // TODO: Interface members
};
// Interface MaterialData
class IMaterialData {
public:
    virtual ~IMaterialData() = default;
    // TODO: Interface members
};
extern const js::number limitOf2Bytes;
// Enum ObjectClass
namespace ObjectClass {
    extern const js::number LINE;
    extern const js::number SHELL;
    js::string getName(js::number key);
}

// Enum TileRequestClass
namespace TileRequestClass {
    extern const js::number UPDATE;
    extern const js::number CREATE;
    extern const js::number DELETE;
    extern const js::number FINISH;
    js::string getName(js::number key);
}

// Const enum CurrentLod
namespace CurrentLod {
    constexpr int GEOMETRY = 0;
    constexpr int WIRES = 1;
    constexpr int INVISIBLE = 2;
}

// Enum MultiThreadingRequestClass
namespace MultiThreadingRequestClass {
    extern const js::number CREATE_MODEL;
    extern const js::number DELETE_MODEL;
    extern const js::number EXECUTE;
    extern const js::number RAYCAST;
    extern const js::number FETCH_BOXES;
    extern const js::number REFRESH_VIEW;
    extern const js::number RECOMPUTE_MESHES;
    extern const js::number CREATE_MATERIAL;
    extern const js::number THROW_ERROR;
    js::string getName(js::number key);
}

// Enum ItemConfigClass
namespace ItemConfigClass {
    extern const js::number VISIBLE;
    js::string getName(js::number key);
}

// Enum SnappingClass
namespace SnappingClass {
    extern const js::number POINT;
    extern const js::number LINE;
    extern const js::number FACE;
    js::string getName(js::number key);
}

// Interface ModelIdMap
class IModelIdMap {
public:
    virtual ~IModelIdMap() = default;
    // TODO: Interface members
};
// Interface RaycastData
class IRaycastData {
public:
    virtual ~IRaycastData() = default;
    // TODO: Interface members
};
// Interface SnappingRaycastData
class ISnappingRaycastData {
public:
    virtual ~ISnappingRaycastData() = default;
    // TODO: Interface members
};
// Interface RectangleRaycastResult
class IRectangleRaycastResult {
public:
    virtual ~IRectangleRaycastResult() = default;
    // TODO: Interface members
};
// Interface RectangleRaycastData
class IRectangleRaycastData {
public:
    virtual ~IRectangleRaycastData() = default;
    // TODO: Interface members
};
// Interface RaycastResult
class IRaycastResult {
public:
    virtual ~IRaycastResult() = default;
    // TODO: Interface members
};
// Interface ItemAttribute
class IItemAttribute {
public:
    virtual ~IItemAttribute() = default;
    // TODO: Interface members
};
// Interface ItemData
class IItemData {
public:
    virtual ~IItemData() = default;
    // TODO: Interface members
};
// Interface SpatialTreeItem
class ISpatialTreeItem {
public:
    virtual ~ISpatialTreeItem() = default;
    // TODO: Interface members
};
// Interface ItemsDataConfig
class IItemsDataConfig {
public:
    virtual ~IItemsDataConfig() = default;
    // TODO: Interface members
};
// Interface VirtualPropertiesConfig
class IVirtualPropertiesConfig {
public:
    virtual ~IVirtualPropertiesConfig() = default;
    // TODO: Interface members
};
// Interface VirtualModelConfig
class IVirtualModelConfig {
public:
    virtual ~IVirtualModelConfig() = default;
    // TODO: Interface members
};
// Interface MappedSelectionInput
class IMappedSelectionInput {
public:
    virtual ~IMappedSelectionInput() = default;
    // TODO: Interface members
};
// Interface MappedResultInput
class IMappedResultInput {
public:
    virtual ~IMappedResultInput() = default;
    // TODO: Interface members
};
// Interface MappedInformationResult
class IMappedInformationResult {
public:
    virtual ~IMappedInformationResult() = default;
    // TODO: Interface members
};
// Interface AttributesUniqueValuesParams
class IAttributesUniqueValuesParams {
public:
    virtual ~IAttributesUniqueValuesParams() = default;
    // TODO: Interface members
};
// Interface ModelSection
class IModelSection {
public:
    virtual ~IModelSection() = default;
    // TODO: Interface members
};

#endif // MODEL_TYPES_H