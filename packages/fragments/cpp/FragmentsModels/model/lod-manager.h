#ifndef LOD_MANAGER_H
#define LOD_MANAGER_H

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
#include "../lod/lod-helper.h"
#include "./model-types.h"
#include "../utils.h"
#include "./material-manager.h"

using namespace js;

// Forward declarations
class LODManager;

class LODManager {
public:
    LODManager(MaterialManager materials);
    virtual auto createMesh(js::any geometry, js::any request);
    virtual auto updateVisibility(LODMesh mesh, js::any status);
    virtual auto processMesh(BIMMesh mesh, js::any request);
private:
    std::shared_ptr<MaterialManager> _materials;
    auto white;
    virtual auto deleteAttributeEvent(js::any _geometry);
};

#endif // LOD_MANAGER_H