#ifndef MATERIAL_MANAGER_H
#define MATERIAL_MANAGER_H

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
#include <three/examples/jsm/lines/LineMaterial.js.h>
#include "./model-types.h"
#include "../utils.h"
#include "../lod.h"
#include "../../../Utils.h"

using namespace js;

// Forward declarations
class MaterialManager;

class MaterialManager {
public:
    MaterialManager() = default;
    auto list;
    auto resetColors(js::array<MaterialDefinition> definitions);
    virtual auto dispose(js::string modelId);
    virtual auto get(MaterialDefinition data, js::any request);
    virtual auto addDefinitions(js::string modelID, js::array<MaterialDefinition> materials);
    virtual auto createHighlights(BIMMesh mesh, js::any request);
    virtual auto getFromRequest(js::any request);
private:
    auto _modelMaterialMapping;
    auto _definitions;
    auto _idGenerator;
    auto white;
    virtual auto newLODMaterial(MaterialData data, js::any request);
    virtual auto getParameters(MaterialDefinition data);
    virtual auto new(MaterialDefinition data, js::any request);
    virtual auto addMaterialToModel(js::string modelId, js::number id);
    virtual auto processHighlight(Map localMap, js::any highlightIndex, js::array<MaterialDefinition> materialDefinitions, js::any index, js::any request, js::array<unknown> materials);
    virtual auto getUniqueMaterial(js::number id, MaterialDefinition data, js::any request);
};

#endif // MATERIAL_MANAGER_H