#ifndef LOD_HELPER_H
#define LOD_HELPER_H

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
#include <three/examples/jsm/Addons.js.h>
#include "./lod-geometry.h"
#include "./lod-shaders.h"
#include "./lod-mesh.h"

using namespace js;

// Forward declarations
class LodHelper;

class LodHelper {
public:
    LodHelper() = default;
    auto tempVec;
    auto tempBox;
    auto setupLodMeshResize(LODMesh mesh);
    void setupLodAttributes(js::any geometry);
    auto setLodBuffer(LODGeometry lodGeometry, js::Float32Array data, std::optional<std::function<void()>> onFinish = std::nullopt);
    void setLodVisibility(LODGeometry lodGeometry, js::any visible);
    auto getInterAttribute(js::any geometry, js::string name);
    auto computeLodSphere(LODGeometry geometry);
    auto newLodMaterialParams(LineMaterialParameters parameters);
    void setLodFilter(LODGeometry geometry, js::any data);
    auto getInstancedAttribute(js::any geometry, js::string name);
    auto computeLodBox(LODGeometry geometry);
private:
    auto setDataBuffer(js::typed::Nullable<unknown> dataBuffer, js::any itemFirst, js::Float32Array data);
    auto disposeAllData(js::any geometry);
    auto setItemFirst(LODGeometry lodGeometry, js::any itemFirst, js::Float32Array data, js::any itemLast);
    auto setupFinish(js::typed::Nullable<std::function<void()>> onFinish, js::typed::Nullable<unknown> dataBuffer);
    auto resetAttributes(js::any itemFirst, js::typed::Nullable<unknown> dataBuffer, js::Float32Array data, js::any itemLast);
    auto setupItemFilter(LODGeometry lodGeometry);
    auto applyVisibilityState(LODGeometry lodGeometry, js::any visible, js::any itemFilter);
    auto getLodMidPoint(LODGeometry geometry, js::any itemFirst);
    auto getLodRadius(js::any midPoint, js::any itemFirst);
    auto vertices;
    auto indices;
};

#endif // LOD_HELPER_H