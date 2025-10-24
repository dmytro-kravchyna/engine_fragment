#ifndef VIRTUAL_CIRCLE_EXTRUSION_MANAGER_H
#define VIRTUAL_CIRCLE_EXTRUSION_MANAGER_H

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
#include "./types.h"
#include "../../model/model-types.h"
#include "../../../../Schema.h"
#include "./virtual-mesh-manager.h"
#include "./circle-extrusion.h"

using namespace js;

// Forward declarations
class VirtualCircleExtrusionManager;

class VirtualCircleExtrusionManager : public VirtualMeshManager {
public:
    VirtualCircleExtrusionManager() = default;
    auto setupTemplates() override;
    auto fetchLod(js::number meshId, bool evenVoid) override;
    auto fetchMeshes(js::number meshId, bool evenVoid) override;
    auto raycast(js::number id, js::any ray) override;
    auto faceRaycast() override;
    auto pointRaycast(js::number id, js::any ray) override;
    auto lineRaycast(js::number id, js::any ray) override;
    auto getObjectClass() override;
    auto getRepresentation() override;
    auto getLodClass() override;
private:
    auto _vceConstructor;
    auto _lodConstructor;
    auto _vceRaycaster;
    auto _vceLineRaycaster;
    auto _vcePointRaycaster;
    auto _representationClass;
    auto _objectClass;
    auto lodClass;
    auto newMeshes(js::number meshId, js::array<TileData> meshes) override;
    auto generateMeshesIfNeeded(js::number meshId, bool createIfVoid, js::array<TileData> meshes) override;
    auto newCircleExtrusionTemplate(js::number id) override;
    auto generateLodIfNeeded(js::number meshId, bool evenVoid, TileData mesh) override;
};

#endif // VIRTUAL_CIRCLE_EXTRUSION_MANAGER_H