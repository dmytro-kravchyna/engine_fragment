#ifndef VIRTUAL_MATERIAL_CONTROLLER_H
#define VIRTUAL_MATERIAL_CONTROLLER_H

#include "index_generated.h"


#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <map>
#include <optional>
#include <initializer_list>
#include "runtime/core.h"
#include "../../model/model-types.h"
#include "../../../../Schema.h"
#include "../../utils/geometry/parser-helper.h"
#include "../../utils/geometry/material-utils.h"

using namespace js;

// Forward declarations
class VirtualMaterialController;

class VirtualMaterialController {
public:
    VirtualMaterialController(js::string modelId, VirtualMaterialTransfer onTransfer);
    virtual js::array<js::number> update(Model model);
    virtual auto fetch(js::number materialId);
    virtual js::array<js::number> transfer(js::array<MaterialDefinition> materials);
    virtual auto getItemsMaterialDefinition(Model model, js::array<js::number> indices, js::array<js::number> localIds);
private:
    js::string _modelId;
    js::array<MaterialDefinition> _list;
    std::shared_ptr<VirtualMaterialTransfer> _onTransfer;
    virtual auto checkMaterialExists(MaterialDefinition material, js::array<js::number> ids);
    virtual auto deduplicateMaterials(js::array<MaterialDefinition> materialDefinition);
    virtual auto getAll(Meshes meshes, js::array<MaterialDefinition> materialDefinitions);
    virtual auto transferMaterialData(js::array<MaterialDefinition> materialDefinitions);
};

#endif // VIRTUAL_MATERIAL_CONTROLLER_H