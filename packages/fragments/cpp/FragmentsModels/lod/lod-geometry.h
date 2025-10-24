#ifndef LOD_GEOMETRY_H
#define LOD_GEOMETRY_H

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
#include "./lod-helper.h"

using namespace js;

// Forward declarations
class LODGeometry;

class LODGeometry : public three::InstancedBufferGeometry {
public:
    auto isLODGeometry;
    bool isFiltered() override;
    LODGeometry();
    auto computeBoundingBox() override;
    auto applyMatrix4(js::any matrix) override;
    auto computeBoundingSphere() override;
    auto getItemFilter() override;
    auto getItemLast() override;
    auto getItemFirst() override;
private:
    auto applyTransformToBuffers(js::any matrix) override;
    auto updateBounds() override;
};

#endif // LOD_GEOMETRY_H